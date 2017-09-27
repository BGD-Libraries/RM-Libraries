#ifndef _RM3510_H_
#define _RM3510_H_

#include <stdint.h>

class rm3510
{
public:
	rm3510();
	void  encoderProcess(uint8_t *data);
	int16_t getRate();
	int16_t getEncode();
	float   getAngle();
	int16_t resetInitEncode();
	int16_t resetInitEncode(uint16_t encode_value);
private:
	static const uint8_t RATE_BUF_SIZE = 1;
	uint8_t  init_state;
	uint16_t init_value;              //初始编码器值
	uint16_t raw_value;               //编码器不经处理的原始值
	uint16_t last_raw_value;          //上一次的编码器原始值
	int32_t  round_cnt;               //圈数
	int16_t  rate;                    //速度
	float    angle;                   //角度
};
#endif
