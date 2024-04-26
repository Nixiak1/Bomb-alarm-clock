#include "scan.h"
#include "sys.h"
#include "delay.h"
#include "key.h"
#include "buzzer.h"
#include "led.h"
#include "sys.h"
#include "usart.h"
int scan_Init_()
{
	static u8 key_up=1;//按键按松开标志		
	LED_Init_();
	if(key_up&&(PAin(1)==0||PAin(2)==0||PAin(3)==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(PAin(1)==0)
			return 1;
		else if(PAin(2)==0)
			return 2;
		else if(PAin(3)==0)
			return 3; 
	
	}
	else if(PA1==1&&PA2==1&&PA3==1)      
		key_up=1; 	     
	return 0;// 无按键按下
}

void key_press()
{
	int key=scan_Init_();
	int min=0,sec=0,num=0;
	while(1)
	{
		if(key==1)
		{
			min++;
			if(min>99)
				min=0;
			Display_min(min);
		}
		
		if(key==2)
		{
			sec++;
			if(sec>60)
				sec=0;
			Display_sec(sec);
		}
		
		if(key==3)
		{
			num=min*100+sec;
			TM1637_Display_INC(num);
			sec=0;
			min=0;
		}
		
	/*	if(key==4)
		{
			sec=0;
			min=0;
			Display_zero();
			buzzer_end();
		}*/
		key=scan_Init_();
	}

}
