/**
  ******************************************************************************
  * @file    api_usart.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart�ӿڲ�
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __HWJ_USART_API_H
#define  __HWJ_USART_API_H


#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* Exported types ------------------------------------------------------------*/
    
/** 
  * usart_init:usart��ʼ�� \n
  * set_usart_print:���øô���Ϊ��ӡ��� \n
  * usart_send:������Ϣ���� \n
  * usart_id:�������豸�Ĵ��ں�,��USBAT1�򴮿ں�Ϊ1 \n
  * xQueue:�����жϺ�������ݵ���Ϣ���� ʹ��ǰ���ж��Ƿ�Ϊ�� \n
  */
typedef struct drive_usart_desc drive_usart_desc_t;
    
struct drive_usart_desc{
    s8   (*usart_init)       (drive_usart_desc_t *handle, u8 usart_id, u8 remap_par, u32 baud_par); /*!< usart��ʼ�� */
    s8   (*set_usart_print)  (u8 usart_id);                                                         /*!< ���øô���Ϊ��ӡ��� */                                                                             /* ��Ϣ���� ʹ��ǰ���ж��Ƿ�Ϊ�� */
    s8   (*usart_send)       (u8 usart_id, u8 *usart_data_par, u8 usart_data_len);                  /*!< ������Ϣ���� */
    u8   usart_id;                                                                                  /*!< �������豸�Ĵ��ں� ��USBAT1�򴮿ں�Ϊ1 */
    QueueHandle_t xQueue;                                                                          /*!< �����жϺ�������ݵ���Ϣ���� ʹ��ǰ���ж��Ƿ�Ϊ�� */
};

/* Exported Defines ----------------------------------------------------------*/
/*
 * @brief ����API����˵��
 *        1����������
 *        2�������ж����ȼ�
 *        3��������Ϣ����,��������������Ϣ���д洢�����ݵ�Ԫ�����͵�����Ԫ���ֽڳ���
 *        4�������ṹ�岢��ʼ���󼴿�ʹ��
 */
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
/*
// <q>USART1 Enable
*/
#define USART1_EN     0
// <h>USART1 priority & Queue
// <o>USART1_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART1 Tx
    #define  USART1_PREEMPTION_PRIORITY  (1)
// <o>USART1_SUB_PRIORITY <1-16>
// <i>Start priority of USART1 Sub Tx
    #define  USART1_SUB_PRIORITY         (2)
// <o>USART1_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART1 
    #define  USART1_QUEUE_LENGTH         (20)
// <o>USART1_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART1     
    #define  USART1_QUEUE_TYPE_L         (1)
// </h>
/*
// <q>USART2 Enable
*/
#define USART2_EN     1
// <h>USART2 priority & Queue
// <o>USART2_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART2 Tx
    #define  USART2_PREEMPTION_PRIORITY  (1)
// <o>USART2_SUB_PRIORITY <1-16>
// <i>Start priority of USART2 Sub Tx
    #define  USART2_SUB_PRIORITY         (2)
// <o>USART2_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART2 
    #define  USART2_QUEUE_LENGTH         (20)
// <o>USART2_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART2     
    #define  USART2_QUEUE_TYPE_L         (1)
// </h>
/*
// <q>USART3 Enable
*/
#define USART3_EN     0
// <h>USART3 priority & Queue
// <o>USART3_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART2 Tx
    #define  USART3_PREEMPTION_PRIORITY  (0)
// <o>USART3_SUB_PRIORITY <1-16>
// <i>Start priority of USART3 Sub Tx
    #define  USART3_SUB_PRIORITY         (0)
// <o>USART3_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART2 
    #define  USART3_QUEUE_LENGTH         (0)
// <o>USART3_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART3     
    #define  USART3_QUEUE_TYPE_L         (0)
// </h>
/*
// <q>USART4 Enable
*/
#define USART4_EN     0
// <h>USART4 priority & Queue
// <o>USART4_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART4 Tx
    #define  USART3_PREEMPTION_PRIORITY  (0)
// <o>USART4_SUB_PRIORITY <1-16>
// <i>Start priority of USART4 Sub Tx
    #define  USART4_SUB_PRIORITY         (0)
// <o>USART4_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART4 
    #define  USART4_QUEUE_LENGTH         (0)
// <o>USART4_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART4     
    #define  USART4_QUEUE_TYPE_L         (0)
// </h>
/*
// <q>USART5 Enable
*/
#define USART5_EN     1
// <h>USART5 priority & Queue
// <o>USART5_PREEMPTION_PRIORITY <1-16>
// <i>Start priority of USART5 Tx
    #define  USART5_PREEMPTION_PRIORITY  (1)
// <o>USART5_SUB_PRIORITY <1-16>
// <i>Start priority of USART5 Sub Tx
    #define  USART5_SUB_PRIORITY         (1)
// <o>USART5_QUEUE_LENGTH <1-50>
// <i>Queue Length of USART5 
    #define  USART5_QUEUE_LENGTH         (4)
// <o>USART5_QUEUE_TYPE_L <1-40>
// <i>Queue Type (byte) of USART5     
    #define  USART5_QUEUE_TYPE_L         (4)
// </h>
// *** <<< End of Configuration section             >>> ***  
    
/**
  * @brief  ���ڽӿڲ��ʼ��
  * @param  handle:���صľ��
  * @param  usart_id:��ʼ���Ĵ��ں�
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��                                    
  *         -1:�ô����в�����ӳ���򲿷���ӳ�䣬����ȫ��ӳ��     
  *         -2:ȫ��ӳ�� 
  * @param  baud_par:������
  * @retval None
  */
void Api_Init_Usart(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par);
    
#ifdef __cplusplus
}
#endif/* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/

