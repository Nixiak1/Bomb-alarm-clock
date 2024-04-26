#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h" 
#include "buzzer.h"
#include "scan.h"
#include "exti.h"
//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
void SystemInit (void)
{
	
}
int main(void)
{		   
	int key;
	Stm32_Clock_Init(9); 	//系统时钟设置
	delay_init(72);	     	//延时初始化 
	TM1637_Init();
	buzzer_Init();
	EXTI_Init();
	uart_init(72,9600);	 //串口初始化为9600
	Display_zero();
	while(1)
	{
		key_press();
		//key=scan_Init_();
		//printf("%d",key);
		//delay_ms(1000);
	}

}

























