/*-----------------------------------------------
  ���ƣ� �����
  Date: 2022/11/16
  Function: 
   - ��ʾ�Ѿ��趨�ļ۸�
   - ͨ���������ð��������ü۸�
------------------------------------------------*/
#include<reg52.h>
#define DataPort P0

//--------���߶˿�--------------------------------------------------------------------
sbit SEG1=P1^0;
sbit SEG2=P1^1;
sbit SEG3=P1^2;
sbit SEG4=P1^3;

//sbit  KOPTION = P3^2; //INT0
//sbit  KSET = P3^3; //INT1

sbit LATCH1=P2^6;//��������ʹ�ܶ˿� ������

//---------��������-------------------------------------------------------------------
void Delay(unsigned int t);  
void SetSegAll(unsigned int t); 
				   
void setVarasNewVar();
void setVaratPostion(unsigned vari);

void SetPrice();
void setOption();	   
void DisplayOption(unsigned i);
void DiaplyPrice();
void DiaplyPriceNewSetting();
void SetSegAll(unsigned int flag);
void Init_INT(void);
void flashVaratPosition(unsigned vari);

//---------ÿ�����������ʾ������-----------------------------------------------------
//0 1 2 3 4 5 6 7 8 9 �� ���ڵ�1��3��4λ������3��4λ�ϵ���ֵû�С��ޡ�
unsigned char code DuanMa[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09,0xFF};
//0. 1. 2. 3. 4. 5. 6. 7. 8. 9.  ���ڵ�2λ��ֵ
unsigned char code DuanMaDian[]={0x02,0x9E,0x24,0x0C,0x98,0x48,0x40,0x1E,0x00,0x08}; 

//S E t 1
unsigned char code CODESET1[] = {0x49,0x61,0xE1,0x9F};
//S E t 2
unsigned char code CODESET2[] = {0x49,0x61,0xE1,0x25}; 
/*
//S H E 1
unsigned char code CODESET1[] = {0x49,0x91,0x61,0x9F};
//S H E 2
unsigned char code CODESET2[] = {0x49,0x91,0x61,0x25}; 
*/
/*//H A O .//D O N E  ��ʾȫ�����ý����������DONE���ص�IDLE�� ��������Ч
unsigned char code DONE[] = {0x91,0x11,0x03,0xFE};
*/

//-------------����ѡ���ֵλ�á���ֵ����ֵ-----------------------------------------
unsigned int KOPTIONINDEX = 0;//0,1,2��3  =�� IDLE CODESET1 CODESET2 DONE
unsigned int WeiPosition = 0;//0,1,2,3	 �����ĸ�λ�ϵ���ֵ
//unsigned int Idle0Set11Set22DONE3 = 0;//	0 1 2 3

//4λ������DuanMa/DuanMaDian�е�����ֵ�� �Ѿ��趨
unsigned int Var1Index = 0;		//��DuanMa�е�����ֵ
unsigned int Var2Index = 0;		//��DuanMaDian�е�����ֵ
unsigned int Var3Index = 0;		//��DuanMa�е�����ֵ
unsigned int Var4Index = 0;		//��DuanMa�е�����ֵ
//�����趨
unsigned int NEWVar1Index = 0;		//��DuanMa�е�����ֵ
unsigned int NEWVar2Index = 0;		//��DuanMaDian�е�����ֵ
unsigned int NEWVar3Index = 0;		//��DuanMa�е�����ֵ
unsigned int NEWVar4Index = 0;		//��DuanMa�е�����ֵ


/*------------------------------------------------
                    ������
------------------------------------------------*/
main()
{				  
	Init_INT();
	while(1)
      {		
			Delay(200);
	  		if(KOPTIONINDEX == 0)
			{
				DiaplyPrice();	
			}
			else
			{
				 
				if(KOPTIONINDEX == 1)
				{
					DisplayOption(KOPTIONINDEX);
				}
				else if(KOPTIONINDEX == 2)
				{
					/*DisplayOption(KOPTIONINDEX);
					Delay(200);
					DiaplyPriceNewSetting();	
					flashVaratPosition(WeiPosition);
					Delay(200);*/
					DisplayOption(KOPTIONINDEX);
					Delay(200);
					flashVaratPosition(WeiPosition);
				}	 				
			}			 
      }
}
 
void setVarasNewVar(){
	     Var1Index =NEWVar1Index;
	     Var2Index =NEWVar2Index;
	     Var3Index =NEWVar3Index;
	     Var4Index =NEWVar4Index;	 
}

void DisplayOption(unsigned i){
	switch(i)
	{
		case 0:
			break;
		case 1:
		 	DataPort= CODESET1[0]; 
       			SetSegAll(0);
	   		SEG1=1;	
	   		Delay(100);

			DataPort=CODESET1[1]; 
       			SetSegAll(0);
	   		SEG2=1;	
	   		Delay(100);
		  
			DataPort= CODESET1[2]; 
       			SetSegAll(0);
	   		SEG3=1;	
	   		Delay(100);	 

			DataPort= CODESET1[3]; 
       			SetSegAll(0);
	   		SEG4=1;	
	   		Delay(100); 

		break;
		case 2:
			DataPort= CODESET2[0]; 
       			SetSegAll(0);
	   		SEG1=1;	
	   		Delay(100);

			DataPort=CODESET2[1]; 
       			SetSegAll(0);
	   		SEG2=1;	
	   		Delay(100);	 		  

			DataPort= CODESET2[2]; 
       			SetSegAll(0);
	   		SEG3=1;	
	   		Delay(100);	 

			DataPort= CODESET2[3]; 
       			SetSegAll(0);
	   		SEG4=1;	
	   		Delay(100); 
 		break;
 }
}

