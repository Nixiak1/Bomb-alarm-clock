#include "key.h"
#include "delay.h"
#include "scan.h"
#include "buzzer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//按键输入 驱动代码		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/06
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//按键初始化函数 
//PA0.15和PC5 设置成输入
void TM1637_Init( void )
{
	RCC->APB2ENR|=1<<3;	//使能B
	GPIOB->CRL&=0x00FFFFFF;
	GPIOB->CRL|=0x33000000;//PB6 7推挽输出
}


//起始位 CLK为高电平时，DIO由高变低
void TM1637_Start( void )
{
    TM1637_DIO_OUT();
    TM1637_CLK = 1;
    TM1637_DIO = 1;
    delay_us( 5 );
    TM1637_DIO = 0;
	TM1637_CLK = 1;
	delay_us(5);
}



void TM1637_Ack( void )
{
    TM1637_DIO_IN();
    TM1637_CLK = 0;
    delay_us( 5 );						//在第八个时钟下降沿之后延时 5us，开始判断 ACK 信号
    //while( TM1637_READ_DIO );			//等待应答位  这一行代码也可以不要 不影响实际使用效果 在使用软件仿真的时候需要屏蔽这句代码，否则程序就会卡在这里。
    TM1637_CLK = 1;
    delay_us( 5 );
    TM1637_CLK = 0;
	delay_us(5);
}



void TM1637_Stop( void )
{
    TM1637_DIO_OUT();
    TM1637_CLK = 1;
    TM1637_DIO = 0;
    delay_us( 5 );
    TM1637_DIO = 1;
	delay_us(5);
}


void TM1637_WriteByte( u8 oneByte )
{
    unsigned char i;
    TM1637_DIO_OUT();
    for( i = 0; i < 8; i++ )
    {
        TM1637_CLK = 0;
        if( oneByte & 0x01 )									//低位在前
        {
            TM1637_DIO = 1;
        }
        else
        {
            TM1637_DIO = 0;
        }
        delay_us( 3 );
        oneByte = oneByte >> 1;
        TM1637_CLK = 1;
        delay_us( 3 );
    }
}



void TM1637_Display_INC( int num)
{
	int disp_num[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
	//char DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
	int a1,a2,a3,a4;
	a1 = num / 1000;
    a2 = num / 100 % 10;
    a3 = num/ 10 % 10;
    a4 = num % 10;
	
	
	while((a1*10+a2)>=0)
	{
		TM1637_Start();
		TM1637_WriteByte( 0x44 );			//写数据到显示寄存器 
		TM1637_Ack();
		TM1637_Stop();
 
		TM1637_Start();
		TM1637_WriteByte( 0xC0 );			//地址命令设置 显示地址 00H
		TM1637_Ack();
		TM1637_WriteByte(disp_num[a1]);//发送数据    第一个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC1 );			//地址命令设置 显示地址 01H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a2]);//发送数据   第二个数码管
		TM1637_Ack();
		TM1637_Stop();
		
		TM1637_Start();
		TM1637_WriteByte( 0xC2 );			//地址命令设置 显示地址 02H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a3] );//发送数据   第三个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC3 );			//地址命令设置 显示地址 03H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a4] );//发送数据   第四个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0x88 | 0x07 );	//开显示，最大亮度-----调节脉冲宽度控制0---7  脉冲宽度14/16
		TM1637_Ack();
		TM1637_Stop();
		
		delay_ms(1000);
		
		a4--;
		if(a4==-1)
		{
			a3--;
			a4=9;
		}
		if((a3*10+a4)==-1)
		{
			a2--;
			if((a2==-1)&&(a1==1))
			{
				a1=0;
				a2=9;
			}
			a3=5;
			a4=9;
		}
	}
	Display_zero();
	buzzer_();
}


void Display_sec(int sec)
{
	int num[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
	int a3,a4;
	a3=sec/10;
	a4=sec%10;
	TM1637_Start();
	TM1637_WriteByte( 0x44 );			//写数据到显示寄存器 
	TM1637_Ack();
	TM1637_Stop();
 
	TM1637_Start();
	TM1637_WriteByte( 0xC2 );			//地址命令设置 显示地址 00H
	TM1637_Ack();
	TM1637_WriteByte(num[a3]);//发送数据    第一个数码管
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0xC3 );			//地址命令设置 显示地址 01H
	TM1637_Ack();
	TM1637_WriteByte( num[a4]);//发送数据   第二个数码管
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0x88 | 0x07 );	//开显示，最大亮度-----调节脉冲宽度控制0---7  脉冲宽度14/16
	TM1637_Ack();
	TM1637_Stop();

}

void Display_min(int min)
{
	int num[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 
	int a1,a2;
	a1=min/10;
	a2=min%10;
	TM1637_Start();
	TM1637_WriteByte( 0x44 );			//写数据到显示寄存器 
	TM1637_Ack();
	TM1637_Stop();
 
	TM1637_Start();
	TM1637_WriteByte( 0xC0 );			//地址命令设置 显示地址 00H
	TM1637_Ack();
	TM1637_WriteByte(num[a1]);//发送数据    第一个数码管
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0xC1 );			//地址命令设置 显示地址 01H
	TM1637_Ack();
	TM1637_WriteByte( num[a2]);//发送数据   第二个数码管
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0x88 | 0x07 );	//开显示，最大亮度-----调节脉冲宽度控制0---7  脉冲宽度14/16
	TM1637_Ack();
	TM1637_Stop();
}

void Display_zero()
{
		TM1637_Start();
		TM1637_WriteByte( 0x44 );			//写数据到显示寄存器 
		TM1637_Ack();
		TM1637_Stop();
 
		TM1637_Start();
		TM1637_WriteByte( 0xC0 );			//地址命令设置 显示地址 00H
		TM1637_Ack();
		TM1637_WriteByte(0x3f);//发送数据    第一个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC1 );			//地址命令设置 显示地址 01H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f);//发送数据   第二个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC2 );			//地址命令设置 显示地址 02H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f );//发送数据   第三个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC3 );			//地址命令设置 显示地址 03H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f);//发送数据   第四个数码管
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0x88 | 0x07 );	//开显示，最大亮度-----调节脉冲宽度控制0---7  脉冲宽度14/16
		TM1637_Ack();
		TM1637_Stop();
	

}
