/**
  ******************************************************************************
  * @file    stm32f10x_spi_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   spi����ģ��
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F10x_SPI_CONFIG_H
#define  __STM32F10x_SPI_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private functions ---------------------------------------------------------*/
    
/**
  * @brief  ��ʼ��spi
  * @param  spi_id:spi���
  * @param  remap_par:��ӳ�����
  * @retval None
  */
void InitSpi(const u8 spi_id, const u8 remap_par);
/**
  * @brief  ����spi flash��Ƭѡ�źŵ�ƽ
  * @param  spi_id:spi���
  * @retval None
  */
void Set_Spi_Flash_Cs(u8 cs_level);

#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2016 HWJ *****END OF FILE****/

