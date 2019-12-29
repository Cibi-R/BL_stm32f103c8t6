#ifndef __COM_H__
#define __COM_H__

#include "com_config.h"

/******************************************************************************************************************************
 *												      Type definitions
 ******************************************************************************************************************************/

typedef enum _COM_Frame_State
{
	COM_FRAME_IDLE,
	COM_FRAME_PROCESSING,
	COM_FRAME_PROCESSED,
	COM_FRAME_CORRUPT,
	COM_MAX_STATES,
}COM_Frame_State;

typedef struct _MessageFrame_ST
{
	COM_Frame_State Frame_State;
	uint8_t Id;
	uint8_t Dlc;
}MessageFrame_ST;


/******************************************************************************************************************************
 *												      Function Declarations
 ******************************************************************************************************************************/

extern void COM_Main(uint8_t Byte);

extern void COM_Init(void);

#endif //__COM_H__
