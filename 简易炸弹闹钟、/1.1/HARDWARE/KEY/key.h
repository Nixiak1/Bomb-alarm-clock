#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
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


//使用 位带 操作
#define TM1637_CLK           PBout(6)
#define TM1637_DIO           PBout(7)
#define TM1637_READ_DIO      PBin(7)
  
//IO方向设置		   								0011输出模式   1000上下拉输入模式
#define TM1637_DIO_IN()      {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define TM1637_DIO_OUT()     {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
	 

void TM1637_Start( void );
void TM1637_Init( void );
void TM1637_Ack( void );
void TM1637_Stop( void );
void TM1637_WriteByte( u8 oneByte );
void TM1637_Display_INC( int num );
void Display_sec(int sec);
void Display_min(int min);
void Display_zero(void);


#endif
