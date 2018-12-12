#include "usart.h"	
#include "stdio.h"	
#include "stm32f4xx_conf.h"
          
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);//ֱ���������   
	USART_SendData(USART2, ch);   
	return ch;
}


//����1��ʼ��---����dbus����
void usart1_init(u32 bound){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 

	//�����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//���������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//������ռʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//USART_ITConfig(USART1, USART_IT_PE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
	
	USART_Cmd(USART1, ENABLE);
}




//��ʼ��IO ����2
//bound:������
void usart2_init(u32 bound){
	
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

//	//Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

}

////����3��ʼ��---��������������
//void usart2_init(u32 bound){
//		
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//  
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
//	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	

//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
//  
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2, &USART_InitStructure); 

//	//�����ж���Դ
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	//���������ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	//������ռʽ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	//USART_ITConfig(USART2, USART_IT_PE, ENABLE);
//	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�
//	
//	USART_Cmd(USART2, ENABLE);
//}



//����3��ʼ��---��������������
//void usart3_init(u32 bound){
//		
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//  
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
//	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	

//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
//  
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART3, &USART_InitStructure); 

//	//�����ж���Դ
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	//���������ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	//������ռʽ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//	//USART_ITConfig(USART3, USART_IT_PE, ENABLE);
//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�
//	
//	USART_Cmd(USART3, ENABLE);
//}


//void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//����DMA2ʱ��
//	  
//	DMA_DeInit(DMA2_Stream2);// ��λ��ʼ��DMA������ 

//	while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);//ȷ��DMA��������λ���
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart1 rx��Ӧdma2��ͨ��4��������2 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	//����DMAԴ���������ݼĴ�����ַ 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;//���ַ(Ҫ����ı�����ָ��)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//���򣺴����赽�ڴ�		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//�����СDMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݵ�λ		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�ڴ����ݵ�λ 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAģʽ������ѭ��
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//���ȼ�����	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//����FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//�洢��ͻ������ 16 ������   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //����ͻ������ 1 ������ 
//	DMA_Init(DMA2_Stream2, &DMA_InitStructure);//����DMA2��������		 
//	  
//	DMA_Cmd(DMA2_Stream2, ENABLE);//ʹ��DMA
//  
//	while(DMA_GetCmdStatus(DMA2_Stream2) != ENABLE);// �ȴ�DMA��������Ч
//  
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 	//ʹ��DMA����  
//}


//void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//����DMA1ʱ��
//	  
//	DMA_DeInit(DMA1_Stream5);// ��λ��ʼ��DMA������ 

//	while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);//ȷ��DMA��������λ���
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart3 rx��Ӧdma1��ͨ��4��������1 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);	//����DMAԴ���������ݼĴ�����ַ 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;//���ַ(Ҫ����ı�����ָ��)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//���򣺴����赽�ڴ�		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//�����СDMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݵ�λ		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�ڴ����ݵ�λ 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAģʽ������ѭ��
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//���ȼ�����	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//����FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//�洢��ͻ������ 16 ������   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //����ͻ������ 1 ������ 
//	DMA_Init(DMA1_Stream5, &DMA_InitStructure);//����DMA2��������		 
//	  
//	DMA_Cmd(DMA1_Stream5, ENABLE);//ʹ��DMA
//  
//	while(DMA_GetCmdStatus(DMA1_Stream5) != ENABLE);// �ȴ�DMA��������Ч
//  
//	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 	//ʹ��DMA����  
//}


//void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//����DMA1ʱ��
//	  
//	DMA_DeInit(DMA1_Stream1);// ��λ��ʼ��DMA������ 

//	while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);//ȷ��DMA��������λ���
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart3 rx��Ӧdma1��ͨ��4��������1 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	//����DMAԴ���������ݼĴ�����ַ 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;//���ַ(Ҫ����ı�����ָ��)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//���򣺴����赽�ڴ�		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//�����СDMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//�ڴ��ַ����
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݵ�λ		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//�ڴ����ݵ�λ 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAģʽ������ѭ��
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//���ȼ�����	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//����FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//�洢��ͻ������ 16 ������   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //����ͻ������ 1 ������ 
//	DMA_Init(DMA1_Stream1, &DMA_InitStructure);//����DMA2��������		 
//	  
//	DMA_Cmd(DMA1_Stream1, ENABLE);//ʹ��DMA
//  
//	while(DMA_GetCmdStatus(DMA1_Stream1) != ENABLE);// �ȴ�DMA��������Ч
//  
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 	//ʹ��DMA����  
//}






















