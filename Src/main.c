#include "main.h"
#include "bt.h"
#include "pwm.h"
#include "display.h"
#include "motor.h"
#include "ssd1306.h"
#include "fonts.h"
#include "servo.h"
#include "ir.h"
#include "ultrasonic.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include "modes.h"

// Global variables
OperationMode_t currentMode = MODE_MANUAL;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;

// Bluetooth control structure
Bluetooth_HandleTypeDef hbluetooth = {0};

void SystemClock_Config(void);

int main(void)
{
    // HAL Initialization
    HAL_Init();
    SystemClock_Config();

    // Peripheral Initialization
    MX_Motor_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    MX_TIM2_Init();
    MX_TIM1_Init();

    // Start peripherals
    HAL_TIM_Base_Start(&htim1);
    HAL_TIM_Base_Start_IT(&htim1);
    PWM_Start();
    servopwm_start();
    MX_Ir_Init();
    SSD1306_Init();
    MX_US_Start();

    // Start Bluetooth reception
    Bluetooth_StartReception();

    // Display initialization message
    SSD1306_Clear();
    SSD1306_GotoXY(10, 20);
    SSD1306_Puts("Bluetooth", &Font_11x18, 1);
    SSD1306_GotoXY(10, 40);
    SSD1306_Puts("Connecting...", &Font_11x18, 1);
    SSD1306_UpdateScreen();
    HAL_Delay(2000);


    while (1)
    {
       Ultrasonic_Update();
			
        if(hbluetooth.status == BT_CMD_READY)
        {
            uint8_t cmd = hbluetooth.buffer[hbluetooth.tail];
            hbluetooth.tail = (hbluetooth.tail + 1) % BT_BUFFER_SIZE;
            
            if(hbluetooth.tail == hbluetooth.head)
            {
                hbluetooth.status = BT_IDLE;
            }
            
            bluetooth_control(cmd);
        }
        
        // Run auto control if in auto mode
        if(currentMode == MODE_AUTO)
        {
            Auto_Control();
        }
        
        // Add small delay to prevent CPU overload
        HAL_Delay(10);
    }
}

// Timer callback for periodic tasks
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
     
    }
}



// System Clock Configuration (unchanged)
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

// Error Handler (unchanged)
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation */
}
#endif /* USE_FULL_ASSERT */