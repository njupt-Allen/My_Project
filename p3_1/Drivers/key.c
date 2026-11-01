/*
 * key.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */
#include "main.h"
#include "string.h"
#include "key.h"
extern UART_HandleTypeDef huart1;

void Key_Init(KeyHandle_TypeDef *Handle)
{
	Handle->Previous = GPIO_PIN_SET;
	Handle->Current  = GPIO_PIN_SET;

}
void Key_Scan(KeyHandle_TypeDef *Handle)
{
	Handle->Current = HAL_GPIO_ReadPin(Handle->GPIO_Port,Handle->GPIO_Pin);

	if(Handle->Previous == GPIO_PIN_RESET  && Handle->Current == GPIO_PIN_SET)
	{
		Handle->ClickedCallback();
		//HAL_UART_Transmit(&huart1,(const uint8_t *)"KEY1 Clicked.\n",strlen("KEY1 Clicked.\n"),HAL_MAX_DELAY);
	}
	Handle->Previous = Handle->Current;

}
