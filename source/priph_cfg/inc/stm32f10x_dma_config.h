/**
  ******************************************************************************
  * @file    stm32f10x_dma_config.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio����ģ��
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_DMA_CONFIG_H
#define  __STM32F10x_DMA_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  ADC1��DMA����
  * @param  None
  * @retval None
  */
void DMA_ADC1_Config(void);
/**
  * @brief  ADC3��DMA����
  * @param  None
  * @retval None
  */
void DMA_ADC3_Config(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
