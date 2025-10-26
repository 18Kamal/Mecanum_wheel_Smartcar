#ifndef BT_H
#define BT_H

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "modes.h"

// Buffer size for Bluetooth commands
#define BT_BUFFER_SIZE 32

// Bluetooth status flags
typedef enum {
    BT_IDLE,
    BT_CMD_READY,
    BT_CMD_PROCESSED
} BT_StatusTypeDef;

// Bluetooth control structure
typedef struct {
    uint8_t buffer[BT_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile BT_StatusTypeDef status;
} Bluetooth_HandleTypeDef;

extern Bluetooth_HandleTypeDef hbluetooth;
extern OperationMode_t currentMode;

void MX_USART1_UART_Init(void);
void Bluetooth_StartReception(void);
void bluetooth_control(uint8_t cmd);

#endif