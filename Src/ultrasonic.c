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
#include "modes.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;
volatile uint16_t distance = 0;
volatile uint8_t safety_override = 0;


uint32_t pMillis;
uint32_t val1 = 0;
uint32_t val2 = 0;

void MX_TIM1_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);
	
	  /*Configure GPIO pins : PB10  */
  GPIO_InitStruct.Pin = TRIG_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TRIG_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin : PB11 */
  GPIO_InitStruct.Pin = ECHO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ECHO_PORT, &GPIO_InitStruct);
	
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void MX_US_Start(void){
	HAL_TIM_Base_Start(&htim1);
  HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
}

float Ultrasonic_GetDistance(void) {
    uint32_t start, end;
    
    // Send a 10µs pulse to trigger
    HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < 10);
    HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

    // Wait for echo signal (timeout = 20ms)
    uint32_t timeout = HAL_GetTick();
    while (!HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) && (HAL_GetTick() - timeout < 20));
    start = __HAL_TIM_GET_COUNTER(&htim1);
    
    timeout = HAL_GetTick();
    while (HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) && (HAL_GetTick() - timeout < 20));
    end = __HAL_TIM_GET_COUNTER(&htim1);

    // Convert to distance in cm
    float distance = (end - start) * 0.034 / 2;
    
    if (distance < 2 || distance > 400) {  // Out of range
        return -1;
    }
    
    return distance;
}


void Ultrasonic_Update(void){
    float distance = Ultrasonic_GetDistance();

    
    // Display the distance
    char buffer[20];
    if (distance >= 0 && distance <= 20) {
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_1, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_2, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_4, 0);
						PWM_SetDutyCycle(&htim3, TIM_CHANNEL_3, 0);
						Servo_ult();
						safety_override = 1;
    } 
}

uint8_t Safety_GetStatus(void){
return safety_override;
}

void Safety_clearOverride(void){
safety_override =0;
}