/**
  ******************************************************************************
  * @file   stm32f10x_tim_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   tim功能模块
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim_config.h"
#include "api_tim.h"

#define EXPAND_WRAPPER( __NEXTLEVEL__, ...)  __NEXTLEVEL__( __VA_ARGS__ )
#define _GET_TIM(x)                          TIM##x
#define GET_TIM(x)                           EXPAND_WRAPPER(_GET_TIM, x)
#define _GET_TIM_IRQ(x)                      TIM##x##_IRQn
#define GET_TIM_IRQ(x)                           EXPAND_WRAPPER(_GET_TIM_IRQ, x)
#define _GET_TIM27_RCC(x)                    RCC_APB1Periph_TIM##x
#define GET_TIM2_7_RCC(x)                    EXPAND_WRAPPER(_GET_TIM27_RCC, x)
#define _GET_TIM18_RCC(x)                    RCC_APB2Periph_TIM##x
#define GET_TIM1_8_RCC(x)                    EXPAND_WRAPPER(_GET_TIM18_RCC, x)
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  初始化定时器定时操作
  * @param  load_value:计数装载值
  * @param  prescaler:预分频系数
  * @retval None
  */
void InitTimerToTime(const u16 load_value, const u16 prescaler)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

#if ((TIM_TO_TIME_ID == 1) || (TIM_TO_TIME_ID == 8))
    RCC_APB2PeriphClockCmd(GET_TIM1_8_RCC(TIM_TO_TIME_ID), ENABLE);
#else
    RCC_APB1PeriphClockCmd(GET_TIM2_7_RCC(TIM_TO_TIME_ID), ENABLE);
#endif 
    
	TIM_DeInit(GET_TIM(TIM_TO_TIME_ID));

	TIM_TimeBaseStructure.TIM_Period = load_value;         ///<装载值
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler - 1;   /*!< 分频系数 APB1_Max = 36M APB2_Max = 72M 预分频系数为1时 不倍频 否则倍频 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(GET_TIM(TIM_TO_TIME_ID), &TIM_TimeBaseStructure);

    NVIC_InitStructure.NVIC_IRQChannel = GET_TIM_IRQ(TIM_TO_TIME_ID);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	TIM_ClearFlag(GET_TIM(TIM_TO_TIME_ID), TIM_FLAG_Update);
	TIM_ITConfig(GET_TIM(TIM_TO_TIME_ID), TIM_IT_Update, ENABLE);
	TIM_Cmd(GET_TIM(TIM_TO_TIME_ID), ENABLE);
}
/**
  * @brief  根据定时器号使能定时器时钟
  * @param  tim_id:定时器的编号
  * @retval None
  */
static void EnableTimRccClock(const u8 tim_id)
{
    switch (tim_id)
    {
        case 1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   ///<使能TIM1时钟
            break;
        case 2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   ///<使能TIM2时钟
            break; 
        case 3:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   ///<使能TIM3时钟
            break;
        case 4:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   ///<使能TIM4时钟
            break; 
        case 8:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   ///<使能TIM8时钟
            break; 
        default:
            break;
    }
}
/**
  * @brief  初始化定时器IO操作
  * @param  mode:
            -0:配置Tim为输入捕获
            -1:配置Tim为PWM输出
  * @param  tim_id:定时器的编号
  * @param  channel:通道数和，后四位每位的高低状态表示CH1-4的选择状态。如0x06表示选择了CH2和CH4.
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @retval None
  */
