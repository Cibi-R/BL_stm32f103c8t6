#include <includes.h>
#include FLASH_H
#include SYS_BOOT_H
#include SYS_H
#include COM_H
#include COM_CONFIG_H
#include COM_PROXY_H
#include LIB_H

HEX_Record_UN Hex_Record;					     /*< To Store the record info. */
HEX_Record_State RecordState = HEX_RECORD_IDLE;  /*< To Store the current state of the record frame. */

FormatAddress_ST FormatAddress;                  /*< To store the info about record address type (linear segment, extended segment,
													    start linear address.) */

uint32_t CurrentAddress = 0x00000000;             /*< To store the starting address of the current received record. */

uint32_t MainFunAddress = 0x00000000;             /*< Main Function address applicable only for ARM devices. */

static uint16_t RecordIndex = 0;	        	  /*< To store the index of the receiving frame. */
static uint8_t Delimeter_Received = 0x00;         /*< To store the status of the delimeter status while receiving. */

void SYS_BOOT_Reset_Record(void)
{
	uint16_t i;

	/* Use memcpy */
	for (i = 0; i < 260; i++)
	{
		Hex_Record.Data[i] = 0;
	}

	RecordState = HEX_RECORD_IDLE;

	RecordIndex = 0;

	Delimeter_Received = 0x00;
}

void SYS_BOOT_Reflash(void)
{
	uint16_t *Data = (uint16_t *)&Hex_Record.Data[4];

	uint8_t i;

	if (Hex_Record.RecordData.Length % 2)
	{
		Hex_Record.RecordData.RecordData[Hex_Record.RecordData.Length] = 0xFF;
	}
	
	for (i = 0; i < Hex_Record.RecordData.Length; i = i + 2)
	{
		FLASH_Program(FLASH_PROGRAM_HALFWORD, CurrentAddress, *Data);

		CurrentAddress += 2;

		Data++;
	}
}

void SYS_BOOT_Parser(void)
{

	if (!LIB_Evaluate_Checksum(Hex_Record.Data, RecordIndex))
	{
		/*< Send Checksum Error. */
		Send_SYS_Text(SYS_CHECK_ERR);
		return;
	}

	if (Hex_Record.RecordData.RecordType == REC_DATA)
	{
		CurrentAddress = (((uint32_t)Hex_Record.RecordData.Address[0] << 8) | (uint32_t)Hex_Record.RecordData.Address[1]);

		if (FormatAddress.Format == FORMAT_EX_LINEAR)
		{
			CurrentAddress = CurrentAddress | (uint32_t)FormatAddress.Address << 16;
		}
		else if (FormatAddress.Format == FORMAT_EX_SEGMENT)
		{

		}
		else if (FormatAddress.Format == FORMAT_NONE)
		{

		}
		else
		{

		}
		
		SYS_BOOT_Reflash();
	}

	else if (Hex_Record.RecordData.RecordType == REC_EX_LINEAR)
	{
		FormatAddress.Format = FORMAT_EX_LINEAR;
		FormatAddress.Address = ((uint16_t)Hex_Record.RecordData.RecordData[1] | (8 << (uint16_t)Hex_Record.RecordData.RecordData[0]));
	}

	else if (Hex_Record.RecordData.RecordType == REC_EX_SEG)
	{

	}

	else if (Hex_Record.RecordData.RecordType == REC_START_LINEAR)
	{
		
	}

	else if (Hex_Record.RecordData.RecordType == REC_END)
	{
		SYS_State_Change_Request(SYS_STATE_COMMAND);
	}

	else
	{
		/*< Invalid record. */
	}

	/*< Acknowledge the frame. */
	Send_SYS_Text(SYS_ACK);

	SYS_BOOT_Reset_Record();
}

void SYS_BOOT_Handler(unsigned char Byte)
{
	if ((Byte == STX) && (Delimeter_Received != 0x01))
	{
		RecordState = HEX_RECORD_PROCESSING;
	}

	else if ((Byte == ETX) && (Delimeter_Received != 0x01))
	{
		SYS_BOOT_Parser();

		RecordState = HEX_RECORD_PROCESSED;
	}

	else
	{
		if (RecordState == HEX_RECORD_PROCESSING)
		{
			if ((Byte == DLE) && (Delimeter_Received != 0x01))
			{
				Delimeter_Received = 0x01;

				return;
			}

			if (RecordIndex <= 260)
			{
				Hex_Record.Data[RecordIndex] = Byte;
				RecordIndex++;
			}

			else
			{
				RecordState = HEX_RECORD_CORRUPT;
			}

			if (Delimeter_Received == 0x01)
			{
				Delimeter_Received = 0x00;
			}
		}
	}
}

void SYS_BOOT_Main(unsigned char Byte)
{
	SYS_BOOT_Handler(Byte);
}
