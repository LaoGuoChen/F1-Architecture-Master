/**
  ******************************************************************************
  * @file    stm32f10x_adc_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   ADC功能模块
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_adc_config.h"
#include "stm32f10x_dma_config.h"
#include "api_adc.h"
#include "common.h"

/* Private variables ---------------------------------------------------------*/
volatile u8  g_vucAdc1ChannelNum = 0;
volatile u8  g_vucAdc2ChannelNum = 0;
volatile u8  g_vucAdc3ChannelNum = 0;

#if      ADC1SAMPLE
    volatile u16 g_vusAdc1ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC2SAMPLE
    volatile u16 g_vusAdc2ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
#if      ADC3SAMPLE
    volatile u16 g_vusAdc3ValueBuff[16 * SAMPLE_CNT] = {0};  ///<建立最大数据存储ADC采集的数据
#endif
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  初始化ADC1或ADC2的某一个
  * @param  gpio_par:通道号
  * @retval None
  */
static void InitAdc12Gpio(const u8 gpio_par)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    
    switch (gpio_par)
    {
        case 0: 
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 1:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 2:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 3:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 4: 
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 5:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 6:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 7:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 8:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 9:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 10:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 11:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 12:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 13:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
       case 14:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 15:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        default :
            break;
    }
}
/**
  * @brief  初始化ADC3
  * @param  gpio_par:通道号
  * @retval None
  */
static void InitAdc3Gpio(const u8 gpio_par)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    
    switch (gpio_par)
    {
        case 0: 
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 1:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 2:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 3:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        break;
        case 4: 
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 5:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 6:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 7:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 8:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_Init(GPIOF, &GPIO_InitStructure);
        break;
        case 9:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        break;
        case 10:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 11:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 12:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 13:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
       case 14:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        case 15:
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        break;
        default :
            break;
    }
    
}
/**
  * @brief  ADC1配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc1(const u8 gpio_par)
{
    static u8 channel_num = 0;
	ADC_InitTypeDef ADC_InitStrucutre;

    g_vucAdc1ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitStrucutre.ADC_Mode = ADC_Mode_Independent; //ADC工作在独立模式
	ADC_InitStrucutre.ADC_ScanConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ContinuousConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发
	ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStrucutre.ADC_NbrOfChannel = g_vucAdc1ChannelNum; //顺序进行转换的工作模式
	ADC_Init(ADC1, &ADC_InitStrucutre);
    if ( ++channel_num > 16)
        return SIGNED_TYPE_ERR;
	/* 设定AD采集通道转换顺序 */
        switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC1, ADC_Channel_0, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_1, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_2, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_3, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC1, ADC_Channel_4, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_5, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_6, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_7, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_8, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 9:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_9, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_10, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_11, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_12, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_13, channel_num, ADC_SampleTime_55Cycles5); 
        break;
       case 14:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_14, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 15:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_15, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        default :
            break;
    }
	
	/* ADC 时钟8分频 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	/* 使能 ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* 使能 ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1); /* 重置ADC1校准寄存器 */
	while(ADC_GetResetCalibrationStatus(ADC1)); /* 等待ADC1校准重置完成  */
	ADC_StartCalibration(ADC1); /* 开始ADC1校准 */
	while(ADC_GetCalibrationStatus(ADC1));  /* 等待ADC1校准完成 */
	/* 使能 ADC1软件触发转换 */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    
    return channel_num;
}
/**
  * @brief  ADC2配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc2(const u8 gpio_par)
{
    static u8 channel_num = 0;
	ADC_InitTypeDef ADC_InitStrucutre;

    g_vucAdc2ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	ADC_InitStrucutre.ADC_Mode = ADC_Mode_Independent; //ADC工作在独立模式
	ADC_InitStrucutre.ADC_ScanConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ContinuousConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发
	ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStrucutre.ADC_NbrOfChannel = g_vucAdc2ChannelNum; //顺序进行转换的工作模式
	ADC_Init(ADC2, &ADC_InitStrucutre);
    if ( ++channel_num > 16)
        return SIGNED_TYPE_ERR;
	/* 设定AD采集通道转换顺序 */
    switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC2, ADC_Channel_0, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_1, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_2, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_3, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC2, ADC_Channel_4, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_5, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_6, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_7, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_8, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 9:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_9, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_10, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_11, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_12, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_13, channel_num, ADC_SampleTime_55Cycles5); 
        break;
       case 14:
            ADC_RegularChannelConfig(ADC2, ADC_Channel_14, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 15:
            ADC_RegularChannelConfig(ADC1, ADC_Channel_15, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        default :
            break;
    }
	
	/* ADC 时钟8分频 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	/* 使能 ADC1 DMA */
	ADC_DMACmd(ADC2, ENABLE);
	/* 使能 ADC1 */
	ADC_Cmd(ADC2, ENABLE);
	ADC_ResetCalibration(ADC2); /* 重置ADC1校准寄存器 */
	while(ADC_GetResetCalibrationStatus(ADC2)); /* 等待ADC1校准重置完成  */
	ADC_StartCalibration(ADC2); /* 开始ADC1校准 */
	while(ADC_GetCalibrationStatus(ADC2));  /* 等待ADC1校准完成 */
	/* 使能 ADC1软件触发转换 */
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    
    return channel_num;
}
/**
  * @brief  ADC3配置通道
  * @param  gpio_par:通道号
  * @retval None
  */
