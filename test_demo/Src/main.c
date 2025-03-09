/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "i2c_hal.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void LED_Disp(u8 dsLED);
void KEY_read(void);
void LED_proc(void);
void KEY_proc(void);
void Rx_proc(void);
void LCD_proc(void);
void RTC_proc(void);
void PWM_proc(void);
void DAC_proc(void);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// PWM frq duty
u32 pwm_tick = 0;
u32 pa3_frq = 1000;
u32 pa4_frq = 2000;
u8 pa3_duty = 50;
u8 pa4_duty = 50;
// Frequency Capture
extern uint32_t tim16_ch1_frq;
extern u8 tim16_ch1_duty;
extern uint32_t tim2_ch1_frq;
extern u8 tim2_ch1_duty;
// ADC value
extern float adc2_volat;
extern float adc1_volat;
extern float mcp_volat;
u8 mcp_num = 0;
// DAC value
u32 dac_tick = 0;
u32 dac_value = 0;
// UART buff
u8 rx_buff[30];
u8 rx_data;
u8 rx_pointer = 0;
u32 rx_tick = 0;
// LED status
u8 led_cnt = 0;
u32 led_tick = 0;
u32 led_num = 0;
u8 led_cnt1 = 0x01;
u8 led_cnt2 = 0x80;
// KEY status
u8 key_pwm_status = 1;
u8 key_dac_status = 1;
typedef struct
{
    u8 value, last, down, up;
    u8 down_flag;
    _Bool shot_flag;
    _Bool long_flag;
} KEY;
KEY key;
// EEPROM reset count
u8 reset_cnt = 0;
u8 reset_last = 0;
// RTC time
u32 rtc_tick = 0;
RTC_DateTypeDef D;
RTC_TimeTypeDef T;
RTC_TimeTypeDef T_start;

