/*
 * buzzer_task.h
 *
 *  Created on: Jul 29, 2026
 *      Author: liuyu
 */

#ifndef TASK_BUZZER_TASK_H_
#define TASK_BUZZER_TASK_H_

void Buzzer_Init(void);
void vBuzzerTask(void *pvParameters);
void Buzzer_Beep(void);

#endif /* TASK_BUZZER_TASK_H_ */
