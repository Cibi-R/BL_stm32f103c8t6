#include <stdint.h>
#include "../api/queue_buffer.h"


/******************************************************************************************************************************
 *												      Preprocessor Constants
 ******************************************************************************************************************************/

/*< Queue Buffer Size */
#define BUFFER_SIZE        50

/*< */
#define BUFFER_EMPTY       0XFF


#if BUFFER_SIZE > 100
    #error "Buffer can not be higher than 100 bytes"
#endif


/*< */
static unsigned char Buffer_DATA[BUFFER_SIZE];

/*< */
static uint8_t BUF_Front = BUFFER_EMPTY;
static uint8_t BUF_Rear  = BUFFER_EMPTY;


void BUF_Reset(void)
{
    unsigned char Index;

    BUF_Front = BUFFER_EMPTY;
    BUF_Rear  = BUFFER_EMPTY;

    for (Index = 0; Index < BUFFER_SIZE; Index++)
    {
        Buffer_DATA[Index] = 0;
    }
}

static uint8_t BUF_Is_Full(void)
{
    if (((BUF_Rear + 1) % BUFFER_SIZE) == BUF_Front)
    {
        return 1;
    }

    return 0;
}


static uint8_t BUF_Is_Empty(void)
{
    if ((BUF_Front == 0XFF) && (BUF_Rear == 0XFF))
    {
        return 1;
    }

    return 0;
}

uint8_t BUF_Is_Data_Available(void)
{
    if (BUF_Is_Empty())
    {
        return 0;
    }

    return 1;
}

void BUF_Enqueue(uint8_t Data)
{
    if (BUF_Is_Empty())
    {
        BUF_Front = 0; BUF_Rear = 0;
    }

    else if (BUF_Is_Full())
    {
        return;
    }

    else
    {
        BUF_Rear++;
    }

    if (BUF_Rear == BUFFER_SIZE)
    {
        BUF_Rear = 0;
    }

    Buffer_DATA[BUF_Rear] = Data;
}

uint8_t BUF_Dequeue(void)
{
    uint8_t Data;

    if (BUF_Is_Empty())
    {
        Data = 0;
    }
    
    else if (BUF_Front == BUF_Rear)
    {
        Data = Buffer_DATA[BUF_Front];

        BUF_Front = BUFFER_EMPTY; BUF_Rear = BUFFER_EMPTY;
    }

    else
    {
        Data = Buffer_DATA[BUF_Front];

        BUF_Front++;

        if (BUF_Front == BUFFER_SIZE)
        {
            BUF_Front = 0;
        }
    }

    return Data;
}
