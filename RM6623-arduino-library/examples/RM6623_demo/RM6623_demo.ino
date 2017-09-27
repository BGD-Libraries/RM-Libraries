#include <mcp_can.h>
#include <RM6623.h>
#include <SPI.h>
const int SPI_CS_pin=40;

MCP_CAN CAN(SPI_CS_pin);

uint8_t CAN_len = 0;        //数据长度
uint8_t can_tx_data[8];     //发送的数据
uint8_t can_rx_data[8];     //接收的数据
uint32_t CAN_ID;

void setup() {
  Serial.begin(115200);
  pinMode(A6,INPUT);
  while(1){
    if(CAN_OK == CAN.begin(CAN_1000KBPS)){
        Serial.println("CAN BUS Shield init ok!");
        break;
    }
    else{
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
    }
  }
  // attachInterrupt(5, MCP2515_ISR, FALLING); // start interrupt
}

// void MCP2515_ISR()
// {
//     flagRecv = 1;
// }
void loop() {
  /*接收RM6623的CAN数据*/
  if(CAN_MSGAVAIL == CAN.checkReceive()){
    CAN.readMsgBufID(&CAN_ID,&CAN_len,can_rx_data);   //接收can数据
    RM6623.unpack(CAN_ID,CAN_len,can_rx_data);          //处理can数据为RM6623格式
  }
  /*通过CAN向电机发送设定电流值*/
  /*RM6623.write(can_tx_data,0,0,0);
  * RM6623的数据处理函数，第一个参数是处理后的数组，
  *                       第二个参数是Pitch电流值，
  *                       第三个参数是Roll电流值，
  *                       第四个参数是Yaw电流值， -5000~5000
  */
  RM6623.pack(can_tx_data,500,500,500);     //将电流值转换为can格式
  CAN.sendMsgBuf(RM6623.tx_ID, 0, 8,can_tx_data);    //发送can数据

  
  Serial.print(RM6623.angle(RM6623.yaw_ID)/8191.0*360);    //角度
  Serial.print("\t");
  Serial.print(RM6623.real_current(RM6623.yaw_ID));        //实际电流值
  Serial.print("\t");
  Serial.print(RM6623.set_current(RM6623.yaw_ID));         //设置电流值，输出设置电流是输入设置电流的5倍
  Serial.print("\t");
  Serial.print(RM6623.hall(RM6623.yaw_ID));                //霍尔值
  Serial.println();

}
