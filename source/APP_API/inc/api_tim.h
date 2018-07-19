/**
  ******************************************************************************
  * @file    api_tim.h
  * @author  ������ 
  * @version V1.0
  * @date    2018.6.19
  * @brief   timӦ�ýӿڲ�
  ******************************************************************************
  */ 
#ifndef __API_TIM_H
#define __API_TIM_H

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
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
// <o>TIM_TO_TIME_ID <1-8>
// <i>The ID num of timer to time
#define  TIM_TO_TIME_ID        5
// *** <<< End of Configuration section             >>> ***  
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ����ʱ����ʱ����
  * @param  load_value:����װ��ֵ
  * @param  prescaler:Ԥ��Ƶϵ��
  * @retval None
  */
void InitTimerToTimeApi(const u16 load_value, const u16 prescaler);
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
void InitTimToCapApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);
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
void InitTimToPwmApi(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc);

/**
  * @brief  TIM��ʱ�жϴ����� \n
  * ���������Լ���� ���ڱ��ļ����������ö�ʱ����(����һ�� ����Ҫ�����ʱ �붨��Ƶ����ߵ� Ȼ��������������) 
  * @retval None
  */
//void TIM5_IRQHandler(void)
//{
//	if(TIM5->SR & 0x0001)//����ж�
//	{
//		TIM5->SR &=~(1<<0);//����жϱ�־λ
//		{
//      }
//  }
//}

/**
  * @brief  TIM���벶���жϴ����� \n
  * ���������Լ����
  * @retval None
  */
//void TIM3_IRQHandler(void)
//{
//    u8 uRising_Falling_Flag = 0;  
//    
//	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) //�������
//	{	 
//		if( uRising_Falling_Flag == 0) 	 
//		{				 
//			uRising_Falling_Flag = 1; 
//			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
//		}
//		else								 
//		{
//			uRising_Falling_Flag = 0;
//			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);	 //CC1P=1 ����Ϊ�½��ز���
//		}
//	}
//	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); //����жϱ�־λ
//}

/**
  * @brief  �綨ʱ��1��ch2��PWMģʽ ��������������ö�ʱ��1ͨ��2��ռ�ձ� \n
  * ���������Լ����
  * @retval None
  */
//TIM1->CCR2 = 50;

#ifdef __cplusplus
}
#endif

#endif /* __API_TIM_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
