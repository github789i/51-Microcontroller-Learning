#include <REGX52.H>
#include "Timer0.h"
#include "key.h"
#include <INTRINS.H>


////STC-ICP生成
//void Timer0Init(void)		//1毫秒@12.000MHz
//{
////	AUXR &= 0x7F;		//定时器时钟12T模式
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0x18;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//	
//	//中断结构 chapt 6.1
//	ET0=1;
//	EA=1;
//	PT0=0;
//}



//void Timer0_Init()
//{
//	//TMOD 寄存器 Chapt 7.1.1 不可位寻址，只能整体指定
//	//TMOD=0x01; //0000 0001
//	TMOD=TMOD&0xF0;	//TMOD低四位清零，高四位保持不变
//	TMOD=TMOD|0x01;	//TMOD低四位置一，高四位保持不变
//	
//	//TCON 寄存器
//	TF0=0;
//	TR0=1;
//	// 相关寄存器 65535us Chapt 7.1.1
//	TH0=64535/256; //高8位
//	TL0=64535%256;	// 低8位
//	
//	//中断结构 chapt 6.1
//	ET0=1;
//	EA=1;
//	PT0=0;
//}

unsigned char keyNum,LEDMode;

void main()
{
//	Timer0_Init();
	P2=0xFE;
	Timer0Init();
	while(1)
	{
		keyNum=Key();
		if(keyNum)
		{
			if(keyNum==1)
			{
				LEDMode++;
				if(LEDMode>=2)LEDMode=0;
			}
		}
	}
}

unsigned int T0Count;
void Timer0_Routine() interrupt 1
{
//	TH0=64535/256; //高8位
//	TL0=64535%256;	// 低8位
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	
	T0Count++;
	if(T0Count>=1000) //每隔一秒闪烁
	{
		T0Count=0;
//		P2_0=~P2_0;
		if(LEDMode==0)
			P2=_crol_(P2,1);
		if(LEDMode==1)
			P2=_cror_(P2,1);
	}
}