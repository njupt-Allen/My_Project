/*
 * lcd_task.c
 *
 *  Created on: Oct 22, 2026
 *      Author: 赵
 */

#include "main.h"

static void BacklightControl(uint8_t on);
static void Reset(void);
static void SendCommand(uint8_t Cmd);
static void SendData(uint8_t *pData,uint16_t Size);



void LCDTask_Init(void)
{
	BacklightControl(1);
	Reset();

	uint8_t dataToSend[10];

	SendCommand(0x11);//退出休眠模式
	HAL_Delay(125);

	SendCommand(0x3a);

	dataToSend[0] = 0x55;
	SendData(dataToSend, 1);

	SendCommand(0x29);

	//设置行范围
	SendCommand(0x2b);
	dataToSend[0] = 0x00;
	dataToSend[1] = 0x9b;
	dataToSend[2] = 0x00;
	dataToSend[3] = 0xa4;
	SendData(dataToSend, 4);

	//设置列范围
	SendCommand(0x2a);
	dataToSend[0] = 0x00;
	dataToSend[1] = 0x73;
	dataToSend[2] = 0x00;
	dataToSend[3] = 0x7c;
	SendData(dataToSend, 4);

	//显示彩色小方块
	SendCommand(0x2c);
	//先传高字节再传低字节
	const uint16_t image[100] = {[0 ... 49] = 0x00f8,[50 ... 99] = 0xe007};

	SendData((uint8_t*)image, 200);

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
	HAL_Delay(5);
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
	HAL_SPI_Transmit(&hspi1, pData, Size, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port,LCD_NSS_Pin, GPIO_PIN_SET);
}






























