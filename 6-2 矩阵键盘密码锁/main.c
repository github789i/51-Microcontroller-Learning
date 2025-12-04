#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char keyNum;
unsigned int password,count;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password");
	while(1)
	{
		keyNum = MatrixKey();
		if(keyNum)
		{
			if(keyNum<=10)
			{
				if(count<4)
				{
					password*=10;			//密码左移一位
					password+=keyNum%10;	//获取一位密码
				}
				count++;
				LCD_ShowNum(2,1,password, 4);
			}
			if(keyNum==11)//enter 
			{
				if(password==2345)//judge password
				{
					LCD_ShowString(1,12,"OK   ");
				}
				else
				{
					LCD_ShowString(1,12,"ERROR");
				}
				password=0;
				count=0;
				LCD_ShowNum(2,1,password,4);
			}
			if(keyNum==12)//cancel
			{
				password=0;
				count=0;
				LCD_ShowString(1,12,"ZERO ");
				LCD_ShowNum(2,1,password,4);
			}
		}
	}
}
