/**
  ******************************************************************************
  * @file   stm32f10x_iwdg_config.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   iwdg����ģ��
  ******************************************************************************
  */
#ifndef  __STM32F10x_IWDG_CONFIG_H
#define  __STM32F10x_IWDG_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  ��ʼ�����Ź���Ƶ ι��ʱ�亯��
  * @param  prer��Ԥ��Ƶ  
  * @param  rlr�����Ź���������װ��ֵ  
  * @note   ��λʱ��ms��Tout=((4*2^prer)*rlr)/40 :�и�4����Ϊ���Ź���Ƶ�Ĵ���(IWDG_PR)��ֵ \n
			������2^prer�Ͷ�Ӧ�ķ�Ƶ��Ҫ��4���Ƿ�Ƶ�����忴�ֲᡣ���Ź�ʱ��40KHZ  
  * @retval None
*/
void Iwdg_Init(const u8 prer, const u16 rlr);
/**
  * @brief  ι������������ι��ʱ�䲻ι���͸�λ
  * @param  None
  * @retval None
*/
void Iwdg_Feed(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/

