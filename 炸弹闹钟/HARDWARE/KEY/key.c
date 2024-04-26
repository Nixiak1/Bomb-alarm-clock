#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//KEY1,2,3,4,5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4


}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下

u8 KEY_Scan(u8 mode)
{	 
	if(KEY0==1||KEY1==1||KEY2==1||KEY3==1||KEY4==1)
	{
		
		delay_ms(100);
		if(KEY0==1) {
				return 1;
		}
		else if(KEY1==1) {
				return 2;
		}
		else if(KEY2==1){
				return 3;
		}
		else if(KEY3==1){
				return 4;
		}
		else if(KEY4==1){
				return 5;
		}

	}	
	
	
	else if(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0)
	{
		return 0;
	}
//	delay_ms(1000);

}
