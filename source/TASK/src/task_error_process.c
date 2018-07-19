/**
  ******************************************************************************
  * @file    task_error_process.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief    错误处理线程业务
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "task_error_process.h"
#include "common.h"
#include "app_hal_init.h"
#include "stm32f10x_can_config.h"

#include "FreeRTOS.h"
#include "task.h"

#include "event_groups.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  错误处理线程入口
  * @param  None
  * @retval None
  */
void vErrorProcessTask ( void * pvParameters )
{
//    EventBits_t ret_error_data = 0;

    
    while (1)
    {
        /*!< 等待事件标志组 */
//		ret_error_data = 
        xEventGroupWaitBits(g_xCreatedEventGroup,                                             ///< 事件标志组对象
                                             0xffffffffUL,                                    ///< 等待任何错误事件
                                             pdTRUE,                                          ///< 事件发生后把所有位均清零
                                             pdFALSE,                                         ///< 等待任何被置位
                                             portMAX_DELAY); 	                              ///< 无期限等待
        
        g_stDev_Heart_Led_Desc.heart_led_ctl_error = 0;

        vTaskDelay( 10 / portTICK_RATE_MS );
    }
}
