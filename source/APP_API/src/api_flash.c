/**
  ******************************************************************************
  * @file    api_flash.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   flashӦ�ýӿڲ�
  ******************************************************************************
  */
#include "api_flash.h"
#include "stm32f10x_spi_config.h"
#include "stm32f10x_flash_config.h"
  
/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  ��ʼ��spi_flash
  * @param  spi_id:spi���
  * @param  remap_par:��ӳ�����
  * @retval None
  */
void Spi_Flash_Init (drive_flash_desc_t *handle, const u8 spi_id, const u8 remap_par)
{
    InitSpi(spi_id, remap_par);
    handle->spi_flash_erase      = Spi_Flash_Sector_Erase;
    handle->spi_flash_power_down = Spi_Flash_Power_Down;
    handle->spi_flash_read       = Spi_Flash_Buffer_Read;
    handle->spi_flash_write      = Spi_Flash_Buffer_Write;
#if STM32_FLASH_WRITE_EN
    handle->stm_flash_read       = Stm_Flash_Read;
    handle->stm_flash_write      = Stm_flash_Write;
#endif    
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
