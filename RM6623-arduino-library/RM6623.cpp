#include "RM6623.h"

RM6623_::RM6623_()
{
	
}

/********************************************************************************
将三个RM6623的电流值写入到buf数组，并转换为can数据格式
*********************************************************************************/
void RM6623_::pack(uint8_t *tx_data, int16_t yaw, int16_t pitch, int16_t roll)
{	
	if (yaw   < -5000 || yaw   > 5000)
		return;
	if (pitch < -5000 || pitch > 5000)
		return;
	if (roll  < -5000 || roll  > 5000)
		return;

	tx_data[0] = (unsigned char)(yaw >> 8)  &0xff; //yaw
	tx_data[1] = (unsigned char) yaw        &0xff;
	tx_data[2] = (unsigned char)(pitch >> 8)&0xff; //pitch
	tx_data[3] = (unsigned char) pitch      &0xff;
	tx_data[4] = (unsigned char)(roll >> 8) &0xff; //roll
	tx_data[5] = (unsigned char) roll       &0xff;
	tx_data[6] = 0x00;
	tx_data[7] = 0x00;
}
/********************************************************************************
根据ID接收can数据
*********************************************************************************/
bool RM6623_::unpack(uint32_t ID,uint8_t len,uint8_t *rx_data)
{
	if (len!=8)	return 0;
	if (ID == yaw_ID) { //yaw
		_Yaw.buf[1] = rx_data[0];
		_Yaw.buf[0] = rx_data[1];
		_Yaw.buf[3] = rx_data[2];
		_Yaw.buf[2] = rx_data[3];
		_Yaw.buf[5] = rx_data[4];
		_Yaw.buf[4] = rx_data[5];
		_Yaw.buf[6] = rx_data[6];
		_Yaw.buf[7] = rx_data[7];
		return 1;
	}
	if (ID == pitch_ID) { //pitch
		_Pitch.buf[1] = rx_data[0];
		_Pitch.buf[0] = rx_data[1];
		_Pitch.buf[3] = rx_data[2];
		_Pitch.buf[2] = rx_data[3];
		_Pitch.buf[5] = rx_data[4];
		_Pitch.buf[4] = rx_data[5];
		_Pitch.buf[6] = rx_data[6];
		_Pitch.buf[7] = rx_data[7];
		return 1;
	}
	if (ID == roll_ID) { //roll
		_Roll.buf[1] = rx_data[0];
		_Roll.buf[0] = rx_data[1];
		_Roll.buf[3] = rx_data[2];
		_Roll.buf[2] = rx_data[3];
		_Roll.buf[5] = rx_data[4];
		_Roll.buf[4] = rx_data[5];
		_Roll.buf[6] = rx_data[6];
		_Roll.buf[7] = rx_data[7];
		return 1;
	}
	return 0;
}
/********************************************************************************
根据ID获得编码器值
*********************************************************************************/
uint16_t RM6623_::encoder(uint32_t ID)
{
	if (ID == yaw_ID)		
		return _Yaw.encoder;

	if (ID == pitch_ID)	
		return _Pitch.encoder;

	if (ID == roll_ID)	
		return _Roll.encoder;
}
/********************************************************************************
根据ID获得角度
*********************************************************************************/
double RM6623_::angle(uint32_t ID)
{
	if (ID == yaw_ID)
		return _Yaw.encoder/(8191/360.0);

	if (ID == pitch_ID)
		return _Pitch.encoder/(8191/360.0);

	if (ID == roll_ID)
		return _Roll.encoder/(8191/360.0);
}
/********************************************************************************
根据ID获得实际电流值-13000 ~ 13000
*********************************************************************************/
int16_t RM6623_::real_current(uint32_t ID)
{
	if (ID == yaw_ID)
		return _Yaw.real_current;

	if (ID == pitch_ID)
		return _Pitch.real_current;

	if (ID == roll_ID)
		return _Roll.real_current;
}
/********************************************************************************
根据ID获得设定电流值-25000 ~ 25000
*********************************************************************************/
int16_t RM6623_::set_current(uint32_t ID)
{
	if (ID == yaw_ID)
		return _Yaw.set_current;

	if (ID == pitch_ID)
		return _Pitch.set_current;

	if (ID == roll_ID)
		return _Roll.set_current; 
}
/********************************************************************************
根据ID获得霍尔值1~6
*********************************************************************************/
uint8_t RM6623_::hall(uint32_t ID)
{
	if (ID == yaw_ID)
		return _Yaw.hall;

	if (ID == pitch_ID)
		return _Pitch.hall;

	if (ID == roll_ID)
		return _Roll.hall;
}

RM6623_ RM6623 = RM6623_();