static void ConfigTimGpio(const u8 mode, const u8 tim_id, const u8 channel, const u8 remap)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    u8 tim_id_remap = (((tim_id & 0x0f) << 4) | (remap & 0x0f));
    
    if(mode == 0)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //复用功能输出
    }
    else if(mode == 1)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
    }
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    switch (tim_id_remap)
    {
        case 0x10:/*!< TIM1的无重映射和部分重映射的CH1-4相同 */         
        case 0x11:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  ///<使能GPIOD时钟
            
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_8);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_9);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_10);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_11);	  
            }	            
        }
            break;
        case 0x12:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOE, GPIO_Pin_9);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;            
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOE, GPIO_Pin_11);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;            
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOE, GPIO_Pin_13);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;            
                GPIO_Init(GPIOE, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOE, GPIO_Pin_14);	  
            }					
        }            
            break;
        case 0x20:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  ///<使能GPIOD时钟

            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_0);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_1);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_2);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_3);	  
            }							
        }  
            break;
        case 0x21:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_15);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_2);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_3);	  
            }
        }
            break;
        case 0x22:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_0);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_1);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_10);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_11);	  
            }
        }
            break;
        case 0x23:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_15);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_3);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_10);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_11);	  
            }
        }
            break;
        case 0x30:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_6);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;            
                GPIO_Init(GPIOA, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOA, GPIO_Pin_7);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_0);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);	  
            }
        }
            break;
        case 0x31:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_4);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_5);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_0);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);	  
            }
        }
            break;
        case 0x32:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_6);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_7);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_8);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_9);	  
            }
        }
            break;
        case 0x40:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  ///<使能GPIOD时钟
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_6);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_7);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_8);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            
                GPIO_Init(GPIOB, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOB, GPIO_Pin_9);	  
            }
        }
            break;
        case 0x41:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  ///<使能GPIOD时钟
            GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;            
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOD, GPIO_Pin_12);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;            
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOD, GPIO_Pin_13);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;            
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOD, GPIO_Pin_14);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;            
                GPIO_Init(GPIOD, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOD, GPIO_Pin_15);	  
            }
        }
            break;
        case 0x80:
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  ///<使能GPIOD时钟
            
            if (channel & 0x01)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_6);	  
            }
            if (channel & 0x02)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_7);	  
            }	
            if (channel & 0x04)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_8);	  
            }	 
            if (channel & 0x08)
            {
                GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            
                GPIO_Init(GPIOC, &GPIO_InitStructure);
                GPIO_ResetBits(GPIOC, GPIO_Pin_9);	  
            }
        }
            break;
        default:
            break;
    }
}
/**
  * @brief  根据定时器编号初始化对应参数
  * @param  tim_id:定时器的编号
  * @param  TIM_TimeBaseStructure:定时器的参数
  * @retval None
  */
static void InitTimeBase(const u8 tim_id, TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure)
{
    switch (tim_id)
    {
        case 1:
            TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); ///<根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            break;
        case 2:
            TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); ///<根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            break; 
        case 3:
            TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); ///<根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            break;
        case 4:
            TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); ///<根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            break; 
        case 8:
            TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); ///<根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            break; 
        default:
            break;
    }

}
/**
  * @brief  初始化定时器输入捕获操作
  * @param  tim_id:定时器的编号
  * @param  channel:通道数和，后四位每位的高低状态表示CH1-4的选择状态。如0x06表示选择了CH2和CH4.
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @param  arr:重载计数
  * @param  psc:预分频系数
  * @retval None
  */
