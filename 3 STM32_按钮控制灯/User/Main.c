#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
uint8_t KeyNum; //global


int main(void)
{
	/*初始化*/
	LED_Init();	
	KEY_Init();
	/*初始化*/
	
/*功能*/
	while(1)
	{
		KeyNum = KEY_GetNum(); //检测KEY状态 -> 1: A1 ; 2: A2
		if(KeyNum==1) {	LED1_Turn(); } 
		
		if(KeyNum==2) { LED2_Turn(); } 
		
	}	
/*功能*/
		
}
