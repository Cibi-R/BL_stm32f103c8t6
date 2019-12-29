#ifndef __COM_CONFIG_H__
#define __COM_CONFIG_H__

/******************************************************************************************************************************
 *												      Preprocessor Constants
 ******************************************************************************************************************************/

#define STX				   ((unsigned char)0x7B)  /*< Start of Text */
#define ETX				   ((unsigned char)0x7D)  /*< End of Text */
#define DLE				   ((unsigned char)0x05)  /*< Data link escape */


/******************************************************************************************************************************
 *												         Frame IDs
 ******************************************************************************************************************************/

#define SYS_TEXT_ID        ((unsigned char)0xA0)  /*< For general communication */



/******************************************************************************************************************************
 *												       Frame Lengths
 ******************************************************************************************************************************/

#define SYS_TEXT_LEN       ((unsigned char)0x02) /*< Length of Text of general communication */



/******************************************************************************************************************************
 *												       Frame Data
 ******************************************************************************************************************************/

#define SYS_HB             ((uint8_t)0xFF)  /*< System HeartBeat */
#define SYS_ACK		       ((uint8_t)0x00)  /*< System Acknowledge */
#define SYS_NACK           ((uint8_t)0x01)  /*< System Not Acknowledge */
#define SYS_CHECK_ERR      ((uint8_t)0x02)  /*< Checksum Error */   
#define SYS_REQ_FRAME	   ((uint8_t)0x03)  /*< Request frame */
#define SYS_GET_MODE	   ((uint8_t)0x04)  /*< Get Current Operating mode. */

#define SYS_ADD_ERR        ((uint8_t)0x10)  /*< Address Error - Not in valid range. */

#define SYS_ENT_IDLE       ((uint8_t)0x0A)  /*< To Enter Idle state */  
#define SYS_EXT_IDLE       ((uint8_t)0x0B)  /*< To Exit Idle State */
#define SYS_ENT_CMD        ((uint8_t)0x0C)  /*< To Enter Command State */
#define SYS_EXT_CMD        ((uint8_t)0x0D)  /*< To Exit Command State */
#define SYS_ENT_REF        ((uint8_t)0x0E)  /*< To Enter Reflash State */
#define SYS_EXT_REF        ((uint8_t)0x0F)  /*< To Exit Reflash State */
#define SYS_ENT_APP        ((uint8_t)0x10)  /*< To Enter Application program */
#define SYS_EXT_APP        ((uint8_t)0x11)  /*< To Exit Application program */

#endif //__COM_CONFIG_H__
