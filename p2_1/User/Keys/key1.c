/*
 * key1.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */

#include"key.h"
#include"string.h"
#include"buzzer_task.h"

static KeyHandle_TypeDef hkey1;


static void KEY1_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	Buzzer_Beep();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"KEY1 Clicked.\n",strlen("KEY1 Clicked.\n"),HAL_MAX_DELAY);
}

void Key1_Init(void)
{
    hkey1.GPIO_Port = key1_GPIO_Port;
    hkey1.GPIO_Pin  = key1_Pin;
    hkey1.ClickedCallback =KEY1_ClickedCallback;
    Key_Init(&hkey1);
}

void Key1_Scan(void)
{
	Key_Scan(&hkey1);
}


