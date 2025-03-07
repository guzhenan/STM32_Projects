#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "BEE.h"
#include "LightSensor.h"
int main(void)
{
	BEE_Init();
	LightSensor_Init();	
	while(1)
	{
		if(LightSensor_Get()==0) BEE_ON();
		else BEE_OFF();
	}
}
