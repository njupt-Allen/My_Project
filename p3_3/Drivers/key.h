/*
 * key.h
 *
 *  Created on: Oct 20, 2026
 *      Author: 赵
 */

#ifndef KEY_H_
#define KEY_H_
#include "main.h"

typedef struct
{
	GPIO_PinState Previous;
	GPIO_PinState Current;

	GPIO_TypeDef*GPIO_Port;
	uint16_t GPIO_Pin;

	void(*ClickedCallback)(void);

}KeyHandle_TypeDef;

void Key_Init(KeyHandle_TypeDef *Handle);
void Key_Scan(KeyHandle_TypeDef *Handle);



#endif /* KEY_H_ */
