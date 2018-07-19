/**
  ******************************************************************************
  * @file    stm32f10x_dma_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dma_config.h"
#include "stm32f10x_adc_config.h"
#include "api_adc.h"

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  ADC1的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC1_Config(void)
{
#if      ADC1SAMPLE    
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //0x4001244C; //ADC1->DR; //DMA外设ADC地址(0x4001244C);
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_vusAdc1ValueBuff;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc1ChannelNum; //DMA通道的缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道X拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道没有设置为从内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道
	DMA_Cmd(DMA1_Channel1 , ENABLE);//Enable the DMA1
#endif
}
/**
  * @brief  ADC3的DMA配置
  * @param  None
  * @retval None
  */
void DMA_ADC3_Config(void)
{
#if      ADC3SAMPLE 
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	DMA_DeInit(DMA2_Channel5); //将DMA的通道5寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC3->DR; //DMA外设ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_vusAdc3ValueBuff; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = SAMPLE_CNT * g_vucAdc3ChannelNum; //DMA通道的缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道X拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道没有设置为从内存到内存传输
	DMA_Init(DMA2_Channel5, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道
	DMA_Cmd(DMA2_Channel5 , ENABLE);//Enable the DMA2
#endif
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
