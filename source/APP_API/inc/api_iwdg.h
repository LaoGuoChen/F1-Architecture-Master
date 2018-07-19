/**
  ******************************************************************************
  * @file    api_iwdg.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   iwdg业务接口层
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
  * @brief  初始化看门狗分频 喂狗时间函数
  * @param  prer：预分频  
  * @param  rlr：看门狗计数器重装载值  
  * @note   复位时间ms：Tout=((4*2^prer)*rlr)/40 :有个4是因为看门狗分频寄存器(IWDG_PR)的值 \n
			并不是2^prer就对应的分频还要乘4才是分频，具体看手册。看门狗时钟40KHZ  
  * @retval None
*/
void IwdgInit(const u8 prer, const u16 rlr);
/**
  * @brief  喂狗函数；超过喂狗时间不喂狗就复位
  * @param  None
  * @retval None
*/
void IwdgFeed(void);

#ifdef __cplusplus
}
#endif

#endif /* __API_IWDG_H */

/************************** (C) COPYRIGHT 2018 HWJ **********END OF FILE******/
