#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(scan_Init()==1)	//WK_UP按键 
	{
		LED0=!LED0;
	}		 
	EXTI->PR=1<<4;  //清除LINE0上的中断标志位  
}

void EXTI_Init(void)
{
	KEY_Init();
	//Ex_NVIC_Config(GPIO_A,4,RTIR); 		//上升沿触发
	//Ex_NVIC_Config(GPIO_C,5,FTIR);		//下降沿触发
	Ex_NVIC_Config(GPIO_A,4,FTIR);		//下降沿触发

	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    	//抢占2，子优先级2，组2

	
}
