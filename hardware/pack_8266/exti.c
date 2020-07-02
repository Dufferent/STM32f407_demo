#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
//#include "oled.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F429������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();               //����GPIOHʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_9;               //PG9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13;     //PG11,10
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2-PG9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���2
    
    //�ж���3-PG10
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //ʹ���ж���2*/
    
  //�ж���13-PG11
  HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
	
	delay_ms(3);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
  key_buf = 1;
	
		
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(3);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
	if(KEY0==0)
		{
           key_buf = 2;        
            }
}

void EXTI15_10_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10|GPIO_PIN_11);
	delay_ms(3);
	if(KEY1 == 0)
		{
        key_buf = 3;    
            }
	if(KEY2 == 0)
		{
				key_buf = 4; 
            }
}
/*
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);//�����жϴ������ú���
}
*/
//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //����
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            //if(WK_UP==1) 
            {
				LED1=!LED1;//����LED0,LED1�������
				LED0=!LED1;
            }
            break;
        case GPIO_PIN_9:
            if(Key1==0)  //LED1��ת
            {
                LED1=!LED1;    
            }
            break;
        case GPIO_PIN_10:
            if(Key2==0)  //ͬʱ����LED0,LED1��ת 
            {
                LED0=!LED0;
				        LED1=!LED1;
            }
            break;

        case GPIO_PIN_11:
            if(Key3==0)  
            {
				LED0=!LED0;//����LED0��ת
            }
            break;
    }
}*/