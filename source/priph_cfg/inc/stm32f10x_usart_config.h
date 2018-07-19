/**
  ******************************************************************************
  * @file    stm32f10x_usart_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart����ģ��
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F10x_USART_CONFIG_H
#define  __STM32F10x_USART_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"	
#include "api_usart.h"
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
  
/**
  * @brief  ���ڳ�ʼ�������
  * @param  handle:ע��󷵻صľ��
  * @param  usart_id:���ں�
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��                                    
  *         -1:�ô����в�����ӳ���򲿷���ӳ�䣬����ȫ��ӳ��     
  *         -2:ȫ��ӳ��  
  * @param  baud_par:������
  * @retval -1:���� 0:�ɹ�
  */
s8 InitUsartShell(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par);

/**
  * @brief  ���ô���Ϊ��ӡ����
  * @param  usart_id:���ں�
  * @retval -1:���� 0:�ɹ�
  */
s8 SetUsartPrintFun(const u8 usart_id);
    
    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

