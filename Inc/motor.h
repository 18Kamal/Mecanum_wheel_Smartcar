#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f1xx_hal.h"

/* Motor direction LED Pin Definitions */
#define MOTOR1_PORT GPIOA
#define MOTOR1_PIN1 GPIO_PIN_4  // Motor 1 Direction 1
#define MOTOR1_PIN2 GPIO_PIN_5  // Motor 1 Direction 2

#define MOTOR2_PORT GPIOA
#define MOTOR2_PIN1 GPIO_PIN_11 // Motor 2 Direction 1
#define MOTOR2_PIN2 GPIO_PIN_12 // Motor 2 Direction 2

#define MOTOR3_PORT GPIOB
#define MOTOR3_PIN1 GPIO_PIN_12 // Motor 3 Direction 1
#define MOTOR3_PIN2 GPIO_PIN_13 // Motor 3 Direction 2

#define MOTOR4_PORT_A GPIOA
#define MOTOR4_PIN1 GPIO_PIN_8  // Motor 4 Direction 1
#define MOTOR4_PORT_B GPIOB
#define MOTOR4_PIN2 GPIO_PIN_5  // Motor 4 Direction 2

/* Function Prototypes */
void MX_Motor_Init(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_Stop(void);
void Motor_Left(void);
void Motor_Right(void);
void Motor_L_Forward(void);
void Motor_L_Backward(void);
void Motor_R_Forward(void);
void Motor_R_Backward(void);
void Motor_R_Rotate(void);
void Motor_L_Rotate(void);


#endif  /* LED_H */