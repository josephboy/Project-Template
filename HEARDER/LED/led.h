#ifndef __LED_H
#define __LED_H

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LEDa PFout(14)	// DS0
#define LEDb PEout(11)	// DS1	 
#define LED1 PGout(1)	// DS1	
#define LED2 PGout(2)	// DS1	
#define LED3 PGout(3)	// DS1	
#define LED4 PGout(4)	// DS1	
#define LED5 PGout(5)	// DS1	
#define LED6 PGout(6)	// DS1	
#define LED7 PGout(7)	// DS1	
#define LED8 PGout(8)	// DS1	

void LED_Init(void);//��ʼ��		 				    
#endif
