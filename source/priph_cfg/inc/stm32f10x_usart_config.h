/**
  ******************************************************************************
  * @file    stm32f10x_usart_config.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart功能模块
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F10x_USART_CONFIG_H
#define  __STM32F10x_USART_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"	
#include "api_usart.h"
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
  
/**
  * @brief  串口初始化总入口
  * @param  handle:注册后返回的句柄
  * @param  usart_id:串口号
  * @param  remap_par:重映射参数
  *         -0:无重映射                                    
  *         -1:该串口有部分重映射则部分重映射，无则全重映射     
  *         -2:全重映射  
  * @param  baud_par:波特率
  * @retval -1:错误 0:成功
  */
s8 InitUsartShell(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par);

/**
  * @brief  设置串口为打印串口
  * @param  usart_id:串口号
  * @retval -1:错误 0:成功
  */
s8 SetUsartPrintFun(const u8 usart_id);
    
    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

