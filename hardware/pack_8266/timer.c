#include "timer.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//V1.1 20140504
//����TIM14_PWM_Init����,����PWM���
//V1.2 20140504
//����TIM5_CH1_Cap_Init����,�������벶��
//V1.3 20141026
//����TIM7_Int_Init����
////////////////////////////////////////////////////////////////////////////////// 	 


//��ʱ��3�жϷ������	 
/*void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
		LED1=!LED1;			    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}*/
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
/*void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ 
	TIM3->PSC=psc;  	//Ԥ��Ƶ��	  
	TIM3->DIER|=1<<0;   //���������ж�	  
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM3_IRQn,2);	//��ռ1�������ȼ�3����2									 
}*/

//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
/*void TIM14_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<8; 	//TIM14ʱ��ʹ��    
	RCC->AHB1ENR|=1<<5;   	//ʹ��PORTFʱ��	
	GPIO_Set(GPIOF,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOF,9,9);	//PF9,AF9 
	
	TIM14->ARR=arr;			//�趨�������Զ���װֵ 
	TIM14->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM14->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM14->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM14->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч	   
	TIM14->CR1|=1<<7;   	//ARPEʹ�� 
	TIM14->CR1|=1<<0;    	//ʹ�ܶ�ʱ��14 											  
}  */

//��ʱ��2ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
/*void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{		 
	RCC->APB1ENR|=1<<3;   	//TIM5 ʱ��ʹ�� 
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	GPIO_Set(GPIOA,PIN0,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD);//���ù���,����
	GPIO_AF_Set(GPIOA,0,2);	//PA0,AF2
	  
 	TIM5->ARR=arr;  		//�趨�������Զ���װֵ   
	TIM5->PSC=psc;  		//Ԥ��Ƶ�� 

	TIM5->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
 	TIM5->CCMR1|=0<<4; 		//IC1F=0000 ���������˲��� ���˲�
 	TIM5->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 

	TIM5->CCER|=0<<1; 		//CC1P=0	�����ز���
	TIM5->CCER|=1<<0; 		//CC1E=1 	���������������ֵ������Ĵ�����

	TIM5->EGR=1<<0;			//�������Ʋ��������¼�,ʹд��PSC��ֵ������Ч,���򽫻�Ҫ�ȵ���ʱ������Ż���Ч!
	TIM5->DIER|=1<<1;   	//��������1�ж�				
	TIM5->DIER|=1<<0;   	//���������ж�	
	TIM5->CR1|=0x01;    	//ʹ�ܶ�ʱ��2
	MY_NVIC_Init(2,0,TIM5_IRQn,2);//��ռ2�������ȼ�0����2	   
}*/
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
/*void TIM5_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM5->SR;
 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(tsr&0X01)//���
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(tsr&0x02)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			    TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM5->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM5->CR1&=~(1<<0)		;    	//ʹ�ܶ�ʱ��2
	 			TIM5->CNT=0;					//���������
	 			TIM5->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز���
				TIM5->CR1|=0x01;    			//ʹ�ܶ�ʱ��2
			}		    
		}			     	    					   
 	}
	TIM5->SR=0;//����жϱ�־λ   
}*/

extern vu16 USART3_RX_STA;
//��ʱ��7�жϷ������		    
void TIM7_IRQHandler(void)
{ 	  		    
	if(TIM7->SR&0X01)//�Ǹ����ж�
	{	 			   
		USART3_RX_STA|=1<<15;	//��ǽ������
		TIM7->SR&=~(1<<0);		//����жϱ�־λ		   
		TIM7->CR1&=~(1<<0);		//�رն�ʱ��7	  
	}	      											 
} 
//ͨ�ö�ʱ��7�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz 
void TIM7_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<5;	//TIM7ʱ��ʹ��    
 	TIM7->ARR=arr;  	//�趨�������Զ���װֵ 
	TIM7->PSC=psc;  	//Ԥ��Ƶ��	  
	TIM7->CNT=0;  		//����������	  
	TIM7->DIER|=1<<0;   //���������ж�	  
	TIM7->CR1|=0x01;    //ʹ�ܶ�ʱ��7
  //	MY_NVIC_Init(0,1,TIM7_IRQn,2);	//��ռ0�������ȼ�1����2		
  __HAL_RCC_TIM7_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM7_IRQn,0,1);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //����ITM3�ж�   	
} 