static s8 InitAdc3(const u8 gpio_par)
{
    static u8 channel_num = 0;
	ADC_InitTypeDef ADC_InitStrucutre;

    g_vucAdc3ChannelNum = channel_num + 1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	ADC_InitStrucutre.ADC_Mode = ADC_Mode_Independent; //ADC工作在独立模式
	ADC_InitStrucutre.ADC_ScanConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ContinuousConvMode = ENABLE; //模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发
	ADC_InitStrucutre.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStrucutre.ADC_NbrOfChannel = g_vucAdc3ChannelNum; //顺序进行转换的工作模式
	ADC_Init(ADC3, &ADC_InitStrucutre);
    if ( ++channel_num > 13)
        return SIGNED_TYPE_ERR;
	/* 设定AD采集通道转换顺序 */
    switch (gpio_par)
    {
        case 0: 
            ADC_RegularChannelConfig(ADC3, ADC_Channel_0, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 1:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_1, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 2:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_2, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 3:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_3, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 4: 
            ADC_RegularChannelConfig(ADC3, ADC_Channel_4, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 5:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_5, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 6:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_6, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 7:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_7, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 8:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_8, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 10:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_10, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 11:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_11, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 12:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_12, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        case 13:
            ADC_RegularChannelConfig(ADC3, ADC_Channel_13, channel_num, ADC_SampleTime_55Cycles5); 
        break;
        default :
            break;
    }
	
	/* ADC 时钟8分频 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	/* 使能 ADC1 DMA */
	ADC_DMACmd(ADC3, ENABLE);
	/* 使能 ADC1 */
	ADC_Cmd(ADC3, ENABLE);
	ADC_ResetCalibration(ADC3); /* 重置ADC1校准寄存器 */
	while(ADC_GetResetCalibrationStatus(ADC3)); /* 等待ADC1校准重置完成  */
	ADC_StartCalibration(ADC3); /* 开始ADC1校准 */
	while(ADC_GetCalibrationStatus(ADC3));  /* 等待ADC1校准完成 */
	/* 使能 ADC1软件触发转换 */
	ADC_SoftwareStartConvCmd(ADC3, ENABLE);
    
    return channel_num;
}
/**
  * @brief  初始化ADC
  * @param  adc_num:adc数 如1即为ADC1
  * @param  adc_channel_sum:该ADC下的所有adc通道,每二进制位数的高低代表对应通道的开启状态，如101=0x0065=0B0000000001100101代表通道0、2、5、6采集
  * @retval -1：传入参数错误,>0:adc对应通道的存储数据下标
  */
s8 Adc_Init(const u8 adc_num, const u16 adc_channel_sum)
{
    u8 get_par_channel_index = 0;
    s8 adc_rec_data_index = 0;
    
    if (adc_num == 0 || adc_num > 3 || adc_channel_sum == 0) /* 传入参数错误 */
        return SIGNED_TYPE_ERR;
    
    switch (adc_num)
    {
        case 1:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc12Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc1(get_par_channel_index);
                }
            }
             DMA_ADC1_Config();
        }
        break;
        case 2:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc12Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc2(get_par_channel_index);
                }
            }
            
        }
        break;
        
        case 3:
        {
            for (get_par_channel_index = 0; get_par_channel_index < 16; get_par_channel_index++)
            {
                if ( ( adc_channel_sum >> get_par_channel_index ) & 0x01)
                {
                    InitAdc3Gpio(get_par_channel_index);
                    adc_rec_data_index = InitAdc3(get_par_channel_index);
                }
            }
            DMA_ADC3_Config();
        }
        break;
    }
    
    return adc_rec_data_index;
}
/**
  * @brief  获取ADC的采集值
  * @param  rec_data_index:ADC下的某通道对应的存储数据下标
  * @param  adc_num:adc数,如1即为ADC1
  * @retval 0:传入参数错误 
  * @retval >0:经过均值滤波的adc采集值
  */
u16 Achieve_Adc_Data(const u8 rec_data_index, const u8 adc_num)
{
    u32 calc_sum          = 0;
    u8  calc_index        = 0;
    u8  adc_channel_index = 0;
    u16 return_voltage_ma = 0;
    
    if (rec_data_index > 18 || adc_num == 0 || adc_num > 3) /* 传入参数错误 */
        return 0;
    
    #if ADC1SAMPLE
    if (adc_num == 1)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc1ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    #if ADC2SAMPLE
    if (adc_num == 2)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc2ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    #if ADC3SAMPLE
    if (adc_num == 3)
    {
        for (calc_index = 0; calc_index < SAMPLE_CNT; calc_index++)
        {
            adc_channel_index = (rec_data_index - 1) + g_vucAdc3ChannelNum * calc_index;
            calc_sum += g_vusAdc3ValueBuff[adc_channel_index];
        }
        
        return_voltage_ma = calc_sum * 3300 / SAMPLE_CNT / 4096;
        
        return return_voltage_ma;
    }
    #endif
    
    return 0;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

