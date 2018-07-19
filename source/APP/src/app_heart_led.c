/**
  ******************************************************************************
  * @file    app_heart_led.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.4
  * @brief   心跳灯业务层
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "app_heart_led.h"
#include "app_hal_init.h"

/* Private variables ---------------------------------------------------------*/
static dev_heart_led_desc_t s_stHandle = {0};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  心跳灯初始化
  * @param  None
  * @retval None
  */	
static void Heart_LED_Init(void)
{
    pinMode(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
}
/**
  * @brief  心跳灯正常模式
  * @param  None
  * @retval None
  */	
static void HeartLedNomal(dev_heart_led_desc_t *handle)
{
    u8 heart_led_nomal_par = CTL_LED_NOMAL;
    
    handle->heart_led_ctl_status = heart_led_nomal_par;
}
/**
  * @brief  心跳灯繁忙模式
  * @param  None
  * @retval None
  */	
static void HeartLedBusy (dev_heart_led_desc_t *handle)
{
    u8 heart_led_busy_par = CTL_LED_BUSY;
    
    handle->heart_led_ctl_status = heart_led_busy_par;
}
/**
  * @brief  心跳灯错误模式
  * @param  None
  * @retval None
  */
static void HeartLedError (dev_heart_led_desc_t *handle)
{
    u8 heart_led_error_par = CTL_LED_ERROR;
    
    handle->heart_led_ctl_status = heart_led_error_par;
}
/**
  * @brief  HAL注册心跳灯控制并初始化。
  * @param  用于返回控制点的句柄
  * @retval None
  */
void drv_heart_led_init(dev_heart_led_desc_t * handle)
{
    Heart_LED_Init();
    
    s_stHandle.heart_led_init      = Heart_LED_Init;
    s_stHandle.heart_led_ctl_nomal = HeartLedNomal;
    s_stHandle.heart_led_ctl_busy  = HeartLedBusy;
    s_stHandle.heart_led_ctl_error = HeartLedError;
    
    *handle = s_stHandle;
}

/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