// LCD buff
#define frq_ui 1
#define adc_ui 2
#define pwm_ui 3
#define dac_ui 4
_Bool lcd_mode = 0;
u8 lcd_buff[30];
u8 ui = 0;
u32 lcd_tick = 0;
void LCD_proc()
{
    if (uwTick - lcd_tick < 100)
        return;
    lcd_tick = uwTick;
    // LCD_Clear(Black);

    memset(lcd_buff, 0, sizeof(lcd_buff));
    if (ui == frq_ui)
    {
        sprintf((char *)lcd_buff, "      FRQ TEST     ");
        LCD_DisplayStringLine(Line0, lcd_buff);

        sprintf((char *)lcd_buff, "   R39_F:%-5dHz     ", tim16_ch1_frq);
        LCD_DisplayStringLine(Line2, lcd_buff);
        sprintf((char *)lcd_buff, "   R39_D:%d %%     ", tim16_ch1_duty);
        LCD_DisplayStringLine(Line3, lcd_buff);

        sprintf((char *)lcd_buff, "   R40_F:%-5dHz     ", tim2_ch1_frq);
        LCD_DisplayStringLine(Line5, lcd_buff);
        sprintf((char *)lcd_buff, "   R40_D:%d %%     ", tim2_ch1_duty);
        LCD_DisplayStringLine(Line6, lcd_buff);
    }
    else if (ui == adc_ui)
    {
        sprintf((char *)lcd_buff, "      ADC TEST     ");
        LCD_DisplayStringLine(Line0, lcd_buff);
        sprintf((char *)lcd_buff, "   R37_V:%.2f V     ", adc2_volat);
        LCD_DisplayStringLine(Line2, lcd_buff);
        sprintf((char *)lcd_buff, "   R38_V:%.2f V     ", adc1_volat);
        LCD_DisplayStringLine(Line3, lcd_buff);
        sprintf((char *)lcd_buff, "   MCP_V:%.2f V     ", mcp_volat);
        LCD_DisplayStringLine(Line4, lcd_buff);
        LCD_SetTextColor(Green);
        sprintf((char *)lcd_buff, "   MCP_Num:%d       ", mcp_num);
        LCD_DisplayStringLine(Line6, lcd_buff);
        LCD_SetTextColor(White);
    }
    else if (ui == pwm_ui)
    {
        sprintf((char *)lcd_buff, "      PWM TEST     ");
        LCD_DisplayStringLine(Line0, lcd_buff);
        if (key_pwm_status == 1)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   PA3_F:%-5dHz        ", pa3_frq);
        LCD_DisplayStringLine(Line2, lcd_buff);
        LCD_SetBackColor(Black);
        if (key_pwm_status == 2)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   PA3_D:%-3d%%        ", pa3_duty);
        LCD_DisplayStringLine(Line3, lcd_buff);
        LCD_SetBackColor(Black);
        if (key_pwm_status == 3)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   PA4_F:%-5dHz        ", pa4_frq);
        LCD_DisplayStringLine(Line5, lcd_buff);
        LCD_SetBackColor(Black);
        if (key_pwm_status == 4)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   PA4_D:%-3d%%        ", pa4_duty);
        LCD_DisplayStringLine(Line6, lcd_buff);
        LCD_SetBackColor(Black);
    }
    else if (ui == dac_ui)
    {

        sprintf((char *)lcd_buff, "      DAC TEST     ");
        LCD_DisplayStringLine(Line0, lcd_buff);
        if (key_dac_status == 1)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   PA5_Num:%-4d       ", dac_value);
        LCD_DisplayStringLine(Line2, lcd_buff);
        LCD_SetBackColor(Black);
        if (key_dac_status == 2)
            LCD_SetBackColor(Green);
        sprintf((char *)lcd_buff, "   RES_Num:%-3d       ", reset_last);
        LCD_DisplayStringLine(Line4, lcd_buff);
        LCD_SetBackColor(Black);
        sprintf((char *)lcd_buff, "   RTC_Num:");
        LCD_DisplayStringLine(Line6, lcd_buff);
        if (key_dac_status == 3)
            LCD_SetBackColor(Green);
        LCD_DisplayChar(Line6, 16 * 9, T_start.Hours / 10 + '0');
        LCD_DisplayChar(Line6, 16 * 8, T_start.Hours % 10 + '0');
        LCD_SetBackColor(Black);
        LCD_DisplayChar(Line6, 16 * 7, '-');
        if (key_dac_status == 4)
            LCD_SetBackColor(Green);
        LCD_DisplayChar(Line6, 16 * 6, T_start.Minutes / 10 + '0');
        LCD_DisplayChar(Line6, 16 * 5, T_start.Minutes % 10 + '0');
        LCD_SetBackColor(Black);
        LCD_DisplayChar(Line6, 16 * 4, '-');
        if (key_dac_status == 5)
            LCD_SetBackColor(Green);
        LCD_DisplayChar(Line6, 16 * 3, T_start.Seconds / 10 + '0');
        LCD_DisplayChar(Line6, 16 * 2, T_start.Seconds % 10 + '0');
        LCD_SetBackColor(Black);
    }
    sprintf((char *)lcd_buff, "      %02d-%02d-%02d     ", T.Hours, T.Minutes, T.Seconds);
    LCD_DisplayStringLine(Line8, lcd_buff);
    sprintf((char *)lcd_buff, "           RESET:%03d", reset_cnt);
    LCD_DisplayStringLine(Line9, lcd_buff);
}
u32 key_long_tick = 0;
u32 key_tick = 0;
void KEY_proc()
{
    if (uwTick - key_tick < 20)
        return;
    key_tick = uwTick;
    KEY_read();
    if (key.down == 3 || key.down == 4)
    {
        key_long_tick = uwTick;
    }
    if (key.value == 3 && uwTick - key_long_tick >= 800)
    {
        if (ui == adc_ui && mcp_num < 127)
        {
            mcp_num += 1;
        }
        else if (ui == dac_ui)
        {
            if (key_dac_status == 2)
                reset_last++;
            else if (key_dac_status == 3 && T_start.Hours < 24)
                T_start.Hours++;
            else if (key_dac_status == 4 && T_start.Minutes < 59)
                T_start.Minutes++;
            else if (key_dac_status == 5 && T_start.Seconds < 59)
                T_start.Seconds++;
            else if (key_dac_status == 1 && dac_value < 4095)
            {
                dac_value += 40;
                if (dac_value > 4095)
                    dac_value = 4095;
            }
        }
    }
    else if (key.value == 4 && uwTick - key_long_tick >= 800)
    {
        if (ui == adc_ui && mcp_num > 0)
        {
            mcp_num -= 1;
        }
        else if (ui == dac_ui)
        {
            if (key_dac_status == 2 && reset_last != 0)
                reset_last--;
            else if (key_dac_status == 3 && T_start.Hours > 0)
                T_start.Hours--;
            else if (key_dac_status == 4 && T_start.Minutes > 0)
                T_start.Minutes--;
            else if (key_dac_status == 5 && T_start.Seconds > 0)
                T_start.Seconds--;
            else if (key_dac_status == 1 && dac_value > 0)
            {
                dac_value -= 40;
                if (dac_value > 4095)
                    dac_value = 0;
            }
        }
    }

    if (key.down == 1)
    {
        key.down_flag = 1;
        led_cnt = 0;
        ui++;
        if (ui == 5)
            ui = 1;
        LCD_Clear(Black);
        if (ui == frq_ui)
        {
            reset_cnt = reset_last;
            EEP_write(0xff, reset_cnt);
        }
    }
	
    else if (key.down == 2)
    {
        if (ui == frq_ui)
        {
            key.down_flag = 2;
            if (led_cnt != 0x55)
                led_cnt = 0x55;
            else
                led_cnt = 0xaa;
        }
        else if (ui == adc_ui)
        {
            if (mcp_num != 0)
                mcp_num = 0;
            else
                mcp_num = 127;
            EEP_write(0x5e, mcp_num);
            MCP_write(mcp_num);
        }
        else if (ui == pwm_ui)
        {
            key_pwm_status++;
            if (key_pwm_status == 5)
                key_pwm_status = 1;
        }
        else if (ui == dac_ui)
        {
            key_dac_status++;
            if (key_dac_status == 6)
                key_dac_status = 1;
        }
    }
    else if (key.up == 3)
    {
        if (ui == frq_ui)
            key.down_flag = 3;

        if (ui == adc_ui)
        {
            mcp_num += 1;
            if (mcp_num > 255)
                mcp_num = 0;
            EEP_write(0x5e, mcp_num);
            MCP_write(mcp_num);
        }
        else if (ui == pwm_ui)
        {
            if (key_pwm_status == 1 && pa3_frq < 10000)
                pa3_frq += 1000;
            else if (key_pwm_status == 3 && pa4_frq < 10000)
                pa4_frq += 1000;
            else if (key_pwm_status == 2 && pa3_duty < 90)
                pa3_duty += 10;
            else if (key_pwm_status == 4 && pa4_duty < 90)
                pa4_duty += 10;
        }
        else if (ui == dac_ui)
        {
            if (key_dac_status == 2)
                reset_last++;
            else if (key_dac_status == 3 && T_start.Hours < 23)
            {
                T_start.Hours++;
                EEP_write(0x10, T_start.Hours);
            }
            else if (key_dac_status == 4 && T_start.Minutes < 59)
            {
                T_start.Minutes++;
                EEP_write(0x20, T_start.Minutes);
            }
            else if (key_dac_status == 5 && T_start.Seconds < 59)
            {
                T_start.Seconds++;
                EEP_write(0x30, T_start.Seconds);
            }
            else if (key_dac_status == 1 && dac_value < 4095)
            {
                dac_value += 40;
                if (dac_value > 4095)
                    dac_value = 4095;
                EEP_write(0x40, dac_value >> 8);
                EEP_write(0x50, dac_value);
            }
        }
    }
    else if (key.up == 4)
    {
        if (ui == frq_ui)
            key.down_flag = 4;
        if (ui == adc_ui)
        {
            mcp_num -= 1;
            if (mcp_num > 127)
                mcp_num = 127;
            EEP_write(0x5e, mcp_num);
            MCP_write(mcp_num);
        }
        else if (ui == pwm_ui)
        {
            if (key_pwm_status == 1 && pa3_frq > 1000)
                pa3_frq -= 1000;
            else if (key_pwm_status == 3 && pa4_frq > 1000)
                pa4_frq -= 1000;
            else if (key_pwm_status == 2 && pa3_duty > 10)
                pa3_duty -= 10;
            else if (key_pwm_status == 4 && pa4_duty > 10)
                pa4_duty -= 10;
        }
        else if (ui == dac_ui)
        {
            if (key_dac_status == 2 && reset_last != 0)
			{
                reset_last--;
				
			}
            else if (key_dac_status == 3 && T_start.Hours > 0)
            {
                T_start.Hours--;
                EEP_write(0x10, T_start.Hours);
            }
            else if (key_dac_status == 4 && T_start.Minutes > 0)
            {
                T_start.Minutes--;
                EEP_write(0x20, T_start.Minutes);
            }
            else if (key_dac_status == 5 && T_start.Seconds > 0)
            {
                T_start.Seconds--;
                EEP_write(0x30, T_start.Seconds);
            }
            else if (key_dac_status == 1 && dac_value > 0)
            {
                dac_value -= 40;
                if (dac_value > 4095)
                    dac_value = 0;
                EEP_write(0x40, dac_value >> 8);
                EEP_write(0x50, dac_value);
            }
        }
    }
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_RTC_Init();
    MX_TIM2_Init();
    MX_TIM16_Init();
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    MX_TIM7_Init();
    MX_TIM8_Init();
    MX_DAC1_Init();
    /* USER CODE BEGIN 2 */

    LCD_Init();
    I2CInit();
    HAL_UART_Receive_IT(&huart1, &rx_data, 1);
    HAL_TIM_Base_Start_IT(&htim7);
    HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    LCD_Clear(Blue);
    reset_cnt = EEP_read(0xff) + 1 ;
    if (reset_cnt != 0)
    {
        mcp_num = EEP_read(0x5e);
		if(mcp_num > 127)
			mcp_num = 0;
        T_start.Hours = EEP_read(0x10);
        T_start.Minutes = EEP_read(0x20);
        T_start.Seconds = EEP_read(0x30);
        if (!(T_start.Hours < 24 && T_start.Minutes < 60 && T_start.Seconds < 60))
        {
            T_start.Hours = 12;
            T_start.Minutes = 59;
            T_start.Seconds = 55;
        }
        HAL_RTC_SetTime(&hrtc, &T_start, RTC_FORMAT_BIN);
        dac_value = EEP_read(0x40) << 8 | EEP_read(0x50);
        if (dac_value > 4095)
            dac_value = 0;
    }
    reset_last = reset_cnt;
    EEP_write(0xff, reset_cnt);
	MCP_write(mcp_num);
    // hrtc.sTime.Hours = 0x11;
    // sTime.Minutes = 0x59;
    // sTime.Seconds = 0x55;
    printf("Hello World\r\n");
    printf("你好，世界\r\n");

    LCD_SetBackColor(White);
    LCD_DisplayStringLine(Line0, (unsigned char *)"                    ");
    LCD_SetBackColor(Black);
    LCD_DisplayStringLine(Line1, (unsigned char *)"                    ");
    LCD_SetBackColor(Grey);
    LCD_DisplayStringLine(Line2, (unsigned char *)"                    ");
    LCD_SetBackColor(Blue);
    LCD_DisplayStringLine(Line3, (unsigned char *)"                    ");
    LCD_SetBackColor(Blue2);
    LCD_DisplayStringLine(Line4, (unsigned char *)"                    ");
    LCD_SetBackColor(Red);
    LCD_DisplayStringLine(Line5, (unsigned char *)"                    ");
    LCD_SetBackColor(Magenta);
    LCD_DisplayStringLine(Line6, (unsigned char *)"                    ");
    LCD_SetBackColor(Green);
    LCD_DisplayStringLine(Line7, (unsigned char *)"                    ");
    LCD_SetBackColor(Cyan);
    LCD_DisplayStringLine(Line8, (unsigned char *)"                    ");
    LCD_SetBackColor(Yellow);
    LCD_DisplayStringLine(Line9, (unsigned char *)"                    ");
    HAL_Delay(1000);
    ui = 1;
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_Clear(Black);
    while (1)
    {
        KEY_proc();
        LED_proc();
        Rx_proc();
        LCD_proc();
        PWM_proc();
        RTC_proc();
        DAC_proc();
        // ADC_proc(); // 这里在tim.c里面有这个函数，但是我放到定时器里面可以学习定时的使用方法
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
    RCC_OscInitStruct.PLL.PLLN = 20;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

void DAC_proc()
{
    if (uwTick - dac_tick < 100)
        return;
    dac_tick = uwTick;
    HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, dac_value);
    HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
}
void PWM_proc()
{
    if (uwTick - pwm_tick < 100)
        return;
    TIM2->ARR = 1e6 / pa3_frq - 1;
    TIM2->CCR4 = (TIM2->ARR + 1) * pa3_duty / 100;
    TIM3->ARR = 1e6 / pa4_frq - 1;
    TIM3->CCR2 = (TIM3->ARR + 1) * pa4_duty / 100;
}
void RTC_proc()
{
    if (uwTick - rtc_tick < 500)
        return;
    rtc_tick = uwTick;
    HAL_RTC_GetTime(&hrtc, &T, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &D, RTC_FORMAT_BIN);
}
void LED_proc()
{
    if (uwTick - led_tick < 100)
        return;
    led_tick = uwTick;
    if (key.down_flag == 3)
    {
        led_cnt = led_cnt1;
        led_cnt1 = led_cnt1 << 1;
        if (led_cnt1 == 0)
            led_cnt1 = 0x01;
    }
    else if (key.down_flag == 4)
    {
        led_cnt = led_cnt2;
        led_cnt2 = led_cnt2 >> 1;
        if (led_cnt2 == 0)
            led_cnt2 = 0x80;
    }
    LED_Disp(led_cnt);
}

void Rx_proc()
{
    if (uwTick - rx_tick < 50)
        return;
    rx_tick = uwTick;
    if (rx_pointer == 1 && rx_buff[0] == '#')
    {
        lcd_mode = !lcd_mode;
        if (lcd_mode == 0)
        {
            LCD_WriteReg(R1, 0x0000);
            LCD_WriteReg(R96, 0x2700);
            LCD_Clear(Black);
        }
        else
        {
            LCD_WriteReg(R1, 0x0100);
            LCD_WriteReg(R96, 0xA700);
            LCD_Clear(Black);
        }
        printf("成功翻转屏幕\r\n");
    }
    else if (rx_pointer > 0)
    {
        printf("%s\r\n", rx_buff);
        printf("发送#字符翻转屏幕\r\n");
    }
    rx_pointer = 0;
    memset(rx_buff, '\0', sizeof(rx_buff));
}
void LED_Disp(u8 dsLED)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, dsLED << 8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}
void KEY_read()
{
    if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
        key.value = 1;
    else if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
        key.value = 2;
    else if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)
        key.value = 3;
    else if (HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) == 0)
        key.value = 4;
    else
        key.value = 0;
    key.down = key.value & (key.value ^ key.last);
    key.up = ~key.value & (key.value ^ key.last);
    key.last = key.value;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
