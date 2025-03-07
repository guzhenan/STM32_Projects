#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
void Serial_Init(void)
{
/****************************************时钟配置****************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
/****************************************时钟配置****************************************/

/****************************************GPIO配置****************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/****************************************GPIO配置****************************************/

/****************************************串口配置****************************************/
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;  //波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //是否选择硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Tx; //选择是  发送模式  |  接受模式
	USART_InitStruct.USART_Parity=USART_Parity_No;  //选择是否有校验位 可选无
	USART_InitStruct.USART_StopBits=USART_StopBits_1;   //选择停止位的位数
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;  //选择每次发送的数据大小
	USART_Init(USART1,  &USART_InitStruct);
/****************************************串口配置****************************************/

/****************************************串口开关****************************************/
	USART_Cmd(USART1, ENABLE);
/****************************************串口开关****************************************/
}

void Serial_SendByte(uint8_t Byte)   //发送一个字节
{	
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	
}

void Serial_SendArray(uint8_t *array,uint16_t Length) //发送一个数组
{
	for(uint16_t i=0; i<Length ; i++)
	{
		Serial_SendByte(array[i]);
	}
	
}	

void Serial_SendString(char *String) //发送一个字符串
{
	for(uint16_t i=0; String[i]!='\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x , uint32_t y)  //x的y次方
{
	uint32_t result=1;
	while(y--)
	{
		result*=x;
	}
	return result;
}

void Serial_SendNum(uint32_t num, uint8_t Length) //发送无符号数
{
	for(uint32_t i=0;i<Length;i++)
	{
		Serial_SendByte( num / Serial_Pow(10, Length - i - 1) % 10 + '0' );
	}
}

/********************重写printf********************/
int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}
/********************重写printf********************/

/********************多个串口打印********************/
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);

}
/********************多个串口打印********************/
