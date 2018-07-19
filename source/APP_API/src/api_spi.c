/**
  ******************************************************************************
  * @file    api_spi.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   spi�ӿڲ�
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "api_spi.h"
#include "stm32f10x_spi_config.h"
#include "common.h"
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ��spi
  * @param  spi_id:spi���
  * @param  remap_par:��ӳ�����
  * @retval None
  */
static void InitSpiShell(const u8 spi_id, const u8 remap_par)
{
    InitSpi(spi_id, remap_par);
}
/**
  * @brief  ������Ϣ����
  * @param  spi_id:��ʼ����spi��
  * @param  spi_data_par:�������ݵĵ�ַ
  * @param  spi_data_len:�������ݵĳ���
  * @param  txData:�ȷ��͵�ֵ
  * @retval None
  */
static u16 Spi_Send(const u8 spi_id, u8 *spi_data_par)
{
    u8 send_index = 0;
    SPI_TypeDef* SPIx = NULL;
    u16 timeout = 0x1000;
    
    if(spi_id == 1)
    {
        SPIx = SPI1;
    }
    else if(spi_id == 2)
    {
        SPIx = SPI2;
    }
    else if(spi_id == 3)
    {
        SPIx = SPI3;
    }
    
    timeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) 
    {
        if(!(--timeout))
        {
            return 0x0;
        }
    }

    /* Send byte through the SPI2 peripheral */
    SPI_I2S_SendData(SPIx, *spi_data_par);

    /* Wait to receive a byte */
    timeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if(!(--timeout))
        {
            return 0x0;
        }
    }
    
    return SPI_I2S_ReceiveData(SPIx);
}
/**
  * @brief  ������Ϣ����
  * @param  spi_id:��ʼ����spi��
  * @retval ���ص���ֵ
  */
static u8  Spi_Receive(const u8 spi_id)
{
    SPI_TypeDef* SPIx = NULL;
    
    if(spi_id == 1)
        SPIx = SPI1;
    else if(spi_id == 2)
        SPIx = SPI2;
    else if(spi_id == 3)
        SPIx = SPI3;
    
    return SPI_I2S_ReceiveData(SPIx);
}
/**
  * @brief  �ȷ�����Ϣ�������Ϣ����
  * @param  spi_id:��ʼ����spi��
  * @param  txData:�ȷ��͵�ֵ
  * @retval 0����ȡ��ʱ���� >0 ���ص���ֵ
  */
static u8 Spi_TxRx(const u8 spi_id, const u8 txData)
{	
	u8 rxData = 0; 
	u16 timeout = 0x1000;
    SPI_TypeDef* SPIx = NULL;
    
    if(spi_id == 1)
        SPIx = SPI1;
    else if(spi_id == 2)
        SPIx = SPI2;
    else if(spi_id == 3)
        SPIx = SPI3;
    
    
	/* Wait until the transmit buffer is empty */
	timeout = 0x1000;
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) {
		if(!(--timeout))
			return 0x0;
	}
	SPI_I2S_SendData(SPIx, txData);
	
	/* Wait until a data is received */
	timeout = 0x1000;
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET){
		if(!(--timeout))
			return 0x0;
	}
	rxData = SPI_I2S_ReceiveData(SPIx);
	
	return (u8)rxData;
}
/**
  * @brief  spi�ӿڲ��ʼ��
  * @param  handle:���صľ��
  * @param  spi_id:��ʼ����spi��
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��                                     
  *         -1:ȫ��ӳ�� 
  * @retval SIGNED_TYPE_ERR�����ó��ִ��� SIGNED_TYPE_SUCCESS�����óɹ�
  */
s8 Api_Init_Spi(drive_spi_desc_t *handle, const u8 spi_id, const u8 remap_par)    
{
    if (NULL == handle)
        return SIGNED_TYPE_ERR;

    InitSpiShell(spi_id, remap_par);
    handle->spi_send    = Spi_Send;
    handle->spi_receive = Spi_Receive;
    handle->spi_tx_rx   = Spi_TxRx;
    handle->spi_id      = spi_id;
    handle->spi_set_cs  = Set_Spi_Flash_Cs;
    
    return SIGNED_TYPE_SUCCESS;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
