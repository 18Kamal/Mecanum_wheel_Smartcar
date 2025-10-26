#include "main.h"
#include "bt.h"
#include "pwm.h"
#include "display.h"
#include "motor.h"
#include "ssd1306.h"
#include "fonts.h"
#include "servo.h"
#include "ultrasonic.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>  
#include "modes.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim3;

void MX_Ir_Init(void){
 GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 
 }

 void IR_sensor_Control(void){

	 
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==GPIO_PIN_RESET  && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==GPIO_PIN_RESET ){
		 Motor_Forward();
	 }
	 else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==GPIO_PIN_SET){
		Motor_R_Rotate();
	 }
	 else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==GPIO_PIN_RESET){
			Motor_L_Rotate();
	 }
	 else {
		Motor_Stop();
		}
 }

// Global variables
static uint32_t obstacle_detected_time = 0;
static bool servo_scanned = false;


void Auto_Control(void) {
    float distance = Ultrasonic_GetDistance();
    const uint32_t mode_switch_timeout = 20000; // 20 seconds in ms

    if (distance >= 0 && distance <= 20) {
        // First time obstacle detected
        if (obstacle_detected_time == 0) {
            obstacle_detected_time = HAL_GetTick();
            servo_scanned = false;
   
        }

        // Stop motors
        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 0);
        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 0);
        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 0);
        PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 0);

        // Display warning
        SSD1306_Clear();
        SSD1306_GotoXY(5, 20);
        SSD1306_Puts("OBSTACLE DETECTED", &Font_7x10, 1);
        
        // Perform servo scan if not done yet
        if (!servo_scanned) {
            SSD1306_GotoXY(5, 35);
            SSD1306_Puts("SCANNING...", &Font_7x10, 1);
            SSD1306_UpdateScreen();
            
            // Perform scanning routine
            Servo_ult(); // This will do the full left-center-right scan
            
            servo_scanned = true;
            
            // Display scan complete message
            SSD1306_GotoXY(5, 50);
            SSD1306_Puts("SCAN COMPLETE", &Font_7x10, 1);
        }
        else {
            // Show how long obstacle has been present
            uint32_t elapsed = (HAL_GetTick() - obstacle_detected_time) / 1000;
            char time_msg[20];
            snprintf(time_msg, sizeof(time_msg), "Time: %lus", elapsed);
            SSD1306_GotoXY(5, 50);
            SSD1306_Puts(time_msg, &Font_7x10, 1);
        }
        
        SSD1306_UpdateScreen();

        // Switch to manual mode after 20 seconds
        if ((HAL_GetTick() - obstacle_detected_time) > mode_switch_timeout) {
            currentMode = MODE_MANUAL;
            safety_override = 0;
            SSD1306_Clear();
            SSD1306_GotoXY(5, 30);
            SSD1306_Puts("SWITCHED TO MANUAL", &Font_7x10, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            obstacle_detected_time = 0; // Reset timer
            servo_scanned = false;
        }
    } 
    else {
        // No obstacle detected
        if (obstacle_detected_time != 0) {
            // Only reset if we were previously blocked
            obstacle_detected_time = 0;
            servo_scanned = false;
        }
        IR_sensor_Control();
    }
}