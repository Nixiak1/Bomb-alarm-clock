#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
	if(scan_Init()==1)	//WK_UP���� 
	{
		LED0=!LED0;
	}		 
	EXTI->PR=1<<4;  //���LINE0�ϵ��жϱ�־λ  
}

void EXTI_Init(void)
{
	KEY_Init();
	//Ex_NVIC_Config(GPIO_A,4,RTIR); 		//�����ش���
	//Ex_NVIC_Config(GPIO_C,5,FTIR);		//�½��ش���
	Ex_NVIC_Config(GPIO_A,4,FTIR);		//�½��ش���

	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    	//��ռ2�������ȼ�2����2

	
}
