#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "scan.h"
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
	if(PAin(4)==0)	
	{
		NVIC_SystemReset();//�����λ
	}	 
	EXTI->PR=1<<4;   
}

void EXTI_Init(void)
{
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0xFFF0FFFF;
	GPIOA->CRL|=0X00080000;
	GPIOA->ODR|=1<<4;					//PA4��������
	Ex_NVIC_Config(GPIO_A,4,FTIR);		//�½��ش���
	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    	//��ռ2�������ȼ�2����20

}
