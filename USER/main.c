//#include "stm32f4xx.h"
//#include "led.h"
//#include "delay.h"


//int main(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	delay_init(180);
//	LED_Init();	
//  while(1)
//	{
//	}
//}
#include "stdio.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "math.h"
#include "time.h"
#include "semphr.h"


u8 UsartSendData[3][20] = {"Task1 Send data\r\n",
													 "Task2 Send data\r\n",
													 "Task3 Send data\r\n"};

static QueueHandle_t xQueue = NULL;
QueueHandle_t xMutex;

//��дprintf��ӡ����
void prvNewPrintString(const portCHAR *pcString)
{
	/*��ͼ��ȡ����������ȡʧ��������޳�ʱ�ȴ�*/
	xSemaphoreTake(xMutex,portMAX_DELAY);
	{
		printf("%s",pcString);
	}
	xSemaphoreGive(xMutex);
	
	//vTaskDelay(rand()&0x1FF)
}	
													 
void led0_task(void *pvParameters)
{
	while(1)
	{
		LED1=~LED1;
		vTaskDelay(500);
		
	}
}

void led1_task(void *pvParameters)
{
	while(1)
	{
		LED2 = 0;
		vTaskDelay(200);
		LED2 = 1;
		vTaskDelay(200);
	}
}

void float_task(void *p_arg)
{
	static float float_num = 0.00;
	while(1)
	{
		float_num += 0.01f;
		printf("float_num��ֵΪ��%.4f\r\n",float_num);
		vTaskDelay(1000);
	}
}

//�������ݸ��ն�
void usart_send(char *Pcstring)
{
	char *cdata;
  cdata	= Pcstring;
	
	printf("%s",cdata);
	
}

//���ݷ�������
void UsartSendDataTask(void *pvParameters)
{
	char *Pcstring;
	
	Pcstring = (char*)pvParameters;
	
	for(;;)
	{
		usart_send(Pcstring);
		
		vTaskDelay(100);
	}
}

//���з�������
void vSendTask(void *pvParameters)
{
	char *Pcstring;
	portBASE_TYPE xStatus;
	
	Pcstring = (char*)pvParameters;
	
	for(;;)
	{
		
		/*�����з�������*/
		xStatus = xQueueSendToBack(xQueue,&pvParameters,portMAX_DELAY);
		
		if(xStatus != pdPASS)
		{
			
			printf("Could not send to the queue.\r\n");
			
		}
	}
}

//���н��պ���
void vReceiveTask(void *pvParameters)
{
	portBASE_TYPE xStatus;
	char *Pcstring;
	const portTickType xTicksToWait = 100/portTICK_RATE_MS;
	
	for(;;)
	{
		if(uxQueueMessagesWaiting(xQueue)!=0)
		{
			
			printf("Queue should have been empty!\t\n");
		
		}
		/*�Ӷ����н�������
		������ʱʱ��Ϊ���޳�ʱʱ��
		*/
		xStatus = xQueueReceive(xQueue,&Pcstring,xTicksToWait);
		if(xStatus == pdPASS)
		{
			
			printf("Receive = %s",Pcstring);
			
		}
		else
		{
			
			printf("Could not receive from the queue.\r\n");
			
		}
	}
}

int main(void)
{
	
	LED_Init();
	
//	LED1=0;
//	LED2=0;
	
//	xMutex = xSemaphoreCreateMutex();
//	
//		//��������
//	xQueue = xQueueCreate(3, sizeof(UsartSendData[0]));
//	
//		//��������1
//	xTaskCreate(UsartSendDataTask,
//							"Task 1",
//							1000,
//							UsartSendData[0],
//							1,
//							NULL);
//	//��������2
//	xTaskCreate(UsartSendDataTask,
//							"Task 2",
//							1000,
//							UsartSendData[1],
//							1,
//							NULL);
//		//��������3
//	xTaskCreate(UsartSendDataTask,
//							"Task 3",
//							1000,
//							UsartSendData[2],
//							1,
//							NULL);
	
	//��������1
	xTaskCreate(led0_task,
							"Task 1",
							1000,
							NULL,
							1,
							NULL);
	//��������2
	xTaskCreate(led1_task,
							"Task 2",
							1000,
							NULL,
							2,
							NULL);
//		//��������3
//	xTaskCreate(float_task,
//							"Task 3",
//							1000,
//							NULL,
//							1,
//							NULL);
//	
//	//����������
	vTaskStartScheduler();
	
	while(1)
	{

	}
}







