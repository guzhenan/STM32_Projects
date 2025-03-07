#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "OLED.h"
uint8_t Serial_RXFlag;		 //判断数据准备就绪的标志位


char Serial_RxPakage[100];  //存放接收的数据包
char Serial_TxPakage[100];  //存放发送的数据包
	 


void Serial_Init(void)
{
/****************************************时钟配置****************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
/****************************************时钟配置****************************************/

/****************************************GPIO配置****************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP; //模拟推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;  //上拉输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/****************************************GPIO配置****************************************/

/****************************************串口配置****************************************/
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;  //波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //是否选择硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Tx | USART_Mode_Rx; //选择是  发送模式  |  接受模式
	USART_InitStruct.USART_Parity=USART_Parity_No;  //选择是否有校验位 可选无
	USART_InitStruct.USART_StopBits=USART_StopBits_1;   //选择停止位的位数
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;  //选择每次发送或接收的数据大小
	USART_Init(USART1,  &USART_InitStruct);
/****************************************串口配置****************************************/

/****************************************串口中断配置****************************************/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开启标志位到NVIC的输出
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
/****************************************串口中断配置****************************************/

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


uint8_t Serial_ReceiveByte(void)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET);  //接受寄存器不空置1 读出数据
	uint8_t RData = USART_ReceiveData(USART1);
	return RData;
	
}


/****************************************读后自动清除功能****************************************/
uint8_t Serial_GetRxFlag(void)
{
	Serial_RXFlag = USART_GetFlagStatus(USART1, USART_FLAG_RXNE);
	if(Serial_RXFlag==1)
	{
		Serial_RXFlag=0;
		return 1;
	}
	return 0;
}
/****************************************读后自动清除功能****************************************/


/****************************************发送数据报****************************************/
void Serial_SendPakage(void)
{
	Serial_SendByte('@');
	Serial_SendString(Serial_TxPakage);
	Serial_SendByte('\r');
	Serial_SendByte('\n');
}
/****************************************发送数据报****************************************/




/****************************************中断执行功能****************************************/
void USART1_IRQHandler(void)
{
	static uint8_t Serial_RxCounter;	 //数据偏移的位置 静态变量下一次进函数值不变
	static uint8_t Serial_TxState;		//状态
	/*	表示接收数据时处于什么状态  value_range[0,2]
	0----等待包头
	1----接收数据
	2----等待包尾
*/
	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET){
		
		uint8_t RxDATA=Serial_ReceiveByte();                  //存放每次接收的数据
		
		if(RxDATA == '@' && Serial_TxState==0)
		{
			Serial_TxState=1;		  //切换成接收数据的状态
			Serial_RxCounter = 0;
		}
		
		else if(Serial_TxState==1)
		{
			
			if(RxDATA=='\r')
			{	
				Serial_TxState = 2;	   
			}
			else
			{
				Serial_RxPakage[Serial_RxCounter++] = RxDATA;
			}
		}
		
		else if(Serial_TxState == 2)
		{
			if(RxDATA=='\n')
			{
				Serial_RxPakage[Serial_RxCounter] = '\0';   //添加字符串结束标志位
				Serial_RXFlag = 1;	  //置接收就绪信号为1
				Serial_TxState = 0;  //切换成等待包头的状态
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);   //中断标志位清0
	}
	
}
/****************************************中断执行功能****************************************/


