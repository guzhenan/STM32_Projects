#ifndef __AD_H
#define __AD_H
extern uint16_t AD_Value[4]; //外部可调用数组
void AD_Init(void);
uint16_t AD_GetValue(void);  //读取ADC数据寄存器
#endif