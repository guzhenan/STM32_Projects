#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"


int main(void)
{


/********************初始化********************/
	OLED_Init();
	MPU6050_Init();
	SixAxisParamTypedef SixAxisParamStruct;
	uint8_t ID=MPU6050_GetID();
	OLED_ShowString(4,1,"ID:");
	OLED_ShowHexNum(4,4,ID,2);
/********************初始化********************/
	

	
/********************功能********************/
	while(1)
	{
		SixAxisParamStruct=MPU6050_GetData();
		OLED_ShowSignedNum(1,1,SixAxisParamStruct.Acc_X,5);
		OLED_ShowSignedNum(2,1,SixAxisParamStruct.Acc_Y,5);
		OLED_ShowSignedNum(3,1,SixAxisParamStruct.Acc_Z,5);
		
		OLED_ShowSignedNum(1,9,SixAxisParamStruct.Gyro_X,5);
		OLED_ShowSignedNum(2,9,SixAxisParamStruct.Gyro_Y,5);
		OLED_ShowSignedNum(3,9,SixAxisParamStruct.Gyro_Z,5);
	}
	
	
/********************功能********************/
		
}
