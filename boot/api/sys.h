#ifndef __SYS_H__
#define __SYS_H__


typedef enum _SYSTEM_State_EN
{
	SYS_STATE_NONE,
	SYS_STATE_ENT_COMMAND,  /*< Entering command state */
	SYS_STATE_EXT_COMMAND,  /*< Exiting command state */
	SYS_STATE_COMMAND,      /*< Ready to make state changes. */
	SYS_STATE_ENT_REFLASH,  /*< Entering reflash state */
	SYS_STATE_EXT_REFLASH,  /*< Exiting reflash state */
	SYS_STATE_REFLASH,      /*< Reflashing State */
	SYS_STATE_MAX,          /*< Max System states. */
}SYSTEM_State_EN;

extern SYSTEM_State_EN SYSTEM_State;
extern SYSTEM_State_EN SYSTEM_State_New;

/******************************************************************************************************************************
 *												                       Function Declarations
 ******************************************************************************************************************************/

 /*
  * @brief  : 
  * @para   : 
  * @return :
  */

extern void SYS_Init(void);


/*
 * @brief  : 
 * @para   : 
 * @return : 
 */

extern void SYS_Main(void);


extern void SYS_State_Change_Request(SYSTEM_State_EN State);


#endif //__SYS_H__
