#include <includes.h>
#include GPIO_H
#include UART_H
#include "../queue_buffer/api/queue_buffer.h"


void Serial_Rx_Handler(void)
{
    BUF_Enqueue(UART_Rx_Bytes(UART1));
}

void Serial_Init(void)
{
    /*< UART-1 Pin Configuration. No remapping programmed for UART1. */
	GPIO_Config PA9, PA10;

    /*< UART-1 */
	PA9.CurrentPort = PA;
	PA9.CurrentPin = P9;
	PA9.PinState = Output_Alternate_PushPull;
	PA9.PinMode = Speed_50MHz_Output;

    PA10.CurrentPort = PA;
	PA10.CurrentPin = P10;
	PA10.PinState = Input_Floating;
	PA10.PinMode = Input;

    /*< Instantiate variable to configure UART peripherals. */
    UART_Config_ST uart1;

    uart1.Instance = UART1;
    uart1.WordLength = UART_8Bit;
    uart1.ParitySelection = UART_No_Parity;
    uart1.StopBits = UART_1_StopBit;
    uart1.BaudRate = UART_Baud_9600;
    uart1.OperatingMode = UART_Transceiver;
	uart1.UART_Rx_ISR = Serial_Rx_Handler;

    /*< Enable clock of the UART. */
    ENABLE_UART1_CLOCK();

    /*< Enable the UART interrupt. */
	NVIC_EnableIRQ(USART1_IRQn);

    /*< UART-1 */
	GPIO_Config_Pin(&PA9);
	GPIO_Config_Pin(&PA10);

    /*< Configure UART. */
    UART_Config_Init(&uart1);
}

void Serial_Tx_Byte(uint8_t Byte)
{
    UART_Tx_Bytes(UART1,Byte);
}

void Serial_Tx_Array(uint8_t *const Byte,uint8_t Len)
{
    UART_Tx_Array(UART1,Byte,Len);
}

uint8_t Serial_Is_Data_Available(void)
{
    return BUF_Is_Data_Available();
}

uint8_t Serial_Read_Data(void)
{
    return BUF_Dequeue();
}