void InitTimToCap(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{	 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    u8 channel_index = 0;
    static u8 sub_priority = 0;
    
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);  ///<使能GPIO外设和AFIO复用功能模块时钟使能

    EnableTimRccClock(tim_id);
    
    ConfigTimGpio(0, tim_id, channel, remap);
     
    TIM_TimeBaseStructure.TIM_Period = arr; ///<设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler = psc; 	///<预分频器   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; ///<设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ///<TIM向上计数模式

    InitTimeBase(tim_id, TIM_TimeBaseStructure);
    
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	///<上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; ///<映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 ///<配置输入分频,不分频 
    TIM_ICInitStructure.TIM_ICFilter = 0x00;///<IC1F=0000 配置输入滤波器 不滤波
        
    for (channel_index = 0; channel_index < 4; channel_index++)
    {
        if (!((channel >> channel_index) & 0x01))
        {
            continue;
        }
        
        if (channel_index == 0)
        {
            TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 
        }
        else if (channel_index == 1)
        {
            TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;   
        }
        else if (channel_index == 2)
        {
            TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
        }
        else if (channel_index == 3)
        {
            TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 
        }
        switch (tim_id)
        {
            case 1:
                TIM_ICInit(TIM1, &TIM_ICInitStructure);    
                break;
            case 2:
                TIM_ICInit(TIM2, &TIM_ICInitStructure);    
                break; 
            case 3:
                TIM_ICInit(TIM3, &TIM_ICInitStructure);  
                break;
            case 4:
                TIM_ICInit(TIM4, &TIM_ICInitStructure);  
                break; 
            case 8:
                TIM_ICInit(TIM8, &TIM_ICInitStructure);  
                break; 
            default:
                break;
        }
    }
    
    ///<中断分组初始化
    switch (tim_id)
    {
        case 1:
            NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;   
            break;
        case 2:
            NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
            break; 
        case 3:
            NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
            break;
        case 4:
            NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
            break; 
        case 8:
            NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; 
            break; 
        default:
            break;
    }
    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_priority++; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);  
    
    switch (tim_id)
    {
        case 1:
            TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
            TIM_Cmd(TIM1, ENABLE ); 	
            break;
        case 2:
            TIM_ITConfig(TIM2, TIM_IT_Update | (channel << 1), ENABLE);// TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | 
            TIM_Cmd(TIM2, ENABLE ); 
            break; 
        case 3:
            TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
            TIM_Cmd(TIM3, ENABLE ); 
            break;
        case 4:
            TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
            TIM_Cmd(TIM4, ENABLE );   
            break; 
        case 8:
            TIM_ITConfig(TIM8, TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
            TIM_Cmd(TIM8, ENABLE ); 
            break; 
        default:
            break;
    }
}
/**
  * @brief  初始化定时器PWM操作
  * @param  tim_id:定时器的编号
  * @param  channel:通道数和，后四位每位的高低状态表示CH1-4的选择状态。如0x06表示选择了CH2和CH4.
  * @param  remap_par:重映射参数
  *         -0:无重映射
  *         -1:该串口有部分重映射则部分重映射，无则全重映射  
  *         -2:全重映射  
  * @param  arr:重载计数
  * @param  psc:预分频系数
  * @retval None
  */
