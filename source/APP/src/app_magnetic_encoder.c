/**
  ******************************************************************************
  * @file    app_magnetic_encoder.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.4
  * @brief   �ű���Ӧ�ýӿڲ�
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "app_magnetic_encoder.h"

/* Private variables ---------------------------------------------------------*/
static drive_adc_desc_t s_stDrive_Adc_Handle = {0};
/* Private functions ---------------------------------------------------------*/

static u16 Read_Magnetic_Encoder_Data(const u8 adc_data_index);

/**
  * @brief  �ű���Ӧ�ýӿڳ�ʼ��
  * @param  ���ڲ����ı������豸���
  * @retval None
  */	
s8 Magnetic_Encoder_Init(magnetic_encoder_desc_t *handle)
{
    drive_adc_init(&s_stDrive_Adc_Handle);
    
    s_stDrive_Adc_Handle.rec_data_index = s_stDrive_Adc_Handle.adc_init(MAGNETIC_ENCODER_ADC_ID, MAGNETIC_ENCODER_ADC_CHANNEL);
    
    if (SIGNED_TYPE_ERR == s_stDrive_Adc_Handle.rec_data_index)
    {
       return SIGNED_TYPE_ERR;
    }
    handle->read_magnetic_encoder_data = Read_Magnetic_Encoder_Data;
    handle->rec_data_index =  s_stDrive_Adc_Handle.rec_data_index;
    
    return SIGNED_TYPE_SUCCESS;
}

/**
  * @brief  ��ȡ�ű���Ӧ������
  * @param  adc_data_index:ADC�µ�ĳͨ����Ӧ�Ĵ洢�����±�
  * @retval ������ֵ�˲���adc�ɼ�ֵ
  */
u16 Read_Magnetic_Encoder_Data(const u8 adc_data_index)
{
    return s_stDrive_Adc_Handle.achieve_adc_data(adc_data_index, MAGNETIC_ENCODER_ADC_ID);
}
