/**
  ******************************************************************************
  * @file    app_magnetic_encoder.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.4
  * @brief   �ű���Ӧ�ýӿڲ�
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_MAGNETIC_ENCODER_H
#define __APP_MAGNETIC_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "api_adc.h"

/* Exported types ------------------------------------------------------------*/

/** 
  * read_magnetic_encoder_data:����������ģʽ ����ֵ���ű����ֵ�˲������ֵ �������ű�����ADC�е����ݴ洢�±� \n
  * rec_data_index:�ű�����ADC�е����ݴ洢�±� \n
  */
    
typedef struct magnetic_encoder_desc magnetic_encoder_desc_t;

struct magnetic_encoder_desc{
    u16  (*read_magnetic_encoder_data) (u8 adc_index); /*!< ����������ģʽ ����ֵ���ű����ֵ�˲������ֵ �������ű�����ADC�е����ݴ洢�±� */
    u8   rec_data_index;                               /*!< �ű�����ADC�е����ݴ洢�±� */
};
/* Exported define -----------------------------------------------------------*/
#define   MAGNETIC_ENCODER_EN            (TURN_ON)
#define   MAGNETIC_ENCODER_ADC_ID        (3)
#define   MAGNETIC_ENCODER_ADC_CHANNEL   (0x40)
#define   MAGNETIC_ENCODER_CHANNEL_ID    (6)

/**
  * @brief  ��ȡ�ű���Ӧ������
  * @param  adc_data_index:ADC�µ�ĳͨ����Ӧ�Ĵ洢�����±�
  * @retval ������ֵ�˲���adc�ɼ�ֵ
  */
s8 Magnetic_Encoder_Init( magnetic_encoder_desc_t *handle);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif


/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/

