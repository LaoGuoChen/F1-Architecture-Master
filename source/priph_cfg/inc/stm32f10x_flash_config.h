/**
  ******************************************************************************
  * @file   stm32f10x_flash_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.13
  * @brief   flash����ģ��
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_FLASH_CONFIG_H
#define  __STM32F10x_FLASH_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_spi_config.h" 
   
#if STM32_FLASH_WRITE_EN	///<���ʹ����д   
/**
  * @brief  ��ָ����ַ��ʼ����ָ�����ȵ�����
  * @param  ReadAddr:��ʼ��ַ
  * @param  pBuffer:����ָ��
  * @param  NumToWrite:����(16λ)��
  * @retval None
  */ 
void Stm_Flash_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
/**
  * @brief  ��ָ����ַ��ʼд��ָ�����ȵ�����
  * @param  WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
  * @param  pBuffer:����ָ��
  * @param  NumToWrite:����(16λ)�� (����Ҫд���16λ���ݵĸ���.) 
  * @retval None
  */ 		 
void Stm_flash_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);
/**
  * @brief  д���ݽ�flash
  * @param  pBuffer:д�����ݵĵ�ַ
  * @param  WriteAddr:д���flash��ַ
  * @param  NumByteToWrite:д�����ݵĳ���
  * @retval None
  */
#endif  

void Spi_Flash_Buffer_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
/**
  * @brief  ��flashָ����ַ��ȡ����
  * @param  pBuffer:��ȡ���ݺ��ŵĵ�ַ
  * @param  ReadAddr:��ȡ��flash��ַ
  * @param  NumByteToWrite:д�����ݵĳ���
  * @retval None
  */
void Spi_Flash_Buffer_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
/**
  * @brief  ����flash������
  * @param  SectorAddr:����ĵ�ַ
  * @retval None
  */
void Spi_Flash_Sector_Erase(u32 SectorAddr);
/**
  * @brief  flash�������ģʽ
  * @param  None
  * @retval None
  */
void Spi_Flash_Power_Down(void);
	
#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2016 HWJ *****END OF FILE****/

