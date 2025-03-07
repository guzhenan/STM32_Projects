#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM1_SetCompare1(uint16_t compare);
void PWM1_SetCompare2(uint16_t compare);
void PWM1_SetCompare3(uint16_t compare);
void PWM1_SetCompare4(uint16_t compare);

void PWM2_SetCompare1(uint16_t compare);
void PWM2_SetCompare2(uint16_t compare);
void PWM2_SetCompare3(uint16_t compare);
void PWM2_SetCompare4(uint16_t compare);
#endif
