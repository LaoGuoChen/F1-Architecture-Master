/**
  ******************************************************************************
  * @file    project_main.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ����������
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#include "app_hal_init.h"
#include "app_heart_led.h"

#include "task_heart_led.h"
#include "task_motor_control.h"
#include "task_error_process.h"
#include "task_can_receive.h"
#include "task_test.h"

#include "FreeRTOS.h"
#include "task.h"

#include "event_groups.h"

/* Private variables ---------------------------------------------------------*/
/********************************** �ں˶����� *******************************/
EventGroupHandle_t g_xCreatedEventGroup = NULL;

/* Private define ------------------------------------------------------------*/
/*********************************** �������ȼ� ********************************/
#define vSTARTTask_PRIORITY							( ( unsigned portBASE_TYPE ) 2U )	//2
#define vHeartLedTask_PRIORITY						( ( unsigned portBASE_TYPE ) 3U )	//3
#define vMotorCtlTask_PRIORITY						( ( unsigned portBASE_TYPE ) 8U )	//8
#define vCanReceiveTask_PRIORITY					( ( unsigned portBASE_TYPE ) 9U )	//9
#define vErrorProcessTask_PRIORITY                  ( ( unsigned portBASE_TYPE ) 10U)	//10
#define vTestTask_PRIORITY                          ( ( unsigned portBASE_TYPE ) 11U)	//11

/* Private functions ---------------------------------------------------------*/
/********************************** ���������� *******************************/
static void vStartTask   ( void * pvParameters );

/**
  * @brief  ������
  * @param  None
  * @retval None
  */
int main ( void )
{	    
	/*!< ������ʼ���� */
	xTaskCreate( vStartTask, "Task Start", configMINIMAL_STACK_SIZE, NULL, vSTARTTask_PRIORITY, NULL);

	/*!< �������������������FreeRTOSϵͳ */
    vTaskStartScheduler();

}

/**
  * @brief  ������ʼ������
  * @param  None
  * @retval None
  */
static void vStartTask( void * pvParameters )                   
{	
    BaseType_t ret_status = 0;
    
    /*!< ���������ź��� */
	g_xCreatedEventGroup = xEventGroupCreate();
    xTaskCreate( vErrorProcessTask, "Error Process Task",    512, NULL, vErrorProcessTask_PRIORITY, NULL);
    
    /*!< ģ���ʼ�� */
    ModulesHalInit();
    
    /*!< ����Ӧ������ */
    ret_status = xTaskCreate( vCanReceiveTask,   "The Task Of Can Receive",512, NULL, vCanReceiveTask_PRIORITY,   NULL);
    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_CAN_RECEIVE_ERR | TASK_CAN_RECEIVE_CREATE_ERR));
    }
    
	ret_status = xTaskCreate( vHeartLedTask,     "The Task Of Heart Led",  512, NULL, vHeartLedTask_PRIORITY,     NULL);
    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_HEART_LED_ERR | TASK_HEART_LED_CREATE_ERR));
    }
    
 	ret_status = xTaskCreate( vMotorCtlTask,     "Motor Control Task",     512, NULL, vMotorCtlTask_PRIORITY,     NULL);
    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_MOTOR_CTL_ERR | TASK_MOTOR_CTL_CREATE_ERR));
    }
    
    ret_status = xTaskCreate( vTestTask,         "Test Task",              512,  NULL, vTestTask_PRIORITY,         NULL);
    if (pdPASS != ret_status)
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_MOTOR_CTL_ERR | TASK_MOTOR_CTL_CREATE_ERR));
    }

    g_stDev_Heart_Led_Desc.heart_led_ctl_nomal(&g_stDev_Heart_Led_Desc);
    vTaskDelete(NULL);		///< ���Լ�ɾ��
}