void InitTimToPwm(const u8 tim_id, const u8 channel, const u8 remap, const u16 arr, const u16 psc)
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    u8 channel_index = 0;
    u8 tim_id_channel = 0;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);  ///<使能GPIO外设和AFIO复用功能模块时钟使能

    EnableTimRccClock(tim_id);
	
    ConfigTimGpio(1, tim_id, channel, remap);
    
	TIM_TimeBaseStructure.TIM_Period = arr; ///<设置自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; ///<设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; ///<设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ///<TIM向上计数模式
	InitTimeBase(tim_id, TIM_TimeBaseStructure);	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; ///<CH1 PWM2模式	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ///<比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; ///<设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; ///<OC1 低电平有效 

	
    for (channel_index = 0; channel_index < 4; channel_index++)
    {
        if(!((channel >> channel_index) & 0x01))
        {
            continue;
        }
        
        tim_id_channel = (((tim_id & 0x0f) << 4) | (channel_index & 0x0f));

        switch (tim_id_channel)
        {
            case 0x10:
            {
                TIM_OC1Init(TIM1, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  ///<CH1 预装载使能
            }
                break;
            case 0x11:
            {
                TIM_OC2Init(TIM1, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  ///<CH2 预装载使能
            }
                break;
            case 0x12:
            {
                TIM_OC3Init(TIM1, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  ///<CH3 预装载使能
            }
                break;
            case 0x13:
            {
                TIM_OC4Init(TIM1, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  ///<CH4 预装载使能
            }
                break;
            case 0x20:
            {
                TIM_OC1Init(TIM2, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  ///<CH1 预装载使能
            }
                break;
            case 0x21:
            {
                TIM_OC2Init(TIM2, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  ///<CH2 预装载使能
            }
                break;
            case 0x22:
            {
                TIM_OC3Init(TIM2, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  ///<CH3 预装载使能
            }
                break;
            case 0x23:
            {
                TIM_OC4Init(TIM2, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  ///<CH4 预装载使能
            }
                break;   
            case 0x30:
            {
                TIM_OC1Init(TIM3, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  ///<CH1 预装载使能
            }
                break;
            case 0x31:
            {
                TIM_OC2Init(TIM3, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  ///<CH2 预装载使能
            }
                break;
            case 0x32:
            {
                TIM_OC3Init(TIM3, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  ///<CH3 预装载使能
            }
                break;
            case 0x33:
            {
                TIM_OC4Init(TIM3, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  ///<CH4 预装载使能
            }
                break;
            case 0x40:
            {
                TIM_OC1Init(TIM4, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  ///<CH1 预装载使能
            }
                break;
            case 0x41:
            {
                TIM_OC2Init(TIM4, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  ///<CH2 预装载使能
            }
                break;
            case 0x42:
            {
                TIM_OC3Init(TIM4, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  ///<CH3 预装载使能
            }
                break;
            case 0x43:
            {
                TIM_OC4Init(TIM4, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  ///<CH4 预装载使能
            }
                break; 
            case 0x80:
            {
                TIM_OC1Init(TIM8, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  ///<CH1 预装载使能
            }
                break;
            case 0x81:
            {
                TIM_OC2Init(TIM8, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  ///<CH2 预装载使能
            }
                break;
            case 0x82:
            {
                TIM_OC3Init(TIM8, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  ///<CH3 预装载使能
            }
                break;
            case 0x83:
            {
                TIM_OC4Init(TIM8, &TIM_OCInitStructure);  ///<根据指定的参数初始化外设TIMx
                TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  ///<CH4 预装载使能
            }
                break; 
        }
    }
    switch (tim_id)
    {
        case 1:
        {
            TIM_ARRPreloadConfig(TIM1, ENABLE); ///<使能TIMx在ARR上的预装载寄存器
            TIM_CtrlPWMOutputs(TIM1, ENABLE);	///<MOE 主输出使能,高级定时器必须开启这个 
            TIM_Cmd(TIM1, ENABLE);  ///<使能TIMx        
        }
            break;
        case 2:
        {
            TIM_ARRPreloadConfig(TIM2, ENABLE); ///<使能TIMx在ARR上的预装载寄存器
            TIM_CtrlPWMOutputs(TIM2,ENABLE);	///<MOE 主输出使能,高级定时器必须开启这个 
            TIM_Cmd(TIM2, ENABLE);  ///<使能TIMx        
        }
            break;
        case 3:
        {
            TIM_ARRPreloadConfig(TIM3, ENABLE); ///<使能TIMx在ARR上的预装载寄存器
            TIM_CtrlPWMOutputs(TIM3,ENABLE);	///<MOE 主输出使能,高级定时器必须开启这个 
            TIM_Cmd(TIM3, ENABLE);  ///<使能TIMx        
        }
            break;
        case 4:
        {
            TIM_ARRPreloadConfig(TIM4, ENABLE); ///<使能TIMx在ARR上的预装载寄存器
            TIM_CtrlPWMOutputs(TIM4,ENABLE);	///<MOE 主输出使能,高级定时器必须开启这个 
            TIM_Cmd(TIM4, ENABLE);  ///<使能TIMx        
        }
            break;
        case 8:
        {
            TIM_ARRPreloadConfig(TIM8, ENABLE); ///<使能TIMx在ARR上的预装载寄存器
            TIM_CtrlPWMOutputs(TIM8,ENABLE);	///<MOE 主输出使能,高级定时器必须开启这个 
            TIM_Cmd(TIM8, ENABLE);  ///<使能TIMx        
        }
            break;
        default:
            break;
        
    }

}
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
