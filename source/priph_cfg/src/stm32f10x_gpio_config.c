/**
  ******************************************************************************
  * @file    stm32f10x_gpio_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   gpio功能模块
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio_config.h"

/**
  * @brief  初始化GPIO
  * @param  None
  * @retval None
  */
void pinMode(GPIO_TypeDef* GPIOx,
	uint16_t pin,
	GPIOMode_TypeDef mode,
	GPIOSpeed_TypeDef GPIO_Speed
)
{
    GPIO_InitTypeDef init;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF, ENABLE);
	
	init.GPIO_Pin = pin;
	init.GPIO_Mode = mode;
	init.GPIO_Speed = GPIO_Speed;
	GPIO_Init(GPIOx, &init);
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
