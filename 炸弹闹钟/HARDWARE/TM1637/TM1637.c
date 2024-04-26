#include "TM1637.h"
#include "delay.h"

unsigned char tab[] =
{
    0x3F,/*0*/
    0x06,/*1*/
    0x5B,/*2*/
    0x4F,/*3*/
    0x66,/*4*/
    0x6D,/*5*/
    0x7D,/*6*/
    0x07,/*7*/
    0x7F,/*8*/
    0x6F,/*9*/
    0x77,/*10 A*/
    0x7C,/*11 b*/
    0x58,/*12 c*/
    0x5E,/*13 d*/
    0x79,/*14 E*/
    0x71,/*15 F*/
    0x76,/*16 H*/
    0x38,/*17 L*/
    0x54,/*18 n*/
    0x73,/*19 P*/
    0x3E,/*20 U*/
    0x00,/*21 ����*/
};

// ���λ����Ϊ1ʱ��ʾ ������ϵ�":" ����
unsigned char disp_num[] = {0x3F, 0x06 | 0x80, 0x5B, 0x4F, 0x66, 0x6D};			//���6�������Ҫ��ʾ������

//�˿ڳ�ʼ��
void TM1637_Init( void )
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( TM1637_CLK_GPIO_CLK | TM1637_DIO_GPIO_CLK, ENABLE );

    GPIO_InitStructure.GPIO_Pin = TM1637_CLK_GPIO_PIN | TM1637_DIO_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( TM1637_CLK_GPIO_PORT, &GPIO_InitStructure );
}

//��ʼλ CLKΪ�ߵ�ƽʱ��DIO�ɸ߱��
void TM1637_Start( void )
{
    TM1637_DIO_OUT();
    TM1637_CLK = 1;
    TM1637_DIO = 1;
    delay_us( 2 );
    TM1637_DIO = 0;
}

//�ȴ�Ӧ�� ����������ȷʱ���ڵڰ˸�ʱ���½��أ�оƬ�ڲ������һ��ACK�źţ���DIO�ܽ����ͣ��ڵھŸ�ʱ�ӽ���֮���ͷ�DIO���ߡ�
void TM1637_Ack( void )
{
    TM1637_DIO_IN();
    TM1637_CLK = 0;
    delay_us( 5 );													//�ڵڰ˸�ʱ���½���֮����ʱ 5us����ʼ�ж� ACK �ź�
    while( TM1637_READ_DIO );								//�ȴ�Ӧ��λ  ��һ�д���Ҳ���Բ�Ҫ ��Ӱ��ʵ��ʹ��Ч�� ��ʹ����������ʱ����Ҫ���������룬�������ͻῨ�����
    TM1637_CLK = 1;
    delay_us( 2 );
    TM1637_CLK = 0;
}

//ֹͣλ CLKΪ�ߵ�ƽʱ��DIO�ɵͱ��
void TM1637_Stop( void )
{
    TM1637_DIO_OUT();
    TM1637_CLK = 0;
    delay_us( 2 );
    TM1637_DIO = 0;
    delay_us( 2 );
    TM1637_CLK = 1;
    delay_us( 2 );
    TM1637_DIO = 1;
}
//����������CLK�ĵ͵�ƽ�仯����CLK�ĸߵ�ƽ�����䡣
//ÿ����һ���ֽڣ�оƬ�ڲ��ڵڰ˸�ʱ���½��ز���һ��ACK
// дһ���ֽ�
void TM1637_WriteByte( unsigned char oneByte )
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

//д��ʾ�Ĵ���  ��ַ����
void TM1637_Display_INC( void )
{
    unsigned char i;
    TM1637_Start();
    TM1637_WriteByte( 0x40 );									//д���ݵ���ʾ�Ĵ��� 40H ��ַ�Զ���1 ģʽ,44H �̶���ַģʽ,����������Լ�1ģʽ
    TM1637_Ack();
    TM1637_Stop();
    TM1637_Start();
    TM1637_WriteByte( 0xC0 );									//��ַ�������� ��ʾ��ַ 00H
    TM1637_Ack();

    for( i = 0; i < 6; i++ )									//��ַ�Լӣ�����ÿ�ζ�д��ַ
    {
        TM1637_WriteByte( disp_num[i] );			//��������   disp_num[]�д洢6�������Ҫ��ʾ������
        TM1637_Ack();
    }
    TM1637_Stop();
#if 0
    TM1637_Start();
    TM1637_WriteByte( 0x88 | 0x07 );					//����ʾ���������-----���������ȿ���0---7  ������14/16
    TM1637_Ack();
    TM1637_Stop();
#endif
}

//д��ʾ�Ĵ���  ��ַ������
// add ����ܵĵ�ַ 0--5
// value Ҫ��ʾ������
void TM1637_Display_NoINC( unsigned char add, unsigned char value )
{
   // unsigned char i;
    TM1637_Start();
    TM1637_WriteByte( 0x44 );								//д���ݵ���ʾ�Ĵ��� 40H ��ַ�Զ���1 ģʽ,44H �̶���ַģʽ,����������Լ�1ģʽ
    TM1637_Ack();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte( 0xC0 | add );					//��ַ�������� ��ʾ��ַ C0H---C5H
    TM1637_Ack();

    TM1637_WriteByte( value );			 				//��������   value�洢Ҫ��ʾ������
    TM1637_Ack();
    TM1637_Stop();
#if 0
    TM1637_Start();
    TM1637_WriteByte( 0x88 | 0x07 );							//����ʾ���������-----���������ȿ���0---7  ������14/16
    TM1637_Ack();
    TM1637_Stop();
#endif
}

