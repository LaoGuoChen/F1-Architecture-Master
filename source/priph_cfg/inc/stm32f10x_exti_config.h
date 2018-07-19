/**
  ******************************************************************************
  * @file    stm32f10x_exti_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   exti����ģ��
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_EXTI_CONFIG_H
#define  __STM32F10x_EXTI_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  �ⲿ�жϳ�ʼ��
  * @param  exti_port:�ⲿ�˿�
  * @param  exti_pin:�ⲿ����
  * @param  trigger:������ʽ
            -0:������
            -1:�½���
            -2:�����½���
  * @retval None
  */
void Exti_Init(GPIO_TypeDef* exti_port, const u16 exti_pin, const u8 trigger);
    

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

