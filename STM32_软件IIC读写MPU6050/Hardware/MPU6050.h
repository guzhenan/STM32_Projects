#ifndef __MPU6050_H
#define __MPU6050_H

typedef struct 
{
	int16_t Acc_X,Acc_Y,Acc_Z;
	int16_t Gyro_X,Gyro_Y,Gyro_Z;
}SixAxisParamTypedef;

void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t RegAddress , uint8_t DATA);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
SixAxisParamTypedef MPU6050_GetData(void);
uint8_t MPU6050_GetID(void);
#endif
