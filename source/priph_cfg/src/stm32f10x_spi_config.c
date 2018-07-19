/**
  ******************************************************************************
  * @file   stm32f10x_spi_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   spi功能模块
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_spi_config.h"

static GPIO_TypeDef* s_stSpiFalshGpio = {0};
static u16 s_usSpiFlashPin = 0;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化spi
  * @param  spi_id:spi编号
  * @param  remap_par:重映射参数
  * @retval None
  */
void InitSpi(const u8 spi_id, const u8 remap_par)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
    u8 spi_id_remap = ((spi_id << 4) | remap_par);
    
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    
    switch (spi_id_remap)
    {
        case 0x10:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            /*!< Configure SPI_FLASH_SPI pins: SCK */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MISO */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MOSI */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
            SPI_Init(SPI1, &SPI_InitStructure);
            /* Enable SPI1  */
            SPI_Cmd(SPI1, ENABLE);
            
            s_stSpiFalshGpio = GPIOA;
            s_usSpiFlashPin  = GPIO_Pin_4;
        }
        break;
        case 0x11:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            /*!< Configure SPI_FLASH_SPI pins: SCK */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MISO */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MOSI */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);    

            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
            SPI_Init(SPI1, &SPI_InitStructure);
            /* Enable SPI1  */
            SPI_Cmd(SPI1, ENABLE);
            
            s_stSpiFalshGpio = GPIOA;
            s_usSpiFlashPin  = GPIO_Pin_15;
        }
        break;
        case 0x20:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            /*!< Configure SPI_FLASH_SPI pins: SCK */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MISO */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MOSI */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
            SPI_Init(SPI2, &SPI_InitStructure);
            /* Enable SPI2  */
            SPI_Cmd(SPI2, ENABLE);
            
            s_stSpiFalshGpio = GPIOB;
            s_usSpiFlashPin  = GPIO_Pin_12;
        }
        break;
        case 0x30:
        {
        	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            /*!< Configure SPI_FLASH_SPI pins: SCK */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MISO */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MOSI */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
            
            SPI_Init(SPI3, &SPI_InitStructure);
            /* Enable SPI3  */
            SPI_Cmd(SPI3, ENABLE);
            
            s_stSpiFalshGpio = GPIOA;
            s_usSpiFlashPin  = GPIO_Pin_15;
        }
        break;
        case 0x31:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            /*!< Configure SPI_FLASH_SPI pins: SCK */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MISO */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI pins: MOSI */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
            SPI_Init(SPI3, &SPI_InitStructure);
            /* Enable SPI3  */
            SPI_Cmd(SPI3, ENABLE);
            
            s_stSpiFalshGpio = GPIOA;
            s_usSpiFlashPin  = GPIO_Pin_4;
        }
        break;
        
        default:
        break;
    } 
}

/**
  * @brief  设置spi flash的片选信号电平
  * @param  spi_id:spi编号
  * @retval None
  */
void Set_Spi_Flash_Cs(const u8 cs_level)
{
    if (s_stSpiFalshGpio != 0)
    {
        if (cs_level == 0)
        {
            GPIO_ResetBits(s_stSpiFalshGpio, s_usSpiFlashPin);
        }
        else 
        {
            GPIO_SetBits(s_stSpiFalshGpio, s_usSpiFlashPin);
        }
    }
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
