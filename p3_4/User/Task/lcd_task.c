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

static SemaphoreHandle_t xSemphrForDMA;

static void BacklightControl(uint8_t on);
static void Reset(void);
static void SendCommand(uint8_t Cmd);
static void SendData(uint8_t *pData,uint16_t Size);
static void SetRowRange(uint16_t Start,uint16_t End);
static void SetColumRange(uint16_t Start,uint16_t End);
static void Showimage(const uint16_t pImage[],uint16_t Size);
static void Showimage1(void);
static void Showimage2(void);

void LCDTask_Init(void)
{
	xSemphrForDMA = xSemaphoreCreateBinary();

	BacklightControl(1);
	Reset();



}
//@作用：LCD的任务函数
void vLCDTask(void*pvParameters)
{
	uint8_t dataToSend[10];

	SendCommand(0x11);//退出休眠模式
	HAL_Delay(125);

	SendCommand(0x3a);

	dataToSend[0] = 0x55;
	SendData(dataToSend, 1);

	SendCommand(0x29);
	for(;;)
	{
		Showimage1();
		vTaskDelay(pdMS_TO_TICKS(200));
		Showimage2();
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
//
//@作用：设置行范围
//@参数：Start - 起始行号
//@参数：End   - 结束行号
//
static void SetRowRange(uint16_t Start,uint16_t End)
{
	uint8_t dataToSend[4];

	SendCommand(0x2b);

	dataToSend[0]=(Start>>8)&0xff;
	dataToSend[1]=  Start&0xff;
	dataToSend[2]=(End>>8)&0xff;
	dataToSend[3]=    End&0xff;

	SendData(dataToSend, 4);

}


//
//@作用：设置列范围
//@参数：Start - 起始列号
//@参数：End   - 结束列号
//
static void SetColumRange(uint16_t Start,uint16_t End)
{
	uint8_t dataToSend[4];

	SendCommand(0x2a);

	dataToSend[0]=(Start>>8)&0xff;
	dataToSend[1]=  Start&0xff;
	dataToSend[2]=(End>>8)&0xff;
	dataToSend[3]=    End&0xff;

	SendData(dataToSend, 4);
}

//
//@作用：显示图像
//@参数：pImage - 要显示图像的数据
//@参数：Size   - 图像的尺寸（像素点数量）
//
static void Showimage(const uint16_t pImage[],uint16_t Size)
{
	SendCommand(0x2c);
	SendData((uint8_t*)pImage, Size*2);

}

#include "image1.h"
//显示图像1
static void Showimage1(void)
{
	SetRowRange(80,159);
	SetColumRange(60, 119);
	Showimage(image1, 80*60);
}

#include "image2.h"
//显示图像2
static void Showimage2(void)
{
	SetRowRange(80,159);
	SetColumRange(60, 119);
	Showimage(image2, 80*60);
}














