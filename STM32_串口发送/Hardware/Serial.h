#ifndef __Serial_H
#define __Serial_H
#include <stdio.h>
void Serial_SendByte(uint8_t Byte);   					//发送一个字节
void Serial_SendArray(uint8_t *array,uint16_t Length);  //发送一个数组
void Serial_SendString(char *String); 					//发送一个字符串
void Serial_SendNum(uint32_t num, uint8_t Length); 		//发送无符号数
void Serial_Init(void); 								//初始化
void Serial_Printf(char *format, ...);
#endif
