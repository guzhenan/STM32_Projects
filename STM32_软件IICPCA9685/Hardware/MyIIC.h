#ifndef __MyIIC_H
#define __MyIIC_H
void MyIIC_Init(void);
void MyIIC_W_SCL(uint8_t BitValue);  	//写SCL电平状态
void MyIIC_W_SDA(uint8_t BitValue); 	//写SDA电平状态
uint8_t MyIIC_R_SDA(void);         		//读SDA数据
void MyIIC_Start(void);  				//起始条件：SCL高电平期间，SDA从高电平切换到低电平
void MyIIC_Stop(void);  				//结束条件：SCL高电平期间，SDA从低电平切换到高电平
void MyIIC_SendByte(uint8_t Byte);		//发送一个字节
uint8_t MyIIC_ReceiveByte(void); 		//接收一个字节
void MyIIC_SendACK(uint8_t ACKBit);		//发送一位应答位
uint8_t MyIIC_ReceiveACK(void); 		//接收一位应答位
#endif	
