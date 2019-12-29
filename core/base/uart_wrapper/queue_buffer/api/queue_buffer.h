#ifndef __QUEUE_BUFFER_H__
#define __QUEUE_BUFFER_H__


/******************************************************************************************************************************
 *												      Function Declarations
 ******************************************************************************************************************************/

/*
 * @brief  : 
 * @para   : 
 * @return : 
 */

extern void BUF_Reset(void);


/*
 * @brief  : 
 * @para   : 
 * @return : 
 */

extern uint8_t BUF_Is_Data_Available(void);


/*
 * @brief  : 
 * @para   : 
 * @return : 
 */

extern void BUF_Enqueue(uint8_t Data);


/*
 * @brief  : 
 * @para   :
 * @return : 
 */

extern uint8_t BUF_Dequeue(void);

#endif //__QUEUE_BUFFER_H__
