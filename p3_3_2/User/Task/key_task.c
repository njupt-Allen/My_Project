#include"key.h"
#include"FreeRTOS.h"
#include"task.h"
#include"main.h"
#include"string.h"
#include"key1.h"
#include"key2.h"
#include"key3.h"
#include"key4.h"
#include"key_up.h"
#include"key_down.h"
extern UART_HandleTypeDef huart1;



void KeyTask(void *pvParameters)
{

	Key1_Init();
	Key2_Init();
	Key3_Init();
	Key4_Init();
	Keyup_Init();
	Keydown_Init();

	for(;;)
	{
		Key1_Scan();
		Key2_Scan();
		Key3_Scan();
		Key4_Scan();
		Keyup_Scan();
		Keydown_Scan();
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}



