/**
  ******************************************************************************
  * @file    app_hal_init.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   �ӿڲ��ʼ��
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_hal_init.h"

/* Private variables ---------------------------------------------------------*/
dev_heart_led_desc_t    g_stDev_Heart_Led_Desc =    {0};
magnetic_encoder_desc_t g_stMagnetic_Encoder_Desc = {0};
drive_usart_desc_t      g_stComm_Lidar_Board_Ctl  = {0};
drive_can_desc_t        g_stComm_Can_Bus          = {0};
drive_spi_desc_t        g_stSpi_Flash_Dev         = {0};
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ģ��Ӳ����ʼ��
  * @param  None
  * @retval None
  */
void ModulesHalInit(void)
{
    drive_usart_desc_t usart1_debug = {0};
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      ///<ʹ�ܸ��ù���ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); /*!<ʹ��SWD ����JTAG*/	
	DBGMCU->CR  &= ~((uint32_t)1<<5);    
	AFIO->MAPR = (AFIO->MAPR & ~((uint32_t)0x7 << 24)) | (2 << 24);     /*!<  PA15 PB3 PB4 */
    
    /*!< ��������ʼ�� */
	#if MAGNETIC_ENCODER_EN	
        if (SIGNED_TYPE_ERR == Magnetic_Encoder_Init(&g_stMagnetic_Encoder_Desc))
        {
            xEventGroupSetBits(g_xCreatedEventGroup, (HAL_INIT_ERR | HAL_INIT_ME_ERR));
        }
	#endif	
	
    /*!< ���������Ƴ�ʼ�� */
    #if HEART_LED_EN
        drv_heart_led_init(&g_stDev_Heart_Led_Desc);
    #endif
    
    /*!< ����debug��ʼ�� */
    #if USART1_EN
        Api_Init_Usart(&usart1_debug, 1, 0, 115200);
        usart1_debug.set_usart_print(usart1_debug.usart_id);
    #endif
    
    #if USART5_EN
        Api_Init_Usart(&g_stComm_Lidar_Board_Ctl, 5, 0, 115200);
    #endif
    
    #if 1 //CAN_EN
        drive_can_init(&g_stComm_Can_Bus, 2);
    #endif
	/*!< �����ʼ�� */
	#if MOTOR_EN		
			
	#endif	
	
	/*!< ��Դ��ʼ�� */
	#if POWER_EN		
			
	#endif	

    if (SIGNED_TYPE_ERR == Api_Init_Spi(&g_stSpi_Flash_Dev, 2, 0))
    {
        xEventGroupSetBits(g_xCreatedEventGroup, (TASK_TEST_ERR | TASK_TEST_CREATE_ERR));
    }
	
}


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
