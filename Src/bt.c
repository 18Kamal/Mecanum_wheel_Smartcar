#include "bt.h"
#include "pwm.h"
#include "display.h"
#include "motor.h"
#include "ssd1306.h"
#include "fonts.h"
#include "servo.h"
#include "ultrasonic.h"
#include "ir.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;


void MX_USART1_UART_Init(void) {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

void Bluetooth_StartReception(void) {
    HAL_UART_Receive_IT(&huart1, &hbluetooth.buffer[hbluetooth.head], 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart->Instance == USART1) {
        // Update buffer index
        hbluetooth.head = (hbluetooth.head + 1) % BT_BUFFER_SIZE;
        
        // Set status to ready if buffer was empty
        if(hbluetooth.status == BT_IDLE) {
            hbluetooth.status = BT_CMD_READY;
        }
        
        // Restart reception
        HAL_UART_Receive_IT(huart, &hbluetooth.buffer[hbluetooth.head], 1);
    }
}

void bluetooth_control(uint8_t cmd) {
    // Mode switching commands
    if (cmd == 'Z') {
        currentMode = MODE_AUTO;
        Motor_Stop();
        SSD1306_Clear();
        SSD1306_GotoXY(10, 40);
        SSD1306_Puts("AUTO MODE", &Font_7x10, 1);
        SSD1306_UpdateScreen();
        return;
    } 
    else if (cmd == 'C') {
        currentMode = MODE_MANUAL;
        SSD1306_Clear();
        SSD1306_GotoXY(10, 40);
        SSD1306_Puts("MANUAL MODE", &Font_7x10, 1);
        SSD1306_UpdateScreen();
        return;
    }

    // Only process movement commands in manual mode
    if (currentMode == MODE_MANUAL) {


 // If in safety override, only allow B/L/R commands
    if (safety_override) {
        switch(cmd) {
            case 'B': 
            case 'L': 
            case 'R':
                // These commands clear the safety override
                safety_override = 0;
                SSD1306_Clear();
                SSD1306_GotoXY(10, 40);
                SSD1306_Puts("SAFETY CLEARED", &Font_7x10, 1);
                SSD1306_UpdateScreen();
                HAL_Delay(1000);
                break;
            default:
                return;
        }
    }

        // Process movement commands
        switch(cmd) {
            case 'F': Motor_Forward(); break;
            case 'B': Motor_Backward(); HAL_Delay(500); break;
            case 'L': Motor_Left(); break;
            case 'R': Motor_Right(); break;
            case 'S': Motor_Stop(); break;
            case 'K': Motor_L_Forward(); break;
            case 'M': Motor_L_Backward(); break;
            case 'A': Motor_R_Forward(); break;
            case 'J': Motor_R_Backward(); break;
            case 'N': Motor_L_Rotate(); break;
            case 'E': Motor_R_Rotate(); break;
            default: break;
        }
    }
}