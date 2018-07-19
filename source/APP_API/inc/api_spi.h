/**
  ******************************************************************************
  * @file    api_spi.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.13
  * @brief   spi�ӿڲ�
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __API_SPI_H
#define  __API_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/** 
  * spi_init:spi��ʼ�� \n
  * spi_send:������Ϣ���� \n
  * spi_receive:������Ϣ���� \n
  * spi_tx_rx:�ȷ�����Ϣ�������Ϣ���� \n
  * spi_id:�������豸�Ĵ��ں�,��spi1����Ϊ1 \n
  */
typedef struct drive_spi_desc drive_spi_desc_t;
    
struct drive_spi_desc{                                                                  
    u16  (*spi_send)       (u8 spi_id, u8 *spi_data_par);                       /*!< ������Ϣ���� */
    u8   (*spi_receive)    (u8 spi_id);                                         /*!< ������Ϣ���� */
    u8   (*spi_tx_rx)      (u8 spi_id, u8 txData);                              /*!< �ȷ�����Ϣ�������Ϣ���� */
    void (*spi_set_cs)     (u8 cs_status);                                      /*!< ����SPIƬѡ�ߵ�״̬ */
    u8    spi_id;                                                               /*!< �������豸��spi�� ��spi1��Ϊ1 */
};
    
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  spi�ӿڲ��ʼ��
  * @param  handle:���صľ��
  * @param  spi_id:��ʼ����spi��
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��                                     
  *         -1:ȫ��ӳ�� 
  * @retval SIGNED_TYPE_ERR�����ó��ִ��� SIGNED_TYPE_SUCCESS�����óɹ�
  */
s8 Api_Init_Spi(drive_spi_desc_t *handle, const u8 spi_id, const u8 remap_par);    


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/


