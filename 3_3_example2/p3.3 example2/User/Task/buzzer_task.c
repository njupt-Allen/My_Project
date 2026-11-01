/*
 * buzzer_task.c
 *
 *  Created on: Jul 29, 2026
 *      Author: liuyu
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "main.h"

static SemaphoreHandle_t xBuzzerSemphr;

void Buzzer_Init(void)
{
	xBuzzerSemphr = xSemaphoreCreateBinary();
}

void vBuzzerTask(void *pvParameters)
{
	for(;;)
	{
		xSemaphoreTake(xBuzzerSemphr, portMAX_DELAY);

		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
		vTaskDelay(pdMS_TO_TICKS(100));
		HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
	}
}

void Buzzer_Beep(void)
{
	xSemaphoreGive(xBuzzerSemphr);
}
