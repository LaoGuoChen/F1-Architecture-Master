/**
  ******************************************************************************
  * @file    app_hal_init.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   接口层初始化
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __HWJ_HALINIT_H
#define  __HWJ_HALINIT_H

#ifdef __cplusplus
extern "C" {
#endif
	
    
/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "api_usart.h"
#include "app_heart_led.h"
#include "app_magnetic_encoder.h"
#include "api_can.h"
#include "api_spi.h"
#include "stm32f10x_can_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/    
extern dev_heart_led_desc_t    g_stDev_Heart_Led_Desc;
extern magnetic_encoder_desc_t g_stMagnetic_Encoder_Desc;
extern drive_usart_desc_t      g_stComm_Lidar_Board_Ctl;
extern drive_can_desc_t        g_stComm_Can_Bus; 
extern drive_spi_desc_t        g_stSpi_Flash_Dev;
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ModulesHalInit(void);
    
    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
