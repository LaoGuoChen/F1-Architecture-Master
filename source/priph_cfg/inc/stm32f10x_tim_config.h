/**
  ******************************************************************************
  * @file   stm32f10x_tim_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   spi����ģ��
  ******************************************************************************
  */
  
#ifndef  __STM32F10x_TIM_CONFIG_H
#define  __STM32F10x_TIM_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ����ʱ����ʱ����
  * @param  load_value:����װ��ֵ
  * @param  prescaler:Ԥ��Ƶϵ��
  * @retval None
  */
void InitTimerToTime(const u16 load_value, const u16 prescaler);
/**
  * @brief  ��ʼ����ʱ�����벶�����
  * @param  tim_id:��ʱ���ı��
  * @param  channel:ͨ�����ͣ�����λÿλ�ĸߵ�״̬��ʾCH1-4��ѡ��״̬����0x06��ʾѡ����CH2��CH4.
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��
  *         -1:�ô����в�����ӳ���򲿷���ӳ�䣬����ȫ��ӳ��  
  *         -2:ȫ��ӳ��  
  * @param  arr:���ؼ���
  * @param  psc:Ԥ��Ƶϵ��
  * @retval None
  */
void InitTimToCap(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);
/**
  * @brief  ��ʼ����ʱ��PWM����
  * @param  tim_id:��ʱ���ı��
  * @param  channel:ͨ�����ͣ�����λÿλ�ĸߵ�״̬��ʾCH1-4��ѡ��״̬����0x06��ʾѡ����CH2��CH4.
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��
  *         -1:�ô����в�����ӳ���򲿷���ӳ�䣬����ȫ��ӳ��  
  *         -2:ȫ��ӳ��  
  * @param  arr:���ؼ���
  * @param  psc:Ԥ��Ƶϵ��
  * @retval None
  */
void InitTimToPwm(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
