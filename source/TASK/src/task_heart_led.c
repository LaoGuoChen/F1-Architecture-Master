/**
  ******************************************************************************
  * @file    task_heart_led.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   心跳灯任务
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include  "task_heart_led.h"
#include  "app_hal_init.h"

#include  "FreeRTOS.h"
#include  "task.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  心跳灯任务函数
  * @param  None
  * @retval None
  */
void vHeartLedTask( void * pvParameters )
{   
    while (1)
    {
        if ( g_stDev_Heart_Led_Desc.heart_led_ctl_status == CTL_LED_NOMAL)
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_1);  /* ON */
            vTaskDelay( 100 / portTICK_RATE_MS );
            GPIO_SetBits(GPIOE, GPIO_Pin_1);    /* OFF */
            vTaskDelay( 900 / portTICK_RATE_MS );
        }
        else if ( g_stDev_Heart_Led_Desc.heart_led_ctl_status == CTL_LED_BUSY)
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_1);  /* ON */
            vTaskDelay( 100 / portTICK_RATE_MS );
            GPIO_SetBits(GPIOE, GPIO_Pin_1);    /* OFF */
            vTaskDelay( 150 / portTICK_RATE_MS );
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_1);  /* ON */
            vTaskDelay( 100 / portTICK_RATE_MS );
        }
    }
}
