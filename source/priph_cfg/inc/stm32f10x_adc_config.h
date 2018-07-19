/**
  ******************************************************************************
  * @file    stm32f10x_adc_config.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ADC����ģ��
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __STM32F10x_ADC_CONFIG_H
#define  __STM32F10x_ADC_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

    
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "api_adc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
    
#define  SAMPLE_CNT    (10)    /*!< �ɼ����� */
/* Private functions ---------------------------------------------------------*/
    
/**
  * @brief  ��ʼ��ADC
  * @param  adc_num:adc�� ��1��ΪADC1
  * @param  adc_channel_sum:��ADC�µ�����adcͨ��,ÿ������λ���ĸߵʹ����Ӧͨ���Ŀ���״̬����101=0x0065=0B0000000001100101����ͨ��0��2��5��6�ɼ�
  * @retval -1:�����������,>0:adc��Ӧͨ���Ĵ洢�����±�
  */
s8 Adc_Init(const u8 adc_num, const u16 adc_channel_sum);

/**
  * @brief  ��ȡADC�Ĳɼ�ֵ
  * @param  rec_data_index:ADC�µ�ĳͨ����Ӧ�Ĵ洢�����±�
  * @param  adc_num:adc��,��1��ΪADC1
  * @retval 0:�����������,>0:������ֵ�˲���adc�ɼ�ֵ
  */
u16 Achieve_Adc_Data(const u8 rec_data_index, const u8 adc_num);

/* Exported Variable ----------------------------------------------*/        
extern volatile u8 g_vucAdc1ChannelNum;
extern volatile u8 g_vucAdc2ChannelNum;
extern volatile u8 g_vucAdc3ChannelNum;
  
#if      ADC1SAMPLE
    extern volatile u16 g_vusAdc1ValueBuff[16 * SAMPLE_CNT];  ///<����������ݴ洢ADC�ɼ�������
#endif
#if      ADC2SAMPLE
    extern volatile u16 g_vusAdc2ValueBuff[16 * SAMPLE_CNT];  ///<����������ݴ洢ADC�ɼ�������
#endif
#if      ADC3SAMPLE
    extern volatile u16 g_vusAdc3ValueBuff[16 * SAMPLE_CNT];  ///<����������ݴ洢ADC�ɼ�������
#endif


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

