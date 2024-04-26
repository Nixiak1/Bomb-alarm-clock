#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h" 
#include "buzzer.h"
#include "scan.h"
#include "exti.h"
//ALIENTEK Mini STM32�����巶������2
//��������ʵ��		   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
void SystemInit (void)
{
	
}
int main(void)
{		   
	int key;
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	delay_init(72);	     	//��ʱ��ʼ�� 
	TM1637_Init();
	buzzer_Init();
	EXTI_Init();
	uart_init(72,9600);	 //���ڳ�ʼ��Ϊ9600
	Display_zero();
	while(1)
	{
		key_press();
		//key=scan_Init_();
		//printf("%d",key);
		//delay_ms(1000);
	}

}

























