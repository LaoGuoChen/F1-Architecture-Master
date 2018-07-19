/**
  ******************************************************************************
  * @file    api_exti.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   extiӦ�ýӿڲ�
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_EXTI_H
#define __API_EXTI_H


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
  * @brief  �ⲿ�жϳ�ʼ��
  * @param  exti_port:�ⲿ�˿�
  * @param  exti_pin:�ⲿ����
  * @param  trigger:������ʽ
            -0:������
            -1:�½���
            -2:�����½���
  * @retval None
  */
void ExtiInit(GPIO_TypeDef* exti_port, const u16 exti_pin, const u8 trigger);

/**
  * @brief  �ⲿ�����ж� \n
  * �����Լ�������ʵ�֡�
  * @retval None
  */

//void EXTI0_IRQHandler(void)
//{
//	EXTI_ClearFlag(EXTI_Line0);
//}

#ifdef __cplusplus
}
#endif

#endif /* __API_EXTI_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
