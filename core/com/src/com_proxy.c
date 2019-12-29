#include <includes.h>
#include UART_WRAPPER_H


void Send_SYS_Text(uint8_t Data)
{
	uint32_t Temp;
	uint8_t Text[] = { 0X7B,0XA0,0X02,0X00,0X00,0X7D };

	Text[3] = Data;

	Temp = (((~Data) + 1) & 0xFF);

	Text[4] = Temp & 0xFF;

	Serial_Tx_Array(Text,6);
}


