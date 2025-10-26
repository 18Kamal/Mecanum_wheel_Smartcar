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
#include "stdio.h"

extern TIM_HandleTypeDef htim2;

void MX_TIM2_Init(void){
   __HAL_RCC_GPIOA_CLK_ENABLE();


/* Configure PA1, PA2, PA3 as PWM Output */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 ;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	


  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};


  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 20000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim2);

}

void servopwm_start(){
 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}
void SetServoAngle(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    uint16_t pulse_width = 500 + (angle * 2000 / 180);  // Convert angle to pulse width (500us to 2500us)
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse_width);
}

void Servo_ult() {
    SetServoAngle(90);  // Center
    HAL_Delay(500);
    
    SetServoAngle(180); // Right
    HAL_Delay(500);
    float right_distance = Ultrasonic_GetDistance();
    
    SetServoAngle(90);  // Center
    HAL_Delay(500);
    
    SetServoAngle(0);   // Left
    HAL_Delay(500);
    float left_distance = Ultrasonic_GetDistance();
    
    SetServoAngle(90);  // Return to center
    HAL_Delay(500);
    
    // Display scan results
    char scan_msg[30];
    snprintf(scan_msg, sizeof(scan_msg), "L:%.1fcm R:%.1fcm", left_distance, right_distance);
    SSD1306_GotoXY(5, 50);
    SSD1306_Puts(scan_msg, &Font_7x10, 1);
    SSD1306_UpdateScreen();
}