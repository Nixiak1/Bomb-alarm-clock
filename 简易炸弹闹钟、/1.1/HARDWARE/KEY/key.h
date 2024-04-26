#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//�������� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/06
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 


//ʹ�� λ�� ����
#define TM1637_CLK           PBout(6)
#define TM1637_DIO           PBout(7)
#define TM1637_READ_DIO      PBin(7)
  
//IO��������		   								0011���ģʽ   1000����������ģʽ
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
