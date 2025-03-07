#include "stm32f10x.h"                  // Device header
#include "MyIIC.h"
#include "MPU6050_REG.h"
#include "MPU6050.h"
#define MPU6050_ADDR 0XD0



void MPU6050_WriteReg(uint8_t RegAddress , uint8_t DATA)
{
	MyIIC_Start();				  //发送开始信号
	MyIIC_SendByte(MPU6050_ADDR); //发送从机地址 7位数据+1位读写位
	MyIIC_ReceiveACK();
	MyIIC_SendByte(RegAddress);   //发送寄存器地址
	MyIIC_ReceiveACK();
	MyIIC_SendByte(DATA);		  //发送数据
	MyIIC_ReceiveACK();			  
	MyIIC_Stop();				  //发送结束信号
	
	
}


#define Read (MPU6050_ADDR|0x01)       //读写位 改为读 (注：默认写)

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	MyIIC_Start();				  	//发送开始信号
	MyIIC_SendByte(MPU6050_ADDR); 	//发送从机地址
	MyIIC_ReceiveACK();
	MyIIC_SendByte(RegAddress);   	//发送寄存器地址
	MyIIC_ReceiveACK();
	
	MyIIC_Start();				  	//发送开始信号
	MyIIC_SendByte(Read); 		  	//接下来要读从机的信号
	MyIIC_ReceiveACK();			  	//接收应答后总线控制权正式交给从机
	uint8_t Byte = MyIIC_ReceiveByte();
	MyIIC_SendACK(1);			  	//不给从机应答 
	MyIIC_Stop();				  	//发送结束信号
	return Byte;
}

void MPU6050_Init(void)
{
	MyIIC_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01); 		//选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00); 		//6轴都不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09); 		//10分频
	MPU6050_WriteReg(MPU6050_CONFIG,0x06); 	  		//数字低通滤波选最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18); 	//陀螺仪配置  最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18); 	//加速度配置  最大量程
		
}


uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}


SixAxisParamTypedef MPU6050_GetData(void)
{
	uint16_t DataH,DataL;
	SixAxisParamTypedef SixAxisParamStruct;
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);  //高八位
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);  //低八位
	SixAxisParamStruct.Acc_X = (DataH<<8)|DataL;  //高八位左移8位与低8位相与 
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	SixAxisParamStruct.Acc_Y = (DataH<<8)|DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	SixAxisParamStruct.Acc_Z = (DataH<<8)|DataL;
/*****************************************************************************/	
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	SixAxisParamStruct.Gyro_X = (DataH<<8)|DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	SixAxisParamStruct.Gyro_Y = (DataH<<8)|DataL;
	
	DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	SixAxisParamStruct.Gyro_Z = (DataH<<8)|DataL;		
	return SixAxisParamStruct;
}
