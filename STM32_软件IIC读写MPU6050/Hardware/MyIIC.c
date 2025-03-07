#include "stm32f10x.h"                  // Device header
#include "DELAY.h"

#define SCL_PORT GPIOB
#define SCL_PIN GPIO_Pin_10

#define SDA_PORT GPIOB
#define SDA_PIN GPIO_Pin_11

void MyIIC_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
/********************GPIO初始化********************/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_OD;      //开漏输出模式
	GPIO_InitStruct.GPIO_Pin=SCL_PIN|SDA_PIN; 
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,SCL_PIN|SDA_PIN);    //置高电平
/********************GPIO初始化********************/


}

void MyIIC_W_SCL(uint8_t BitValue)  //写SCL电平状态
{
	GPIO_WriteBit(SCL_PORT,SCL_PIN,(BitAction)BitValue);
	Delay_us(10);
}

void MyIIC_W_SDA(uint8_t BitValue) //写SDA电平状态
{
	GPIO_WriteBit(SDA_PORT,SDA_PIN,(BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyIIC_R_SDA(void)         //读SDA数据
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(SDA_PORT,SDA_PIN);
	Delay_us(10);
	return BitValue;
}

void MyIIC_Start(void)  //起始条件：SCL高电平期间，SDA从高电平切换到低电平
{
	/*初始时先都置1*/
	MyIIC_W_SDA(1);
	MyIIC_W_SCL(1);
	/*初始时先都置1*/
	
	/*先拉低SDA 再拉低SCL 产生IIC开始信号*/
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(0);
	/*先拉低SDA 再拉低SCL 产生IIC开始信号*/
}

void MyIIC_Stop(void)  //结束条件：SCL高电平期间，SDA从低电平切换到高电平
{
	/*初始时先都置0*/
	MyIIC_W_SDA(0);
	/*初始时先都置0*/
	
	/*先释放SCL 再释放SDA 产生IIC结束信号*/
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(1);
	/*先释放SCL 再释放SDA 产生IIC结束信号*/
}

void MyIIC_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyIIC_W_SDA(Byte&(0x80)>>i); //从高位开始 每次循环取1位  主机依次将数据位放到SDA线上
		MyIIC_W_SCL(1);   			 //SCL高电平时 从机读取一位数据且SDA不允许有数据变化
		MyIIC_W_SCL(0);				 //SCL低电平时 主机写一位数据
	}

}	

uint8_t MyIIC_ReceiveByte(void) //接收一个字节：SCL低电平期间，从机将数据位依次放到SDA线上（高位先行），然后释放SCL，主机将在SCL高电平期间读取数据位
{
	uint8_t Byte=0x00;
	MyIIC_W_SDA(1);
	for(uint8_t i=0;i<8;i++)
	{
		MyIIC_W_SCL(1);
		if(MyIIC_R_SDA()==1) { Byte |= (0x80>>i); }  //依次从高位到低位读取并赋值给Byte
		MyIIC_W_SCL(0); 
	}
	
	
	return Byte;
}

void MyIIC_SendACK(uint8_t ACKBit)
{
		MyIIC_W_SDA(ACKBit); 		//发送一位应答位
		MyIIC_W_SCL(1);   			//SCL高电平时 从机读取一位数据且SDA不允许有数据变化
		MyIIC_W_SCL(0);				//SCL低电平时 主机写一位数据
}	

uint8_t MyIIC_ReceiveACK(void) //接收一位应答位
{
	uint8_t ACKBit;
	MyIIC_W_SDA(1); //主机释放SDA 防止从机干扰 同时把应答位放到SDA上
	MyIIC_W_SCL(1); //SCL高电平主机读取应答位
	ACKBit=MyIIC_R_SDA(); 
	MyIIC_W_SCL(0); //进入下一个时序单元
	return ACKBit;
}
