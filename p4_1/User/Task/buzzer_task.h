/*
 * buzzer_task.h
 *
 *  Created on: Oct 22, 2026
 *      Author: 赵
 */

#ifndef TASK_BUZZER_TASK_H_
#define TASK_BUZZER_TASK_H_

void Buzzer_Init(void);
void vBuzzer_Task(void *pvParamters);
void Buzzer_Beep(void);

#endif /* TASK_BUZZER_TASK_H_ */
