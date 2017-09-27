#ifndef _RM6623_H_
#define _RM6623_H_
#include <stdint.h>
#if defined(ARDUINO)&&ARDUINO>=100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class RM6623_
{
	public:
		RM6623_();
		void pack(uint8_t *tx_data,int16_t yaw,int16_t pitch,int16_t roll);
		bool unpack(uint32_t ID,uint8_t len,uint8_t *rx_data);
		uint16_t encoder     (uint32_t ID);
		double   angle       (uint32_t ID);
		int16_t  real_current(uint32_t ID);
		int16_t  set_current (uint32_t ID);
		uint8_t  hall        (uint32_t ID);
		const uint32_t yaw_ID   =0x205;
		const uint32_t pitch_ID =0x206;
		const uint32_t roll_ID  =0x207;
		const uint32_t tx_ID    =0x1ff;
	private:
		typedef union
		{
			struct
			{
				unsigned    encoder:16;
				int    real_current:16;
				int     set_current:16;
				unsigned        hall:8;
			};
			unsigned char buf[8];
		}RM6623_rx_data;
		RM6623_rx_data _Pitch;
		RM6623_rx_data _Roll;
		RM6623_rx_data _Yaw;
};
extern RM6623_ RM6623;
#endif
