/*
 * lcd_task.c
 *
 *  Created on: Oct 22, 2026
 *      Author: 赵
 */

#include "main.h"
#include "FreeRTOS.h"
#include "lcd_task.h"
#include "semphr.h"
#include "lcd.h"

static SemaphoreHandle_t xSemphrForDMA;

static void BacklightControl(uint8_t on);
static void Reset(void);
static void SendCommand(uint8_t Cmd);
static void SendData(uint8_t *pData,uint16_t Size);


void LCDTask_Init(void)
{
	xSemphrForDMA = xSemaphoreCreateBinary();

	LCD_InitTypeDef LCD_InitStrut ={0};

	LCD_InitStrut.back_light_control_callback  = BacklightControl;
	LCD_InitStrut.reset_callback               = Reset;
	LCD_InitStrut.send_command_callback        = SendCommand;
	LCD_InitStrut.send_data_callback           = SendData;

	lcd_init(&LCD_InitStrut);
}
//@作用：LCD的任务函数
void vLCDTask(void*pvParameters)
{
	lcd_clear();
	//#1. 绘制粉色标题背景

	lcd_set_cursor(260, 8);
	lcd_set_brush(0xff7bff);
	lcd_fill_rect(60, 15);

	//#2.绘制标题文字
	lcd_set_cursor(262, 21);
	lcd_set_pen(0x000000);
	lcd_print_string("Run Mode");

	//#3.绘制面板背景
	lcd_set_cursor(260, 23);
	lcd_set_brush(0xcccccc);
	lcd_fill_rect(60, 35);

	//#4.绘制文字
	lcd_set_cursor(265, 43);
	lcd_set_pen(0x000000);
	lcd_print_string("One-Shot");

	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(200));


	}
}
//
//@作用：控制LCD屏幕的背光
//@参数：On 0-熄灭背光 1-点亮背光
//
static void BacklightControl(uint8_t on)
{
	if(on == 0)
	{
		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
	}
	else
	{

		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
	}
}

//
//@作用：对LCD进行复位
//@参数：无
//

static void Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(120);
}

//
//@作用：发送命令
//@参数：Cmd 发送的命令字节
//
static void SendCommand(uint8_t Cmd)
{
	extern SPI_HandleTypeDef hspi1;

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port,LCD_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &Cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port,LCD_NSS_Pin, GPIO_PIN_SET);
}

//
//@作用：发送数据
//@参数：pData - 要发送的数组
//@参数：Size  - 数组长度
//
static void SendData(uint8_t *pData,uint16_t Size)
{
	extern SPI_HandleTypeDef hspi1;

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port,LCD_NSS_Pin, GPIO_PIN_RESET);
	//轮询方式,效率低
	//HAL_SPI_Transmit(&hspi1, pData, Size, HAL_MAX_DELAY);
	//通过DMA发送数据
	HAL_SPI_Transmit_DMA(&hspi1, pData, Size);
	//取信号，等待数据发送完成
	xSemaphoreTake(xSemphrForDMA,portMAX_DELAY);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port,LCD_NSS_Pin, GPIO_PIN_SET);
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi -> Instance == SPI1)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemphrForDMA,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}














