/**
  ******************************************************************************
  * @file    api_can.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.8
  * @brief   canӦ�ýӿڲ�
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __CAN_API_H
#define  __CAN_API_H

#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_can_config.h"
#include  "can_macro.h"
    
/* Exported types ------------------------------------------------------------*/
/** 
  * can_init:can��ʼ�� \n
  * can_send_data_frame:can��������֡ \n
  * can_send_remote_frame:can����Զ��֡ \n
  * can_receive_data:can�������� \n
  * can_tx_recv_data:can�ȷ����ٽ������� \n
  */
typedef struct drive_can_desc drive_can_desc_t;

struct drive_can_desc{
    s8  (*can_init)              (u8 remap_par);                  /*!< can��ʼ��   */
    s8  (*can_send_data_frame)   (u32 id, void *buf, u8 bufsize); /*!< can��������֡ */   
    s8  (*can_send_remote_frame) (u32 id);                        /*!< can����Զ��֡ */ 
    s8  (*can_receive_data)      (can_msg *msg, u16 timeout);     /*!< can�������� */  
    s8  (*can_tx_recv_data)      (u32 id, void *inbuf, u8 insize, void *outbuf, u8 outsize , u16 timeout); /*!< can�ȷ����ٽ������� */      
};

typedef struct
{
    u32 id;
    u32 mask;
    u8  format;
}can_set_filter_t;
/** 
  * can���ù��������� \n
  * ��һ�����û��ڴ���ӹ����������� \n
  */
static can_set_filter_t can_set_filter_table[] = {
{0x00200000, 0x00f00000, EXTENDED_FORMAT},
{0x00400000, 0x00f00000, EXTENDED_FORMAT}
};

/* Exported Defines ----------------------------------------------------------*/
/*!< �ڶ�����ͨ�����������÷��͡����յ����ȼ�����Ϣ���г��� */
// *** <<< Use Configuration Wizard in Context Menu >>> *** 
// <h>Can priority
// <o>CAN1_TX_ISR_PRIO <1-16>
// <i>Start priority of CAN1 Tx
#define  CAN1_TX_ISR_PRIO		(4)
// <o>CAN1_RX_ISR_PRIO <1-16>
// <i>Start priority of CAN1 Rx
#define  CAN1_RX_ISR_PRIO		(5)
// <o>CAN1_TX_ISR_PRIO <1-40>
// <i>Start priority of CAN1 Tx
#define  CAN_SEND_OBJECTS       (20)
// <o>CAN1_TX_ISR_PRIO <1-40>
// <i>Start priority of CAN1 Tx
#define  CAN_RECE_OBJECTS       (20)
// </h>
// *** <<< End of Configuration section             >>> *** 

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ��������HALע��CAN����ʼ�����û����þ������
  * @param  handle:���ڷ��ؿ��Ƶ�ľ��
  * @param  remap_par:��ӳ�����
  *         -0:����ӳ��
  *         -1:��can���в�����ӳ���򲿷���ӳ�䣬����ȫ��ӳ��  
  *         -2:ȫ��ӳ��  
  * @retval SIGNED_TYPE_ERR�����ó��ִ��� SIGNED_TYPE_SUCCESS�����óɹ�
  */
s8 drive_can_init(drive_can_desc_t *handle, const u8 remap_par);

    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
