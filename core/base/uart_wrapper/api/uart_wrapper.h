#ifndef __UART_WRAPPER_H__
#define __UART_WRAPPER_H__

/******************************************************************************************************************************
 *												  Preprocessor Macros
 ******************************************************************************************************************************/





/******************************************************************************************************************************
 *												  Function Declaration
 ******************************************************************************************************************************/

extern void Serial_Init(void);

extern void Serial_Tx_Byte(uint8_t Byte);

extern void Serial_Tx_Array(uint8_t *const Byte,uint8_t Len);

extern uint8_t Serial_Is_Data_Available(void);

extern uint8_t Serial_Read_Data(void);

#endif //__UART_WRAPPER_H__
