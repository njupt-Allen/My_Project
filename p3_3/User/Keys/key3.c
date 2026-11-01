/*
 * key3.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */

#include"key.h"
#include"key3.h"
#include"string.h"
#include"buzzer_task.h"

static KeyHandle_TypeDef hkey3;


static void key3_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	Buzzer_Beep();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"key3 Clicked.\n",strlen("key3 Clicked.\n"),HAL_MAX_DELAY);
}

void Key3_Init(void)
{
    hkey3.GPIO_Port = key3_GPIO_Port;
    hkey3.GPIO_Pin  = key3_Pin;
    hkey3.ClickedCallback =key3_ClickedCallback;
    Key_Init(&hkey3);
}

void Key3_Scan(void)
{
	Key_Scan(&hkey3);
}
