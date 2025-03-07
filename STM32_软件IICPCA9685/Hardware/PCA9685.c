#include "stm32f10x.h"                  // Device header
#include "MyIIC.h"
#include "DELAY.h"
#include "PCA9685.h"
#include <math.h>
void PCA9685_Init(float hz,uint8_t angle)
{
	uint32_t off=0;
	MyIIC_Init();
	PCA9685_Write_Reg(PCA_Model,0x00);
	PCA9685_setFreq(hz);
	off = (u32)(158+angle*2.2);
	PCA9685_setPWM(0,0,off);
	PCA9685_setPWM(1,0,off);
	PCA9685_setPWM(2,0,off);
	PCA9685_setPWM(3,0,off);
	PCA9685_setPWM(4,0,off);
	PCA9685_setPWM(5,0,off);
	PCA9685_setPWM(6,0,off);
	PCA9685_setPWM(7,0,off);
	PCA9685_setPWM(8,0,off);
	PCA9685_setPWM(9,0,off);
	PCA9685_setPWM(10,0,off);
	PCA9685_setPWM(11,0,off);
	PCA9685_setPWM(12,0,off);
	PCA9685_setPWM(13,0,off);
	PCA9685_setPWM(14,0,off);
	PCA9685_setPWM(15,0,off);
	Delay_ms(100);
}

void PCA9685_Write_Reg(uint8_t Reg_Address,uint8_t Data)
{
	MyIIC_Start();
	
	MyIIC_SendByte(PCA_Addr);
	MyIIC_ReceiveACK(); 
	
	MyIIC_SendByte(Reg_Address);
	MyIIC_ReceiveACK(); 
	
	MyIIC_SendByte(Data);
	MyIIC_ReceiveACK(); 
	
	MyIIC_Stop();  
}


uint8_t PCA9685_Read_Reg(uint8_t Reg_Address)
{

	
	MyIIC_Start();
	
	MyIIC_SendByte(PCA_Addr);
	MyIIC_ReceiveACK(); 
	
	MyIIC_SendByte(Reg_Address);
	MyIIC_ReceiveACK(); 	
		
	MyIIC_Start();				  	//发送开始信号
	
	MyIIC_SendByte(PCA_Addr|0x01);  //接下来要读从机的信号
	MyIIC_ReceiveACK();			  	//接收应答后总线控制权正式交给从机
	
	uint8_t Byte = MyIIC_ReceiveByte();
	MyIIC_SendACK(1);			  	//不给从机应答 
	
	MyIIC_Stop();				  	//发送结束信号
	
	return Byte;
}

void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off)
{
		MyIIC_Start();
		
		MyIIC_SendByte(PCA_Addr);
		MyIIC_ReceiveACK(); 
		
		MyIIC_SendByte(LED0_ON_L+4*num);
		MyIIC_ReceiveACK(); 
		
		MyIIC_SendByte(on&0xFF);
		MyIIC_ReceiveACK(); 

		MyIIC_SendByte(on>>8);
		MyIIC_ReceiveACK(); 
		
		MyIIC_SendByte(off&0xFF);
		MyIIC_ReceiveACK(); 
		
		MyIIC_SendByte(off>>8);
		MyIIC_ReceiveACK(); 

		MyIIC_Stop();		
}

void PCA9685_setFreq(float freq)
{
	u8 prescale,oldmode,newmode;
	
	double prescaleval;
	
	//freq *= 0.92;
	prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale = floor(prescaleval+0.5f);
	oldmode = PCA9685_Read_Reg(PCA_Model);
	
	newmode = (oldmode&0x7F)|0x10;
	PCA9685_Write_Reg(PCA_Model,newmode);
	PCA9685_Write_Reg(PCA_Pre,prescale);
	PCA9685_Write_Reg(PCA_Model,oldmode);
	Delay_ms(5);
	PCA9685_Write_Reg(PCA_Model,oldmode|0xa1);
	
	
}

void setAngle(uint8_t num,uint8_t angle)
{
	u32 off = 0;
	off = (u32)(158+angle*2.2);
	PCA9685_setPWM(num,0,off);
}
