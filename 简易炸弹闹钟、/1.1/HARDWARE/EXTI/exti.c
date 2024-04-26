#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "scan.h"
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(PAin(4)==0)	
	{
		NVIC_SystemReset();//软件复位
	}	 
	EXTI->PR=1<<4;   
}

void EXTI_Init(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0xFFF0FFFF;
	GPIOA->CRL|=0X00080000;
	GPIOA->ODR|=1<<4;					//PA4上拉输入
	Ex_NVIC_Config(GPIO_A,4,FTIR);		//下降沿触发
	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    	//抢占2，子优先级2，组20

}
