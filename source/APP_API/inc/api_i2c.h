/**
  ******************************************************************************
  * @file    api_i2c.c
  * @author  ������ 
  * @version V1.0
  * @date    2018.6.2
  * @brief   i2cҵ��ӿڲ�
  ******************************************************************************
  */ 
#ifndef __API_I2C_H
#define __API_I2C_H

/* Define to prevent recursive inclusion -------------------------------------*/

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
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ģ��IIC��ʼ��
  * @param  None
  * @retval None
  */
void SimulateI2cInit(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin);
/**
  * @brief  ģ��IIC���ݵ�ַ��ȡ����ֽ�
  * @param  None
  * @retval ����:�ɹ� 0:ʧ��
  */  
u8 SimulateI2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data);    
/**
  * @brief  ģ��IIC���ݵ�ַд�����ֽ�
  * @param  None
  * @retval 1:�ɹ� 0:ʧ��
  */  
u8 SimulateI2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data);
/**
  * @brief  Ӳ��IIC���ó�ʼ��
  * @param  i2c_id:i2c�ı��
  * @param  i2c_remap:
            -0:����ӳ��
            -1:��ӳ��
  * @param  slave_addr:I2C�豸�Ĵӵ�ַ
  * @retval 1:�ɹ� 0:ʧ��
  */ 
void HardwareI2cInit(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr);   
/**
  * @brief  Ӳ��IIC��������
  * @param  addr:�Ĵ����ĵ�ַ
  * @param  data:�����͵�����
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cSendDataShell(u8 addr, u8 data);
/**
  * @brief  Ӳ��IIC��ȡ����
  * @param  addr:�Ĵ����ĵ�ַ
  * @retval ��0:���յ������� 0:ʧ��
  */ 
u8 HardwareI2cReceiveDataShell(u8 addr);
/**
  * @brief  Ӳ��IIC��ȡ�������
  * @param  register_addr:�Ĵ����ĵ�ַ
  * @param  data_out:���յ������ݵ�ַ
  * @param  length:�����յ����ݳ���
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cReadDatasShell(u8 register_addr, u8 *data_out, u8 length);

#ifdef __cplusplus
}
#endif

#endif /* __API_I2C_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
