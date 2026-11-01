/*
 * key_up.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */
#include"key.h"
#include"key_up.h"
#include"string.h"

static KeyHandle_TypeDef hkeyup;


static void keyup_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1,(const uint8_t *)"keyup Clicked.\n",strlen("keyup Clicked.\n"),HAL_MAX_DELAY);
}

void Keyup_Init(void)
{
    hkeyup.GPIO_Port = key_up_GPIO_Port;
    hkeyup.GPIO_Pin  = key_up_Pin;
    hkeyup.ClickedCallback =keyup_ClickedCallback;
    Key_Init(&hkeyup);
}

void Keyup_Scan(void)
{
	Key_Scan(&hkeyup);
}
