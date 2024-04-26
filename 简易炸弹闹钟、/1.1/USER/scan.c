#include "scan.h"
#include "sys.h"
#include "delay.h"

int scan_Init()
{
	int i,j;
	int keys[3][3]={{0,0,0},{0,1,2},{0,3,4}};
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0x11100001;
	GPIOA->CRL|=0x00033880;		//PA1~2输入  3~4输出
	GPIOA->ODR|=1<<1;
	GPIOA->ODR|=1<<2;			//1~2 上拉输入
	PAout(3)=0;
	PAout(4)=0;
	if(PAin(1)==0||PAin(2)==0)
	{
		delay_ms(10);
		if(PAin(1)==0)
			i=1;
		else
			i=2;
	}
	else
		i=0;
	
	GPIOA->CRL&=0x11100001;
	GPIOA->CRL|=0x00088330;		//PA1~2输出  3~4输入
	GPIOA->ODR|=1<<3;
	GPIOA->ODR|=1<<4;			//3~4 上拉输入
	PAout(1)=0;
	PAout(2)=0;
	if(PAin(3)==0||PAin(4)==0)
	{
		delay_ms(10);
		if(PAin(3)==0)
			j=1;
		else
			j=2;
	}
	else
		j=0;
	
	return keys[i][j];
}
