#ifndef __PCA9685_H
#define __PCA9685_H

#define PCA_Addr 0x80
#define PCA_Model 0x00
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define PCA_Pre 0xFE

void PCA9685_Init(float hz,uint8_t angle);

void PCA9685_Write_Reg(uint8_t Reg_Address,uint8_t Data);

uint8_t PCA9685_Read_Reg(uint8_t Reg_Address);

void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off);

void PCA9685_setFreq(float freq);

void setAngle(u8 num,u8 angle);
#endif
