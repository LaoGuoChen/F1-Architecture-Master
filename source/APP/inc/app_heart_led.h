/**
  ******************************************************************************
  * @file    app_heart_led.h
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.4
  * @brief   心跳灯业务层
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __APP_HEART_LED_H
#define  __APP_HEART_LED_H


#ifdef __cplusplus
extern "C" {
#endif
	
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio_config.h"

/* Exported types ------------------------------------------------------------*/
    
/** 
  * heart_led_init:心跳灯初始化 \n
  * heart_led_ctl_nomal:心跳灯正常模式 \n
  * heart_led_ctl_busy:心跳灯繁忙模式 \n
  * heart_led_ctl_error:心跳灯错误模式 \n
  * heart_led_ctl_status:心跳灯控制状态 \n
  */
typedef struct dev_heart_led_desc dev_heart_led_desc_t;

struct dev_heart_led_desc{
    void (*heart_led_init)      (void);                         /*!< 心跳灯初始化   */
    void (*heart_led_ctl_nomal) (dev_heart_led_desc_t *handle); /*!< 心跳灯正常模式 */
    void (*heart_led_ctl_busy)  (dev_heart_led_desc_t *handle); /*!< 心跳灯繁忙模式 */
    void (*heart_led_ctl_error) (dev_heart_led_desc_t *handle); /*!< 心跳灯错误模式 */
    u8    heart_led_ctl_status;                                /*!< 心跳灯控制状态 */
};

/* Exported macro ------------------------------------------------------------*/   
enum{
    CTL_LED_NOMAL = 1,
    CTL_LED_BUSY  = 2,
    CTL_LED_ERROR = 3,
};
/* Exported define -----------------------------------------------------------*/
#define  HEART_LED_EN (TURN_ON)	

/**
  * @brief  HAL注册心跳灯控制并初始化。
  * @param  用于返回控制点的句柄
  * @retval None
  */
void drv_heart_led_init(dev_heart_led_desc_t * handle);
    
	
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif

