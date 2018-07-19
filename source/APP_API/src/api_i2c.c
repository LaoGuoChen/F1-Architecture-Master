/**
  ******************************************************************************
  * @file    api_i2c.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   i2cҵ��ӿڲ�
  ******************************************************************************
  */
#include "api_i2c.h"
#include "stm32f10x_i2c_config.h"  

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ģ��IIC��ʼ��
  * @param  None
  * @retval None
  */
void SimulateI2cInit(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin)
{
    I2c_Init(gpio_scl_port, gpio_scl_pin, gpio_sda_port, gpio_sda_pin);
}
/**
  * @brief  ģ��IIC���ݵ�ַ��ȡ����ֽ�
  * @param  None
  * @retval ����:�ɹ� 0:ʧ��
  */  
u8 SimulateI2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data)    
{
     return I2cReadBytes(SlaveAddress, reg, length, data); 
}  
/**
  * @brief  ģ��IIC���ݵ�ַд�����ֽ�
  * @param  None
  * @retval 1:�ɹ� 0:ʧ��
  */  
u8 SimulateI2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data)
{
    return I2cWriteBytes(SlaveAddress, reg, length, data);
}
/**
  * @brief  Ӳ��IIC���ó�ʼ��
  * @param  i2c_id:i2c�ı��
  * @param  i2c_remap:
            -0:����ӳ��
            -1:��ӳ��
  * @param  slave_addr:I2C�豸�Ĵӵ�ַ
  * @retval 1:�ɹ� 0:ʧ��
  */ 
void HardwareI2cInit(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr)
{
    I2CConfig(i2c_id, i2c_remap, slave_addr);
}    
/**
  * @brief  Ӳ��IIC��������
  * @param  addr:�Ĵ����ĵ�ַ
  * @param  data:�����͵�����
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cSendDataShell(u8 addr, u8 data)
{
    return HardwareI2cSendData(addr, data);
}
/**
  * @brief  Ӳ��IIC��ȡ����
  * @param  addr:�Ĵ����ĵ�ַ
  * @retval ��0:���յ������� 0:ʧ��
  */ 
u8 HardwareI2cReceiveDataShell(u8 addr)
{
    return HardwareI2cReadData(addr);
}
/**
  * @brief  Ӳ��IIC��ȡ�������
  * @param  register_addr:�Ĵ����ĵ�ַ
  * @param  data_out:���յ������ݵ�ַ
  * @param  length:�����յ����ݳ���
  * @retval 1:�ɹ� 0:ʧ��
  */ 
u8 HardwareI2cReadDatasShell(u8 register_addr, u8 *data_out, u8 length)
{
    return HardwareI2cReadDatas(register_addr, data_out, length);
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
