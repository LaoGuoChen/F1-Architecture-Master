/**
  ******************************************************************************
  * @file    stm32f10x_i2c_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   i2c����ģ��
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_I2C_CONFIG_H
#define  __STM32F10x_I2C_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  ģ��IIC��ʼ��
  * @param  None
  * @retval None
  */
void I2c_Init(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin);
/**
  * @brief  ģ��IIC���ݵ�ַ��ȡ����ֽ�
  * @param  None
  * @retval ����:�ɹ� 0:ʧ��
  */  
u8 I2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data);    
/**
  * @brief  ģ��IIC���ݵ�ַд�����ֽ�
  * @param  None
  * @retval 1:�ɹ� 0:ʧ��
  */  
u8 I2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data);
/**
  * @brief  Ӳ��IIC���ó�ʼ��
  * @param  i2c_id:i2c�ı��
  * @param  i2c_remap:
            -0:����ӳ��
            -1:��ӳ��
  * @param  slave_addr:I2C�豸�Ĵӵ�ַ
  * @retval 1:�ɹ� 0:ʧ��
  */ 
void I2CConfig(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr);    
/**
  * @brief  Ӳ��IIC��������
  * @param  addr:�Ĵ����ĵ�ַ
  * @param  data:�����͵�����
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cSendData(u8 addr, u8 data);
/**
  * @brief  Ӳ��IIC��ȡ����
  * @param  addr:�Ĵ����ĵ�ַ
  * @retval ��0:���յ������� 0:ʧ��
  */ 
u8 HardwareI2cReadData(u8 addr);
/**
  * @brief  Ӳ��IIC��ȡ�������
  * @param  register_addr:�Ĵ����ĵ�ַ
  * @param  data_out:���յ������ݵ�ַ
  * @param  length:�����յ����ݳ���
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cReadDatas(u8 register_addr, u8 *data_out, u8 length);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

 
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

