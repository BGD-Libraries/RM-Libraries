#include "rm3510.h"

rm3510::rm3510()
{
	init_state     = 0;
	init_value     = 0;
	raw_value      = 0;
	last_raw_value = 0;
	round_cnt      = 0;
	rate           = 0;
	angle          = 0;
}

void rm3510::encoderProcess(uint8_t *data)
{
	last_raw_value = raw_value;
	raw_value = ((uint16_t)data[0]<<8)|data[1];

	if (init_state == 0) {
		init_state = 1;
		last_raw_value = raw_value;
	}

	int16_t diff = raw_value - last_raw_value;
	//两次编码器的反馈值差别太大，表示圈数发生了改变
	if (diff < -7500) {
		round_cnt++;
	}
	else if (diff>7500) {
		round_cnt--;
	}

	//计算得到角度值，范围正负无穷大
	angle = (float)(raw_value - init_value)*360/8192 + round_cnt * 360;

	rate = (((uint16_t)data[2]<<8)|data[3]);
}

int16_t rm3510::getRate()
{
	return rate;
}

int16_t rm3510::getEncode()
{
	return raw_value;
}


float rm3510::getAngle()
{
	return angle;
}

int16_t rm3510::resetInitEncode()
{
	init_state = raw_value;
	round_cnt = 0;
	return init_state;
}

int16_t rm3510::resetInitEncode(uint16_t encode_value)
{
	if (encode_value < 8192) {
		init_state = encode_value;
		round_cnt = 0;
	}
	return init_state;
}
