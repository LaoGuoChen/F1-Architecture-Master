/**
  ******************************************************************************
  * @file    api_iwdg.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   iwdgҵ��ӿڲ�
  ******************************************************************************
  */
  
#include "api_iwdg.h"
#include "stm32f10x_iwdg_config.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ�����Ź���Ƶ ι��ʱ�亯��
  * @param  prer��Ԥ��Ƶ  
  * @param  rlr�����Ź���������װ��ֵ    
  * @note   ��λʱ��ms��Tout=((4*2^prer)*rlr)/40 :�и�4����Ϊ���Ź���Ƶ�Ĵ���(IWDG_PR)��ֵ \n
			������2^prer�Ͷ�Ӧ�ķ�Ƶ��Ҫ��4���Ƿ�Ƶ�����忴�ֲᡣ���Ź�ʱ��40KHZ  
  * @retval None
*/
void IwdgInit(const u8 prer, const u16 rlr)
{
    Iwdg_Init(prer, rlr);
}
/**
  * @brief  ι������������ι��ʱ�䲻ι���͸�λ
  * @param  None
  * @retval None
*/
void IwdgFeed(void)
{
    Iwdg_Feed();
}

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
