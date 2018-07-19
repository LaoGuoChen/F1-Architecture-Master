/**
  ******************************************************************************
  * @file    stm32f10x_dma_config.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio����ģ��
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dma_config.h"
#include "stm32f10x_adc_config.h"
#include "api_adc.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ADC1��DMA����
  * @param  None
  * @retval None
  */
void DMA_ADC1_Config(void)
{
#if      ADC1SAMPLE    
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //0x4001244C; //ADC1->DR; //DMA����ADC��ַ(0x4001244C);
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_vusAdc1ValueBuff;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc1ChannelNum; //DMAͨ���Ļ����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ��Xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��û������Ϊ���ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	DMA_Cmd(DMA1_Channel1 , ENABLE);//Enable the DMA1
#endif
}
/**
  * @brief  ADC3��DMA����
  * @param  None
  * @retval None
  */
void DMA_ADC3_Config(void)
{
#if      ADC3SAMPLE 
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	DMA_DeInit(DMA2_Channel5); //��DMA��ͨ��5�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC3->DR; //DMA����ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_vusAdc3ValueBuff; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc3ChannelNum; //DMAͨ���Ļ����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ��Xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��û������Ϊ���ڴ浽�ڴ洫��
	DMA_Init(DMA2_Channel5, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	DMA_Cmd(DMA2_Channel5 , ENABLE);//Enable the DMA2
#endif
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
