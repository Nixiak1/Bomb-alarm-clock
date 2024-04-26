#include "buzzer.h"
#include "delay.h"
#include "sys.h"
#include "scan.h"
#include "key.h"
void buzzer_Init(void)
{

	
	RCC->APB2ENR|=1<<2;
	GPIOA->CRL&=0xFFFFFFF0;
	GPIOA->CRL|=0X00000003;



}

void buzzer_(void)
{
	int i;
	while(1)
	{
		for(i=0;i<3;i++)
		{
			buzzer=1;
			delay_ms(150);
			buzzer=0;
			delay_ms(150);
		}
		delay_ms(500);
	}
}

void buzzer_end()
{
	buzzer=0;
}
