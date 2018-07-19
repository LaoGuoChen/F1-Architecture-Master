/**
  ******************************************************************************
  * @file    api_flash.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   flashӦ�ýӿڲ�
  ******************************************************************************
  */
  
#ifndef  __API_FLASH_H
#define  __API_FLASH_H

/* Define to prevent recursive inclusion -------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif 
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
/*
// <q>STM32_FLASH_WRITE_EN
*/
#define STM32_FLASH_WRITE_EN  1
// <o>FLASH_SPI_ID <1-3>
// <i>The ID Bum of Spi to Flash
#define  FLASH_SPI_ID  2
// *** <<< End of Configuration section             >>> ***  

#define EXPAND_WRAPPER( __NEXTLEVEL__, ...)  __NEXTLEVEL__( __VA_ARGS__ )
#define  _GET_SPI(x)   SPI##x
#define  GET_SPI(x)    EXPAND_WRAPPER(_GET_SPI, x)
    
#define FLASH_CHIP_WRITE_ENABLE             0x06 
#define FLASH_CHIP_READ_STATAUS_REG         0x05 
#define FLASH_CHIP_WIP_FLAG                 0x01  /* Write In Progress (WIP) flag */
#define FLASH_CHIP_POWER_DOWN_ADDR          0xB9
#define FLASH_CHIP_SECTOR_ERASE             0x20
#define FLASH_CHIP_PAGE_PROGRAM	            0x02 
#define FLASH_CHIP_PER_WRITE_PAGE_SIZE      256
#define FLASH_CHIP_PAGE_SIZE                256
#define FLASH_CHIP_READ_DATA                0x03   
    
/** 
  * stm_flash_read:���ڲ�flashָ����ַ��ʼ����ָ�����ȵ����� \n
  * stm_flash_write:���ڲ�flashָ����ַ��ʼд��ָ�����ȵ����� \n
  * spi_flash_write:д���ݽ��ⲿflash \n
  * spi_flash_read:�������豸�Ĵ��ں�,��USBAT1�򴮿ں�Ϊ1 \n
  * Spi_Flash_Sector_Erase: ����flash������ \n
  * Spi_Flash_Power_Down: flash�������ģʽ \n
  */
typedef struct drive_flash_desc drive_flash_desc_t;
    
struct drive_flash_desc{
#if STM32_FLASH_WRITE_EN	///<���ʹ����д 
    void (*stm_flash_read)        (u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
    void (*stm_flash_write)       (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);
#endif
    void (*spi_flash_write)       (u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);                                                                                
    void (*spi_flash_read)        (u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);                 
    void (*spi_flash_erase)       (u32 SectorAddr);
    void (*spi_flash_power_down)  (void);                                                                                  
};
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ��spi_flash
  * @param  spi_id:spi���
  * @param  remap_par:��ӳ�����
  * @retval None
  */
void Spi_Flash_Init (drive_flash_desc_t *handle, const u8 spi_id, const u8 remap_par);

#ifdef __cplusplus
}
#endif

#endif /* __API_FLASH_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
