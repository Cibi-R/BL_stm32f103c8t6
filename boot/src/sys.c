#include <includes.h>
#include UART_WRAPPER_H
#include TIMER_H
#include GPIO_H
#include FLASH_H
#include COM_H
#include COM_PROXY_H
#include SYS_BOOT_H
#include SYS_H

SYSTEM_State_EN SYSTEM_State = SYS_STATE_COMMAND;     /*< Stores the current state of the system. */
SYSTEM_State_EN SYSTEM_State_New = SYS_STATE_NONE;    /*< Stores the new requested state of the system. */


void SYS_State_Update(SYSTEM_State_EN State)
{
	SYSTEM_State = State;
}

uint8_t SYS_Change_Request_Available(void)
{
	if (SYSTEM_State_New != SYS_STATE_NONE)
	{
		return 1;
	}

	return 0;
}

void SYS_State_Change_Request(SYSTEM_State_EN State)
{
	SYSTEM_State_New = State;
}

void SYS_State_Change_Request_Process(void)
{
	if (SYSTEM_State_New == SYS_STATE_COMMAND)
	{
		SYSTEM_State = SYS_STATE_ENT_COMMAND;
	}

	else if (SYSTEM_State_New == SYS_STATE_REFLASH)
	{
		SYSTEM_State = SYS_STATE_ENT_REFLASH;
	}

	else
	{
		
	}

	SYSTEM_State_New = SYS_STATE_NONE;
}

void SYS_Handler(void)
{
    switch (SYSTEM_State)
	{
		case SYS_STATE_ENT_COMMAND:
		{
			SYS_State_Update(SYS_STATE_COMMAND);
			break;
		}

		case SYS_STATE_COMMAND:
		{   
			while (Serial_Is_Data_Available())
			{
				COM_Main(Serial_Read_Data());
			}

			if (SYS_Change_Request_Available())
			{
				SYS_State_Update(SYS_STATE_EXT_COMMAND);
			}
			break;
		}

		case SYS_STATE_EXT_COMMAND:
		{
			SYS_State_Change_Request_Process();
			break;
		}

		case SYS_STATE_ENT_REFLASH:
		{
			/*< Open Flash Controller to perform reflash operation. */
			FLASH_Unlock();
			SYS_State_Update(SYS_STATE_REFLASH);
			Send_SYS_Text(SYS_ENT_REF);
			break;
		}
		
		case SYS_STATE_REFLASH:
		{
			while (Serial_Is_Data_Available())
			{
				SYS_BOOT_Main(Serial_Read_Data());
			}
			if (SYS_Change_Request_Available())
			{
				SYS_State_Update(SYS_STATE_EXT_REFLASH);
			}
			break;
		}

		case SYS_STATE_EXT_REFLASH:
		{
			/*< Close Flash controller while exiting reflash state. */
			FLASH_Lock();
			SYS_State_Change_Request_Process();
			break;
		}
		
		default:
		{
			break;
		}
	}
}

void TIM2_IRQHandler(void)
{
	/* Clear pending interrupt */
	TIM2->SR &= 0XFFFE;

	/* Clear TIM2 Interrupt pending state*/
	NVIC->ICPR[0] |= (1 << 28);

    SYS_Handler();
}


void SYS_Init(void)
{
    PORTA_CLOCK_ENABLE();

    AFIOEN_CLOCK_ENABLE();

    Serial_Init();

    Timer_2_Interrupt_Init();
}

void SYS_Main(void)
{

}
