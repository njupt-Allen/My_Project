/*
 * key2.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */

#include"key.h"
#include"key2.h"
#include"string.h"
#include"buzzer_task.h"

static KeyHandle_TypeDef hkey2;


static void key2_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	Buzzer_Beep();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"key2 Clicked.\n",strlen("key2 Clicked.\n"),HAL_MAX_DELAY);
}

void Key2_Init(void)
{
    hkey2.GPIO_Port = key2_GPIO_Port;
    hkey2.GPIO_Pin  = key2_Pin;
    hkey2.ClickedCallback =key2_ClickedCallback;
    Key_Init(&hkey2);
}

void Key2_Scan(void)
{
	Key_Scan(&hkey2);
}
