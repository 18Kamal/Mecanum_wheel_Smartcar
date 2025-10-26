#ifndef  __ULTRASONIC_H
#define __ULTRASONIC_H

#define TRIG_PIN 		GPIO_PIN_10
#define TRIG_PORT 	GPIOB
#define ECHO_PIN 		GPIO_PIN_11
#define ECHO_PORT 	GPIOB

#include "main.h"

// Safety Thresholds
#define OBSTACLE_THRESHOLD_CM 20
#define CLEARANCE_THRESHOLD_CM 25  // Must be >10 to prevent flickering

// Global Variables
extern volatile uint16_t distance;
extern volatile uint8_t safety_override;

void MX_TIM1_Init(void);
void MX_US_Start(void);
void Ultrasonic_Update(void);
float Ultrasonic_GetDistance(void);
uint8_t Safety_GetStatus(void);
void Safety_clearOverride(void);

#endif