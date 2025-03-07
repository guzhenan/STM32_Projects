#include "stm32f10x.h"                  // Device header

void MyDMA_Init(uint32_t DMA_PeripheralBaseAddr,uint32_t DMA_MemoryBaseAddr)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);			//开启AHB时钟
	DMA_InitTypeDef DMA_InitStruct;

	DMA_InitStruct.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;		 //存储器地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //每次传输数据大小
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;		 //是否自增
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr; //外设地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;//每次接收数据大小
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;	//是否自增
	
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_BufferSize = DMA_MemoryDataSize_Byte;       //DMA缓冲大小
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;				   //外设是源地址还是目的
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;					   //硬件触发还是软件触发
	 
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	DMA_Cmd(DMA1_Channel1 ,DISABLE);
	
	
}

void MyDMA_Eable(void)
{
	DMA_SetCurrDataCounter(DMA1_Channel1, 4);      //传输计数值 一次传输多少个数据 必须在DMA关闭下设置
	DMA_Cmd(DMA1_Channel1 ,ENABLE);					 //开启DMA传送
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);  //等待完成传输
	DMA_ClearFlag(DMA1_FLAG_TC1);					 //清除标志位
	DMA_Cmd(DMA1_Channel1 ,DISABLE);
}
