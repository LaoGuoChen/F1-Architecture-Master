/**
  ******************************************************************************
  * @file    api_iwdg.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   iwdgҵ��ӿڲ�
  ******************************************************************************
  */
  
#ifndef  __API_IWDG_H
#define  __API_IWDG_H

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
/* Exported functions ------------------------------------------------------- */
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��ʼ�����Ź���Ƶ ι��ʱ�亯��
  * @param  prer��Ԥ��Ƶ  
  * @param  rlr�����Ź���������װ��ֵ  
  * @note   ��λʱ��ms��Tout=((4*2^prer)*rlr)/40 :�и�4����Ϊ���Ź���Ƶ�Ĵ���(IWDG_PR)��ֵ \n
			������2^prer�Ͷ�Ӧ�ķ�Ƶ��Ҫ��4���Ƿ�Ƶ�����忴�ֲᡣ���Ź�ʱ��40KHZ  
  * @retval None
*/
void IwdgInit(const u8 prer, const u16 rlr);
/**
  * @brief  ι������������ι��ʱ�䲻ι���͸�λ
  * @param  None
  * @retval None
*/
void IwdgFeed(void);

#ifdef __cplusplus
}
#endif

#endif /* __API_IWDG_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
