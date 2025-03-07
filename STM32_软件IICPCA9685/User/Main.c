#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PCA9685.h"
#include "MyIIC.h"
#include "KEY.h"
uint8_t keyValue;
int main(void)
{


/********************初始化********************/
	OLED_Init();
	PCA9685_Init(50,0);
	KEY_Init();
/********************初始化********************/
	

	
/********************功能********************/
//	MyIIC_Start();
//	MyIIC_SendByte(0X80);
//	uint8_t ack=MyIIC_ReceiveACK(); 
//	OLED_ShowNum(1,1,ack,2);

//	PCA9685_setPWM(0,0,100);

	while(1)
	{
		keyValue=KEY_GetNum();
		if(keyValue==1) 
		{
			setAngle(0,60);
			Delay_s(5);
			setAngle(0,0);
		}

	}
	
	
/********************功能********************/
		
}
