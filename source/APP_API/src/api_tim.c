/**
  ******************************************************************************
  * @file    api_tim.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.19
  * @brief   timӦ�ýӿڲ�
  ******************************************************************************
  */
#include "api_tim.h"
#include "stm32f10x_tim_config.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ����ʱ����ʱ����
  * @param  load_value:����װ��ֵ
  * @param  prescaler:Ԥ��Ƶϵ��
  * @retval None
  */
void InitTimerToTimeApi(const u16 load_value, const u16 prescaler)
{
    InitTimerToTime(load_value, prescaler);
}
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
void InitTimToCapApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{
    InitTimToCap(tim_id, channel, remap, arr, psc);
}
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
void InitTimToPwmApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{
    InitTimToPwm(tim_id, channel, remap, arr, psc);
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
