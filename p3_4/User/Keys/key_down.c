/*
 * key_down.c
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */
#include"key.h"
#include"key_down.h"
#include"string.h"
#include"buzzer_task.h"

static KeyHandle_TypeDef hkeydown;


static void keydown_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	Buzzer_Beep();
	HAL_UART_Transmit(&huart1,(const uint8_t *)"keydown Clicked.\n",strlen("keydown Clicked.\n"),HAL_MAX_DELAY);
}

void Keydown_Init(void)
{
    hkeydown.GPIO_Port = key_down_GPIO_Port;
    hkeydown.GPIO_Pin  = key_down_Pin;
    hkeydown.ClickedCallback =keydown_ClickedCallback;
    Key_Init(&hkeydown);
}

void Keydown_Scan(void)
{
	Key_Scan(&hkeydown);
}
