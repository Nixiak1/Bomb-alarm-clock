#include "sys.h"   
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/05
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化


void LED_Init_(void)		//按键初始化  PA1~3
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟
	GPIOA->CRL&=0xFFFF000F;
	GPIOA->CRL|=0X00008880;//PA1~3上拉输入
	GPIOA->ODR|=1<<1;
	GPIOA->ODR|=1<<2;
	GPIOA->ODR|=1<<3;
}