// level : �������ȵȼ�  0---7
void TM1637_SetBrightness( unsigned char level )
{
    TM1637_Start();
    TM1637_WriteByte( 0x88 | level );							//����ʾ���������-----���������ȿ���0---7  ������14/16
    TM1637_Ack();
    TM1637_Stop();
}




//������  ������ʱ��ʱ��Ƶ��ӦС�� 250K���ȶ���λ�������λ��
unsigned char TM1637_ScanKey( void )
{
    unsigned char reKey, i;
    TM1637_Start();
    TM1637_WriteByte( 0x42 );						//����ɨ����
    TM1637_Ack();
    TM1637_DIO = 1;											//�ڶ�����֮ǰ����������
    TM1637_DIO_IN();
    for( i = 0; i < 8; i++ )						//�ӵ�λ��ʼ��
    {
        TM1637_CLK = 0;
        reKey = reKey >> 1;
        delay_us( 30 );
        TM1637_CLK = 1;
        if( TM1637_READ_DIO )
        {
            reKey = reKey | 0x80;
        }
        else
        {
            reKey = reKey | 0x00;
        }
        delay_us( 30 );
    }
    TM1637_Ack();
    TM1637_Stop();
    return( reKey );
}


//�������������������ݵ�λ��ǰ��λ�ں�
unsigned char TM1637_KeyProcess( void )
{
    unsigned char temp;
    unsigned char keyNum = 0;
    temp = TM1637_ScanKey();                                 //��ȡ��������ֵ
    if( temp != 0xff )
    {
        switch( temp )
        {
        case 0xf7 :							//K1��SG1��Ӧ��������
            keyNum = 1;
            break;
        case 0xf6 :						 	//K1��SG2��Ӧ��������
            keyNum = 2;
            break;
        case 0xf5 :							//K1��SG3��Ӧ��������
            keyNum = 3;
            break;
        case 0xf4 :							//K1��SG4��Ӧ��������
            keyNum = 4;
            break;
        case 0xf3 :							//K1��SG5��Ӧ��������
            keyNum = 5;
            break;
        case 0xf2 :						 	//K1��SG6��Ӧ��������
            keyNum = 6;
            break;
        case 0xf1 :							//K1��SG7��Ӧ��������
            keyNum = 7;
            break;
        case 0xf0 :							//K1��SG8��Ӧ��������
            keyNum = 8;
            break;

        case 0xef :						 	//K2��SG1��Ӧ��������
            keyNum = 9;
            break;
        case 0xee :							//K2��SG2��Ӧ��������
            keyNum = 10;
            break;
        case 0xed :							//K2��SG3��Ӧ��������
            keyNum = 11;
            break;
        case 0xec :						 	//K2��SG4��Ӧ��������
            keyNum = 12;
            break;
        case 0xeb :							//K2��SG5��Ӧ��������
            keyNum = 13;
            break;
        case 0xea :							//K2��SG6��Ӧ��������
            keyNum = 14;
            break;
        case 0xe9 :							//K2��SG7��Ӧ��������
            keyNum = 15;
            break;
        case 0xe8 :							//K2��SG8��Ӧ��������
            keyNum = 16;
            break;
        default   :
            keyNum = 0;
            break;
        }
    }
    return keyNum;
}

void Countdown_Control(int m,int n)//m��������ܵ�λ n�����������ʾ��ַ�Ĳ���
{
	if(m==1)
	{
		switch (n)
			{
				case 1:
					TM1637_Display_NoINC( m,tab[1]| 0x80 );
					break;
				case 2:
					TM1637_Display_NoINC( m,tab[2]| 0x80 );
					break;
				case 3:
					TM1637_Display_NoINC( m,tab[3] | 0x80);
					break;
				case 4:
					TM1637_Display_NoINC( m,tab[4]| 0x80 );
					break;
				case 5:
					TM1637_Display_NoINC( m,tab[5] | 0x80);
					break;
				case 6:
					TM1637_Display_NoINC( m,tab[6]| 0x80 );
					break;
				case 7:
					TM1637_Display_NoINC( m,tab[7] | 0x80);
					break;
				case 8:
					TM1637_Display_NoINC( m,tab[8]| 0x80 );
					break;
				case 9:
					TM1637_Display_NoINC( m,tab[9]| 0x80 );
					break;
				case 0:
					TM1637_Display_NoINC( m,tab[0]| 0x80 );
					break;
			}
	
	}
	else
		{
			switch (n)
			{
				case 1:
					TM1637_Display_NoINC( m,tab[1] );
					break;
				case 2:
					TM1637_Display_NoINC( m,tab[2] );
					break;
				case 3:
					TM1637_Display_NoINC( m,tab[3] );
					break;
				case 4:
					TM1637_Display_NoINC( m,tab[4] );
					break;
				case 5:
					TM1637_Display_NoINC( m,tab[5] );
					break;
				case 6:
					TM1637_Display_NoINC( m,tab[6] );
					break;
				case 7:
					TM1637_Display_NoINC( m,tab[7] );
					break;
				case 8:
					TM1637_Display_NoINC( m,tab[8] );
					break;
				case 9:
					TM1637_Display_NoINC( m,tab[9] );
					break;
				case 0:
					TM1637_Display_NoINC( m,tab[0] );
					break;
			}
	}
	
}


