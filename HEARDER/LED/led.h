#ifndef __LED_H
#define __LED_H

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
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

void LED_Init(void);//初始化		 				    
#endif