void DiaplyPrice(){
			DataPort= DuanMa[Var1Index]; 
       			SetSegAll(0);
	   		SEG1=1;	
	   		Delay(100);

			DataPort=DuanMaDian[Var2Index]; 
       			SetSegAll(0);
	   		SEG2=1;	
	   		Delay(100);
		  			   
			DataPort= DuanMa[Var3Index]; 
       			SetSegAll(0);
	   		SEG3=1;	
	   		Delay(100);
						
			DataPort= DuanMa[Var4Index]; 
       			SetSegAll(0);
	   		SEG4=1;	
	   		Delay(100); 
}

void DiaplyPriceNewSetting(){
			DataPort= DuanMa[NEWVar1Index]; 
       			SetSegAll(0);
	   		SEG1=1;	
	   		Delay(100);

			DataPort= DuanMaDian[NEWVar2Index]; 
       			SetSegAll(0);
	   		SEG2=1;	
	   		Delay(100);
		  			   
			DataPort= DuanMa[NEWVar3Index]; 
       			SetSegAll(0);
	   		SEG3=1;	
	   		Delay(100);
						
			DataPort= DuanMa[NEWVar4Index]; 
       			SetSegAll(0);
	   		SEG4=1;	
	   		Delay(100); 
}

void SetSegAll(unsigned int flag){
	 SEG1=flag;	
	 SEG2=flag;	
	 SEG3=flag;	
	 SEG4=flag;	 
}

/*------------------------------------------------
 ��ʱ����������������� unsigned int t���޷���ֵ
 unsigned int �Ƕ����޷������α�������ֵ�ķ�Χ��
 0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
 	while(--t);
}

/*------------------------------------------------
                    ��ʱ����ʼ���ӳ���
------------------------------------------------*/
void Init_INT(void)
{	
   	EA=1;//�����ж�	
//	IT1=1;//�����س�����ʽ���½��أ�
//	EX1=1;//��INT0���ж�����	
//	IT0=1;//�����س�����ʽ���½��أ�
//	EX0=1;//��INT0���ж�����	


	IT0=1;//�½��ش���
	IT1=1;
	PX0=1;//�������ȼ�
	IE=0x85;//����INT0,INT1�ж�

}
/*------------------------------------------------
                 ��ʱ���ж��ӳ���
------------------------------------------------*/
void ISR_INT0(void) interrupt 0 
{					 
	EA=0;//��ֹ�ж� 
	setOption();
	EA=1;//���ж� 
}

void ISR_INT1(void) interrupt 2 
{		 
	EA=0;//��ֹ�ж� 
	DiaplyPriceNewSetting();
	SetPrice(); 
	DiaplyPriceNewSetting();
	EA=1;
}

void SetPrice(){
	if(INT1==0){//���°�������⵽0������������������μ��	 
	  Delay(10);										 	 
	  if(INT1 == 0){
	  		switch(KOPTIONINDEX)
			{
				case 0:
					
				break;
				case 1:	  //������ֵλ��	   
					WeiPosition ++;
					if(WeiPosition == 4) 
					{
						WeiPosition = 0;
					}

					//flash the var at the weipostion
					 flashVaratPosition(WeiPosition);
				break;
				case 2:  //������ֵ
					 setVaratPostion(WeiPosition);
				break; 
			} 
	  }
	}  
	while(INT1==0);	 
}

void setOption(){
	if(INT0==0){//���°�������⵽0������������������μ��	 
	  Delay(10);										 	 
	  if(INT0 == 0){	  			
			KOPTIONINDEX ++;
		
			if(KOPTIONINDEX==3){
				KOPTIONINDEX = 0;
				setVarasNewVar();	 
			} 
			else{
				DisplayOption(KOPTIONINDEX);
			}
	  }	  
	}
	Delay(100);
	while(INT0 ==0);
}

void flashVaratPosition(unsigned vari)
{									    
	switch(vari){
		case 0:	 
			DataPort= DuanMa[NEWVar1Index]; 
       			SetSegAll(0);
	   		SEG1=1;	
	   		Delay(200);
			DataPort= 0xFD; 
			SetSegAll(0);
			SEG1=1;	
			Delay(200);
		break;
		case 1:
			DataPort= DuanMaDian[NEWVar2Index]; 
       			SetSegAll(0);
	   		SEG2=1;	
	   		Delay(200); 

			DataPort= 0xFD; 
			SetSegAll(0);
			SEG2=1;	
			Delay(200);

		break;
		case 2:
			DataPort= DuanMa[NEWVar3Index]; 
       			SetSegAll(0);
	   		SEG3=1;	
	   		Delay(200); 

			DataPort= 0xFD; 
			SetSegAll(0);
			SEG3=1;	
			Delay(200);
		break;
		case 3:
			DataPort= DuanMa[NEWVar4Index]; 
       			SetSegAll(0);
	   		SEG4=1;	
	   		Delay(200); 

			DataPort= 0xFD; 
			SetSegAll(0);
			SEG4=1;	
			Delay(200);
		break;
	} 	
}

void setVaratPostion(unsigned vari){
	switch(vari){
		case 0:	 
			NEWVar1Index ++;
			if(NEWVar1Index == 12) 
			{					
				NEWVar1Index = 0;
			}
		break;
		case 1:
			NEWVar2Index ++;
			if(NEWVar2Index == 11) 
			{						
					NEWVar2Index = 0;
			}
		break;
		case 2:
			NEWVar3Index ++;
			if(NEWVar3Index == 11) 
			{						
					NEWVar3Index = 0;
			}
		break;
		case 3:
			NEWVar4Index ++;
			if(NEWVar4Index == 11) 
			{						
					NEWVar4Index = 0;
			}
		break;
	}	
}