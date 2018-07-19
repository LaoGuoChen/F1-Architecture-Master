/**
  ******************************************************************************
  * @file    stm32f10x_gpio_config.h
  * @author  êÌÖÇÐÛ  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio¹¦ÄÜÄ£¿é
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F10x_GPIO_CONFIG_H
#define  __STM32F10x_GPIO_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif
    
    
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void pinMode(GPIO_TypeDef* GPIOx,
	uint16_t pin,
	GPIOMode_TypeDef mode,
	GPIOSpeed_TypeDef GPIO_Speed
);
    
    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

