/**
  ******************************************************************************
  * @file    task_error_process.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief    �������߳�ҵ��
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
  * @brief  �������߳����
  * @param  None
  * @retval None
  */
void vErrorProcessTask ( void * pvParameters )
{
//    EventBits_t ret_error_data = 0;

    
    while (1)
    {
        /*!< �ȴ��¼���־�� */
//		ret_error_data = 
        xEventGroupWaitBits(g_xCreatedEventGroup,                                             ///< �¼���־�����
                                             0xffffffffUL,                                    ///< �ȴ��κδ����¼�
                                             pdTRUE,                                          ///< �¼������������λ������
                                             pdFALSE,                                         ///< �ȴ��κα���λ
                                             portMAX_DELAY); 	                              ///< �����޵ȴ�
        
        g_stDev_Heart_Led_Desc.heart_led_ctl_error = 0;

        vTaskDelay( 10 / portTICK_RATE_MS );
    }
}
