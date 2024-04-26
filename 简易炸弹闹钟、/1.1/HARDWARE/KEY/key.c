#include "key.h"
#include "delay.h"
#include "scan.h"
#include "buzzer.h"
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
 	    
//������ʼ������ 
//PA0.15��PC5 ���ó�����
void TM1637_Init( void )
{
	RCC->APB2ENR|=1<<3;	//ʹ��B
	GPIOB->CRL&=0x00FFFFFF;
	GPIOB->CRL|=0x33000000;//PB6 7�������
}


//��ʼλ CLKΪ�ߵ�ƽʱ��DIO�ɸ߱��
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
    delay_us( 5 );						//�ڵڰ˸�ʱ���½���֮����ʱ 5us����ʼ�ж� ACK �ź�
    //while( TM1637_READ_DIO );			//�ȴ�Ӧ��λ  ��һ�д���Ҳ���Բ�Ҫ ��Ӱ��ʵ��ʹ��Ч�� ��ʹ����������ʱ����Ҫ���������룬�������ͻῨ�����
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
        if( oneByte & 0x01 )									//��λ��ǰ
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
		TM1637_WriteByte( 0x44 );			//д���ݵ���ʾ�Ĵ��� 
		TM1637_Ack();
		TM1637_Stop();
 
		TM1637_Start();
		TM1637_WriteByte( 0xC0 );			//��ַ�������� ��ʾ��ַ 00H
		TM1637_Ack();
		TM1637_WriteByte(disp_num[a1]);//��������    ��һ�������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC1 );			//��ַ�������� ��ʾ��ַ 01H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a2]);//��������   �ڶ��������
		TM1637_Ack();
		TM1637_Stop();
		
		TM1637_Start();
		TM1637_WriteByte( 0xC2 );			//��ַ�������� ��ʾ��ַ 02H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a3] );//��������   �����������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC3 );			//��ַ�������� ��ʾ��ַ 03H
		TM1637_Ack();
		TM1637_WriteByte( disp_num[a4] );//��������   ���ĸ������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0x88 | 0x07 );	//����ʾ���������-----���������ȿ���0---7  ������14/16
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
	TM1637_WriteByte( 0x44 );			//д���ݵ���ʾ�Ĵ��� 
	TM1637_Ack();
	TM1637_Stop();
 
	TM1637_Start();
	TM1637_WriteByte( 0xC2 );			//��ַ�������� ��ʾ��ַ 00H
	TM1637_Ack();
	TM1637_WriteByte(num[a3]);//��������    ��һ�������
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0xC3 );			//��ַ�������� ��ʾ��ַ 01H
	TM1637_Ack();
	TM1637_WriteByte( num[a4]);//��������   �ڶ��������
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0x88 | 0x07 );	//����ʾ���������-----���������ȿ���0---7  ������14/16
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
	TM1637_WriteByte( 0x44 );			//д���ݵ���ʾ�Ĵ��� 
	TM1637_Ack();
	TM1637_Stop();
 
	TM1637_Start();
	TM1637_WriteByte( 0xC0 );			//��ַ�������� ��ʾ��ַ 00H
	TM1637_Ack();
	TM1637_WriteByte(num[a1]);//��������    ��һ�������
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0xC1 );			//��ַ�������� ��ʾ��ַ 01H
	TM1637_Ack();
	TM1637_WriteByte( num[a2]);//��������   �ڶ��������
	TM1637_Ack();
	TM1637_Stop();
	
	TM1637_Start();
	TM1637_WriteByte( 0x88 | 0x07 );	//����ʾ���������-----���������ȿ���0---7  ������14/16
	TM1637_Ack();
	TM1637_Stop();
}

void Display_zero()
{
		TM1637_Start();
		TM1637_WriteByte( 0x44 );			//д���ݵ���ʾ�Ĵ��� 
		TM1637_Ack();
		TM1637_Stop();
 
		TM1637_Start();
		TM1637_WriteByte( 0xC0 );			//��ַ�������� ��ʾ��ַ 00H
		TM1637_Ack();
		TM1637_WriteByte(0x3f);//��������    ��һ�������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC1 );			//��ַ�������� ��ʾ��ַ 01H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f);//��������   �ڶ��������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC2 );			//��ַ�������� ��ʾ��ַ 02H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f );//��������   �����������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0xC3 );			//��ַ�������� ��ʾ��ַ 03H
		TM1637_Ack();
		TM1637_WriteByte( 0x3f);//��������   ���ĸ������
		TM1637_Ack();
		TM1637_Stop();
	
		TM1637_Start();
		TM1637_WriteByte( 0x88 | 0x07 );	//����ʾ���������-----���������ȿ���0---7  ������14/16
		TM1637_Ack();
		TM1637_Stop();
	

}
