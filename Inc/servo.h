#ifndef  __SERVO_H
#define __SERVO_H

#include "main.h"

void MX_TIM2_Init(void);
void servopwm_start();
void Servo_ult();
void SetServoAngle(int angle);
void Servo1_ult();
void SetServo1Angle(int angle);

#endif