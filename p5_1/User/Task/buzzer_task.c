/*
 * buzzer_task.c
 *
 *  Created on: Oct 22, 2026
 *      Author: 赵
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "main.h"


static SemaphoreHandle_t xBuzzerSemphr;

void Buzzer_Init(void)
{
	//xBuzzerSemphr = xSemaphoreCreateBinary();
	//创建计数信号量
	xBuzzerSemphr = xSemaphoreCreateCounting(10,0);
}

void vBuzzer_Task(void *pvParamters)
{
	for(;;)
	{
		xSemaphoreTake(xBuzzerSemphr,portMAX_DELAY);
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
		vTaskDelay(pdMS_TO_TICKS(500));
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}
}
void Buzzer_Beep(void)
{
	xSemaphoreGive(xBuzzerSemphr);
}













