/**
  ******************************************************************************
  * @file   stm32f10x_iwdg_config.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.15
  * @brief   iwdg����ģ��
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_iwdg_config.h"


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ��ʼ�����Ź���Ƶ ι��ʱ�亯��
  * @param  prer��Ԥ��Ƶ  
  * @param  rlr�����Ź���������װ��ֵ  
  * @note   ��λʱ��ms��Tout=((4*2^prer)*rlr)/40 :�и�4����Ϊ���Ź���Ƶ�Ĵ���(IWDG_PR)��ֵ \n
			������2^prer�Ͷ�Ӧ�ķ�Ƶ��Ҫ��4���Ƿ�Ƶ�����忴�ֲᡣ���Ź�ʱ��40KHZ  
  * @retval None
*/
void Iwdg_Init(const u8 prer, const u16 rlr)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); ///<����Ĵ�������  
    IWDG_SetPrescaler(prer);                      ///< д���ʼ����Ƶֵ    
    IWDG_SetReload(rlr);                          ///<д���Զ�װ��ֵ    
    IWDG_ReloadCounter();                         ///<�����Ĵ�������
	IWDG_Enable();                                ///<�������Ź�
}

/**
  * @brief  ι������������ι��ʱ�䲻ι���͸�λ
  * @param  None
  * @retval None
*/
void Iwdg_Feed(void)
{
    IWDG_ReloadCounter();   
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
