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

extern TIM_HandleTypeDef htim3;

void MX_Motor_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);
   
		/* Configure Motor 1 direction LEDs (PA4, PA5) */
    GPIO_InitStruct.Pin = MOTOR1_PIN1 | MOTOR1_PIN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR1_PORT, &GPIO_InitStruct);

    /* Configure Motor 2 direction LEDs (PA11, PA12) */
    GPIO_InitStruct.Pin = MOTOR2_PIN1 | MOTOR2_PIN2;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR2_PORT, &GPIO_InitStruct);

    /* Configure Motor 3 direction LEDs (PB12, PB13) */
    GPIO_InitStruct.Pin = MOTOR3_PIN1 | MOTOR3_PIN2;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR3_PORT, &GPIO_InitStruct);

    /* Configure Motor 4 direction LEDs (PA8, PB5) */
    GPIO_InitStruct.Pin = MOTOR4_PIN1;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR4_PORT_A, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MOTOR4_PIN2;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR4_PORT_B, &GPIO_InitStruct);
}

/* Car move Forward */
void Motor_Forward(void) {
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 200);
            
					  HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 200);
		
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 200);
		
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 200);
		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("FORWARD", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_UpdateScreen(); // Update the display
}
/* Car move Backward */
void Motor_Backward(void) {
            HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 200);
						
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 200);
						
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 200);
         
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 200);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("BACKWARD", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_UpdateScreen(); // Update the display
}

/* Car Stop */
void Motor_Stop(void) {
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 0);
			
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("STOP", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_UpdateScreen(); // Update the display
}

/* Car move left */
void Motor_Left(void) {
	          HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 250);
						
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 250);
						
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 250);
         
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 250);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("RIGHT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_UpdateScreen(); // Update the display
}

/* Car move Right */
void Motor_Right(void) {
            HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 250);
						
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 250);
						
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 250);
         
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 250);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("LEFT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_UpdateScreen(); // Update the display
}
/* Car move left forward */
void Motor_L_Forward(void){
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 250);
						
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 250);
         
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("LEFT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("FORWARD", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display
}

/* Car move left Backward */
void Motor_L_Backward(void){
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 250);
         
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 250);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("LEFT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("BACKWARD", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display
}
/* Car move right forward */
void Motor_R_Forward(void){
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 250);

						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 250);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("RIGHT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("FORWARD", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display

}
/* Car move right Backward */
void Motor_R_Backward(void){
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 250);
						
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 250);
         
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("RIGHT", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("BACKWARD", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display
}

/* Car rotate right */
void Motor_R_Rotate(void){
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 300);
            
					  HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 300);
							HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 300);
         
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 300);
         		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("ROTATE", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("RIGHT", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display
}
/* Car rotate left */
void Motor_L_Rotate(void){
	            HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 300);
						
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2, GPIO_PIN_SET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 300);
							HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR3_PORT, MOTOR3_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 300);
		
						HAL_GPIO_WritePin(MOTOR4_PORT_A, MOTOR4_PIN1, GPIO_PIN_SET);
						HAL_GPIO_WritePin(MOTOR4_PORT_B, MOTOR4_PIN2, GPIO_PIN_RESET);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 300);
		
						SSD1306_Clear(); // Clear the display
						SSD1306_GotoXY(20, 20); // Set cursor position
						SSD1306_Puts("ROTATE", &Font_11x18, 1); // Display "Bluetooth"
						SSD1306_GotoXY(20, 40); // Move cursor to the next line
						SSD1306_Puts("LEFT", &Font_11x18, 1);
						SSD1306_UpdateScreen(); // Update the display

}
