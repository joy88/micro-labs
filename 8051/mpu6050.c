//-----------------------------------------
// MPU6050 IIC���Գ���
// ʹ�õ�Ƭ��STC89C51 
// ����11.0592M
//-----------------------------------------
#include <REG52.H>	
#include <math.h>    //Keil library  
#include <stdio.h>   //Keil library	
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

//-----------------------------------------
//�������ͼ�����
//-----------------------------------------
uchar dis[6];//�������תΪ�ַ������ַ���

//-----------------------------------------
//�ⲿ����:���ں�MPU6050
//-----------------------------------------
extern void InitMPU6050();
extern int GetData(uchar REG_Address);
extern void init_uart();	
extern void  SeriPushSend(uchar send_data);
//-----------------------------------------
//�ڲ�����:��ʱ������ת�ַ��������͵�����
//-----------------------------------------
void delay(unsigned int k);
void my_printf(uchar *s,int temp_data);
void SendData(int value);

//-----------------------------------------
//��ʱ
//-----------------------------------------
void delay(unsigned int k)	
{						
	unsigned int i,j;				
	for(i=0;i<k;i++)
	{			
		for(j=0;j<121;j++);
	}						
}
//-----------------------------------------
//����ת�ַ���
//-----------------------------------------
void my_printf(uchar *s,int temp_data)
{
	if(temp_data<0)
	{
		temp_data=-temp_data;
		*s='-';
	}
	else *s=' ';
	*++s =temp_data/10000+0x30;
	temp_data=temp_data%10000;     //ȡ������
	*++s =temp_data/1000+0x30;
	temp_data=temp_data%1000;     //ȡ������
	*++s =temp_data/100+0x30;
	temp_data=temp_data%100;     //ȡ������
	*++s =temp_data/10+0x30;
	temp_data=temp_data%10;      //ȡ������
	*++s =temp_data+0x30; 	
}
//-----------------------------------------
//����+���͵�����
//-----------------------------------------
void SendData(int value)
{ 
	uchar i;
	my_printf(dis, value);			//ת��������ʾ
	for(i=0;i<6;i++)
	{
    	SeriPushSend(dis[i]);
    }
}

//-----------------------------------------
//������
//-----------------------------------------
void main()
{ 
	delay(500);		//�ϵ���ʱ		
	init_uart();
	InitMPU6050();	//��ʼ��MPU6050
	delay(150);
	while(1)
	{
		SeriPushSend('#');//���У��س�
		SendData(GetData(0x3B));	//X����ٶ�
		SendData(GetData(0x3D));	//Y����ٶ�
		SendData(GetData(0x3F));	//Z����ٶ�
		SeriPushSend('$'); //����
		delay(20);
	}
}