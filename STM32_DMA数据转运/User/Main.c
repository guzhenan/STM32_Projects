#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"
uint8_t A[] = {0x01,0x02,0x03,0x04};
uint8_t B[] = {0x00,0x00,0x00,0x00};

//被const修饰数据只能读不能写 所以存在Flash里

int main(void)
{


/********************初始化********************/
	OLED_Init();
	MyDMA_Init( (uint32_t)&B, (uint32_t)&A);
/********************初始化********************/

	
	
/********************功能********************/

	while(1)
	{
	MyDMA_Eable();
	OLED_ShowString(1,1,"A:");
	OLED_ShowHexNum(1,3,(uint32_t)&A,8);
	OLED_ShowHexNum(2,1,A[0],2);
	OLED_ShowHexNum(2,4,A[1],2);
	OLED_ShowHexNum(2,7,A[2],2);
	OLED_ShowHexNum(2,10,A[3],2);
	Delay_ms(1000);
	OLED_ShowString(3,1,"B:");
	OLED_ShowHexNum(3,3,(uint32_t)&B,8);
	OLED_ShowHexNum(4,1,B[0],2);
	OLED_ShowHexNum(4,4,B[1],2);
	OLED_ShowHexNum(4,7,B[2],2);
	OLED_ShowHexNum(4,10,B[3],2);
	for(int i=0;i<4;i++)
		A[i]++;
	
	
	}

/********************功能********************/
		
}
