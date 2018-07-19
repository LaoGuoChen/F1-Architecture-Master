/**
  ******************************************************************************
  * @file    api_adc.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   adcӦ�ýӿڲ�
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __ADC_API_H
#define  __ADC_API_H

#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_adc_config.h"
#include "common.h"
/* Exported types ------------------------------------------------------------*/
/** 
  * adc_init:ADC��ʼ�� \n
  * achieve_adc_data:��ȡADC�ɼ����� \n
  */
typedef struct drive_adc_desc drive_adc_desc_t;

struct drive_adc_desc{
    s8   (*adc_init)         (u8 adc_num_par, u16 adc_channel_par); /*!< ADC��ʼ��   */
    u16  (*achieve_adc_data) (u8 rec_data_index, u8 adc_num_par);   /*!< ��ȡADC�ɼ����� */    
    s8   rec_data_index;
};
/* Exported Defines ----------------------------------------------------------*/
#define  ADC1SAMPLE (TURN_OFF)	
#define  ADC2SAMPLE (TURN_OFF)
#define  ADC3SAMPLE (TURN_ON)

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  HALע��ADC.
  * @param  handle:���ڷ��ؿ��Ƶ�ľ��
  * @retval None
  */
void drive_adc_init(drive_adc_desc_t * handle);

    
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/******************* (C) COPYRIGHT 2018 HWJ *****END OF FILE****/
  
