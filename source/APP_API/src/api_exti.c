/**
  ******************************************************************************
  * @file    api_exti.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   extiӦ�ýӿڲ�
  ******************************************************************************
  */
#include "api_exti.h" 
#include "stm32f10x_exti_config.h" 
 
/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
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
void ExtiInit(GPIO_TypeDef* exti_port,const u16 exti_pin,const u8 trigger)
{
    Exti_Init(exti_port, exti_pin, trigger);
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

