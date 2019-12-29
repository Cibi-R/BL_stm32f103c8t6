#include <includes.h>
#include LIB_H


uint8_t LIB_Evaluate_Checksum(uint8_t Data[], uint8_t Len)
{
	uint8_t RetVal = 0;
	uint8_t i;
	uint32_t Checksum = 0;

	if ((Data != NULL) && (Len != 0))
	{
		for (i = 0; i < Len-1; i++)
		{
			Checksum = Checksum + (uint32_t)Data[i];
		}

		Checksum = (~Checksum) + 1;

		if ((uint8_t)(Checksum & 0xFF) == Data[i])
		{
			RetVal = 1;
		}
		else
		{
			RetVal = 0;
		}
	}

	else
	{
		RetVal = 0;
	}

	return RetVal;
}
