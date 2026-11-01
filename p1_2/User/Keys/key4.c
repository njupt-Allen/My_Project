/*
 * key4.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */

#include"key.h"
#include"key4.h"
#include"string.h"

static KeyHandle_TypeDef hkey4;


static void key4_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1,(const uint8_t *)"key4 Clicked.\n",strlen("key4 Clicked.\n"),HAL_MAX_DELAY);
}

void Key4_Init(void)
{
    hkey4.GPIO_Port = key4_GPIO_Port;
    hkey4.GPIO_Pin  = key4_Pin;
    hkey4.ClickedCallback =key4_ClickedCallback;
    Key_Init(&hkey4);
}

void Key4_Scan(void)
{
	Key_Scan(&hkey4);
}

