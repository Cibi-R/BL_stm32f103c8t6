#include <includes.h>
#include COM_H
#include COM_PROXY_H
#include SYS_BOOT_H
#include SYS_H
#include LIB_H

MessageFrame_ST MessageFrame;
uint8_t MessageData[5];
uint8_t MessageIndex;


static uint8_t Delimeter_Received = 0x00;

void COM_Reset_Frame(void)
{
	MessageFrame.Id = 0x00;
	MessageFrame.Dlc = 0x00;
	MessageFrame.Frame_State = COM_FRAME_IDLE;

	Delimeter_Received = 0x00;
}

void COM_Cmd_Parser(void)
{

	if (!LIB_Evaluate_Checksum(MessageData, MessageFrame.Dlc))
	{
		Send_SYS_Text(SYS_CHECK_ERR);
	}

	else if (MessageFrame.Id == SYS_TEXT_ID)
	{
		if (MessageIndex == SYS_TEXT_LEN)
		{
			switch (MessageData[0])
			{
				case SYS_HB:
				{
					Send_SYS_Text(SYS_ACK);
					break;
				}

				case SYS_GET_MODE:
				{
					break;
				}

				case SYS_ENT_CMD:
				{
					break;
				}

				case SYS_ENT_REF:
				{
					Send_SYS_Text(SYS_ACK);
					SYS_State_Change_Request(SYS_STATE_REFLASH);			
					break;
				}
				
				case SYS_ENT_APP:
				{
					Send_SYS_Text(SYS_ACK);
					
					NVIC->ICER[0] |= (1<<28); /*< Disable timer interrupt */
					
					uint32_t MSP_Value = *((uint32_t volatile*)0X08002000U);
	
					void (*App_Reset_Handler)(void);
	
					App_Reset_Handler = (void(*)(void))(*(uint32_t*)(0X08002000U + 4));
	
					/* Initiate the Main Stack Pointer. */
					__set_MSP(MSP_Value);
	
					/* Call the reset handler of Application program. */
					App_Reset_Handler();
					
					break;
				}

				default:
				{
					break;
				}
			}
		}
	}

	COM_Reset_Frame();
}

void COM_Handler(uint8_t Byte)
{
	if ((Byte == STX) && (Delimeter_Received != 0x01))
	{
		MessageFrame.Frame_State = COM_FRAME_PROCESSING;
	}

	else if ((Byte == ETX) && (Delimeter_Received != 0x01))
	{
		COM_Cmd_Parser();
	}

	else
	{
		if (MessageFrame.Frame_State == COM_FRAME_PROCESSING)
		{
			if ((Byte == DLE) && (Delimeter_Received != 0x01))
			{
				Delimeter_Received = 0x01;

				return;
			}

			if (MessageFrame.Id == 0)
			{
				MessageFrame.Id = Byte;
			}

			else if (MessageFrame.Dlc == 0)
			{
				MessageFrame.Dlc = Byte;
			}

			else
			{
				MessageData[MessageIndex] = Byte;
				MessageIndex++;
			}

			if (Delimeter_Received == 0x01)
			{
				Delimeter_Received = 0x00;
			}
		}
	}
}

void COM_Main(uint8_t Byte)
{
	COM_Handler(Byte);
}

void COM_Init(void)
{
	COM_Reset_Frame();
}
