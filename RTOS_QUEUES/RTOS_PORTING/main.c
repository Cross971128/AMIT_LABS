/*
 * main.c
 *
 *  Created on: Feb 11, 2020
 *      Author: ThinkPad
 */
#include "FreeRtos.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include "lcd.h"
#include "keypad.h"
#include "UART.h"

xQueueHandle xQueue;

/*****************************
void count(void *p)
{
	unsigned char xStatus;
	static int count=0;
	DDRD &=~(1<<2);

while(1)
{
	if(PIND &(1<<2))



	{
		if(count==10)
		{
			count =0;
		}
		else
		{
			count ++;

		}
		//xStatus = xQueueSendToBack(xQueue,&count,200);

	}

  xStatus = xQueueSendToBack(xQueue,&count,20);
  vTaskDelay(100);
}


	//if (xStatus !=PdPASS)
	//{
		//vPrintString("could not send to queue");
	//}
	//queue send



}
void led(void *p)
{
	unsigned char xStatus;
	int receivedvalue;
	 DDRC|=(1<<2);
	 DDRC|=(1<<7);
	 PORTC&=~(1<<2);
	 PORTC&=~(1<<7);

	 while(1)
	 {
		 //queue receive
		 xStatus = xQueueReceive(xQueue,&receivedvalue,portMAX_DELAY);
		 if(receivedvalue <= 5)
		 {
			PORTC |=(1<<2);
			 PORTC &=~(1<<7);

		 }
		 else if(receivedvalue >5)
		 {
			 PORTC |=(1<<7);
			 PORTC &=~(1<<2);
		 }
		

		 
		 vTaskDelay(50);

}//end while

}//end led
//******************************
*/
void sys_inti(void)
{
	DDRB&=~(1<<PB0);
	DDRC|=(1<<PC7);
	
}
void count(void * Pvalue)
{
	unsigned char stat=0;
	while(1)
{	
	if(PINB&(1<<PB0))
	{
	vTaskDelay(300/ portTICK_PERIOD_MS);
		if(stat == 9)
		{
			stat=0;
		}
		else
		{stat ++;}
	xQueueSendToBack(xQueue,&stat,20/portTICK_PERIOD_MS);
	
	}
	
}
}
void count_keypad(void * Pvalue)
{	
	unsigned char stat=0;
	while(1)
	{
		stat = KeyPad_getPressedKey();
		vTaskDelay(300/ portTICK_PERIOD_MS);
		xQueueSendToBack(xQueue,&stat,20/portTICK_PERIOD_MS);
					
	}

}
void led (void * Pvalue)
{
	unsigned char recieved =0;
	while(1)
	{
	xQueueReceive(xQueue,&recieved,0);
	if(recieved == 1)
	{
		PORTC|=(1<<PC7);
		recieved=0;
	}
	else
	{
		PORTC&=~(1<<PC7);
	}
	vTaskDelay(100/portTICK_PERIOD_MS);
	
	}
}
void LCD_Display(void * PValue)
{
	unsigned char recieved=0;
	while(1)
	{
		LCD_goToRowColumn(0,0);
		xQueueReceive(xQueue,&recieved,portMAX_DELAY);
		LCD_intgerToString((int)recieved);
		vTaskDelay(100/portTICK_PERIOD_MS);
	}	
}
void UART_TASK(void * PValue)
{
	 uartInit_test();
	unsigned char recieved=0;
	unsigned char buffer[2];
	while(1)
	{
		
		xQueuePeek(xQueue,&recieved,portMAX_DELAY);
	sprintf(buffer,"%d",recieved);
		UART_sendString(buffer);
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}
 int main()

 {
	LCD_init();
	xQueue = xQueueCreate(3,sizeof(int));
	if(xQueue != NULL)
	{
		//xTaskCreate(count,"count1",240,(void*)100,1,NULL);
		xTaskCreate(count_keypad,"keypad",240,NULL,1,NULL);
		//xTaskCreate(led,"led1",240,(void*)100,1,NULL);
		xTaskCreate(LCD_Display,"LCD",240,NULL,1,NULL);
		xTaskCreate(UART_TASK,"UART",240,NULL,2,NULL);
		vTaskStartScheduler();

	}
	else
	{

	}
	while(1);


return 0;

 }
