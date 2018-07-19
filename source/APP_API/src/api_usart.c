/**
  ******************************************************************************
  * @file    api_usart.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   usart�ӿڲ�
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "api_usart.h"
#include "stm32f10x_usart_config.h"
#include "common.h"

/**
  * @brief  ���ڷ��ͺ���.
  * @param  usart_id:���ں�
  * @param  usart_data_par:��Ҫ���͵ĵ�ַ
  * @param  usart_data_len���������ݳ���
  * @retval -1:����ʧ��(��Ӧ����δ���������Ѿ�������������).0���ɹ�
  */
static s8 Usart_Send(u8 usart_id, u8 *usart_data_par, u8 usart_data_len)
{
    u8 usart_send_data_index = 0;
    
    if (usart_id > 5 || NULL == usart_data_par)
        return SIGNED_TYPE_ERR;
    
    switch (usart_id)
    {   
        #if USART1_EN
        case 1:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                USART_SendData(USART1, *(usart_data_par + usart_send_data_index));
            }
            break;
        #endif
        #if USART2_EN
        case 2:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                USART_SendData(USART2, *(usart_data_par + usart_send_data_index));
            }
            break;
        #endif
        #if USART3_EN
        case 3:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                USART_SendData(USART3, *(usart_data_par + usart_send_data_index));
            }
            break;
        #endif
        #if USART4_EN
        case 4:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                USART_SendData(UART4, *(usart_data_par + usart_send_data_index));
            }
            break;
        #endif
        #if USART5_EN
        case 5:
            for (usart_send_data_index = 0; usart_send_data_index < usart_data_len; usart_send_data_index++)
            {
                USART_SendData(UART5, *(usart_data_par + usart_send_data_index));
            }
            break;
        #endif
        default:
            break;
    }
    
    return SIGNED_TYPE_SUCCESS;
}
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
void Api_Init_Usart(drive_usart_desc_t *handle, const u8 usart_id, const u8 remap_par, const u32 baud_par)
{
    handle->usart_init      = InitUsartShell;
    handle->usart_send      = Usart_Send;
    handle->set_usart_print = SetUsartPrintFun;
    handle->usart_id        = usart_id;
    handle->usart_init(handle, usart_id, remap_par, baud_par);
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
