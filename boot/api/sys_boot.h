#ifndef __SYS_BOOT_H__
#define __SYS_BOOT_H__


#define REC_DATA              ((uint8_t)0x00)
#define REC_EX_LINEAR         ((uint8_t)0x04)
#define REC_EX_SEG            ((uint8_t)0x02)
#define REC_START_LINEAR      ((uint8_t)0x05)
#define REC_END               ((uint8_t)0x01)

typedef enum _RecordFormat_EN
{
	FORMAT_NONE,
	FORMAT_EX_LINEAR,
	FORMAT_EX_SEGMENT,
	FORMAT_MAX,
}RecordFormat_EN;

typedef enum _HEX_Record_State
{
	HEX_RECORD_IDLE,
	HEX_RECORD_PROCESSING,
	HEX_RECORD_PROCESSED,
	HEX_RECORD_CORRUPT,
	HEX_RECORD_MAX_STATES,
}HEX_Record_State;

typedef struct FormatAddress_ST
{
	RecordFormat_EN Format;
	uint16_t Address;
}FormatAddress_ST;

typedef struct _HEX_Record_ST
{
	uint8_t  Length;
	uint8_t  Address[2];
	uint8_t  RecordType;
	uint8_t  RecordData[256];
}HEX_Record_ST;

typedef union _HEX_Record_UN
{
	HEX_Record_ST RecordData;
	uint8_t Data[260];
}HEX_Record_UN;


extern void SYS_BOOT_Main(unsigned char Byte);


#endif //__SYS_BOOT_H__
