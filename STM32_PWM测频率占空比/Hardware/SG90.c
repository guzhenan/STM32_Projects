#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void SG90_Init()
{
	PWM_Init();
}

/*舵机脉冲控制参数
	angle: 0 	map--------->500--->0.5ms
	angle: 45 	map--------->1000--->1ms
	angle: 90 	map--------->1500--->1.5ms
	angle: 135 	map--------->2000--->2ms
	angle: 180 	map--------->2500--->2.5ms
舵机脉冲控制参数*/
void SG90_SetAngle(float Angle)
{
	PWM_SetCompare1(Angle / 180 * 2000 + 500);  //调用PWM
}
