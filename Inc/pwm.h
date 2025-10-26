#ifndef PWM_H
#define PWM_H

#include "main.h"

void MX_TIM3_Init(void);
void PWM_Start(void);
void PWM_SetDutyCycle(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t dutyCycle);

#endif