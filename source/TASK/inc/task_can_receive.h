/**
  ******************************************************************************
  * @file    task_can_receive.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.13
  * @brief   CAN接收数据处理
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_CAN_RECEIVE_H
#define __TASK_CAN_RECEIVE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported Variable ---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void vCanReceiveTask( void * pvParameters );


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
