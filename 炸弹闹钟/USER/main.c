#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "TM1637.h"
#include "beep.h"

/************************************************
 ALIENTEK战舰STM32开发板实验8
 定时器中断实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

void time_out(int a,int b,int c,int d);
 int main(void)
 {		
	int a=0,b=0,c=0,d=0;
	 int key=0;
	 int Flag = 0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600); //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	TM1637_Init();
	 BEEP_Init(); //蜂鸣器初始化
	
	KEY_Init();  //按键初始化
	Countdown_Control(0,a);
	Countdown_Control(1,b);
	Countdown_Control(2,c);
	Countdown_Control(3,d);
	TM1637_SetBrightness( 6 );	
		PBout(8)=1;
	 	PBout(10)=1;
		PBout(11)=0;

    while ( 1 )
    {
			
		if(Flag)
		{
				BEEP = 0;
				LED1 = 1;
				LED0 = 0;
		}
	
		key = KEY_Scan(0);
		printf("%d\n\t",key);
		
		switch (key)
		{
			case 1:
			{
				//printf("1\n\t");
				
				if(a==6)
				{
					a=0;
				}
				else
				{
					if(a==5)
					{
						a++;
						b=0;
						c=0;
						d=0;

					}
					else
						a++;
				}
					Countdown_Control(0,a);
	Countdown_Control(1,b);
	Countdown_Control(2,c);
	Countdown_Control(3,d);

				break;
			}
			case 2:
			{
				if(b==9)
				{
					b=0;
				}
				else
					b++;
					Countdown_Control(0,a);
	Countdown_Control(1,b);
	Countdown_Control(2,c);
	Countdown_Control(3,d);
				break;
			}
			case 3:
			{
				if(c==6)
					c=0;
				else
				{
					if(c==5)
					{
						c++;
						d=0;
					}
					else
						c++;
				}
				
			Countdown_Control(0,a);
	Countdown_Control(1,b);
	Countdown_Control(2,c);
	Countdown_Control(3,d);
				break;

			

			}
			case 4:
			{
				if(d==9||c==6)
					d=0;
				else
					d++;

					Countdown_Control(0,a);
	Countdown_Control(1,b);
	Countdown_Control(2,c);
	Countdown_Control(3,d);
				break;
			}
			case 5:
			{
				//delay_ms(1000);
				TIM3_Int_Init(9999,7199);//10Khz的计数频率，计数到10000为1000ms  
				time_out(a,b,c,d);
				
				 Flag = 1;
					break;
				

				break;
			}
		}
		
       
        TM1637_SetBrightness( 6 );					//设置亮度等级 0---7

    }

 
}	 


void time_out(int a,int b,int c,int d)
{
	int sum = 0;
	int keys = 0;
		sum = (c*10+d)%5+1;
	while((!(a==0&&b==0&&c==0&&d==0)))
	{
		
		Countdown_Control(0,a);
		Countdown_Control(1,b);
		Countdown_Control(2,c);
		Countdown_Control(3,d);	
		if(a>0||b>0||c>0||d>0)
		{
			if(d==0)
				{
					d=9;
					if(c!=0)
						c--;
					else
					{
						c=5;
						if(b!=0)
							b--;
						else
							{
								b=9;
								if(a!=0)
									a--;
								else
									a=0;
							}
					}						
				}
			else
					d--;
		}
	
	
		delay_ms(1000);
	

		
		
	}
		Countdown_Control(0,a);
		Countdown_Control(1,b);
		Countdown_Control(2,c);
		Countdown_Control(3,d);	
	

}

