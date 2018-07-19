/**
  ******************************************************************************
  * @file    app_heart_led.h
  * @author  ������  
  * @version V1.0
  * @date    2018.6.4
  * @brief   ������ҵ���
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
  * heart_led_init:�����Ƴ�ʼ�� \n
  * heart_led_ctl_nomal:����������ģʽ \n
  * heart_led_ctl_busy:�����Ʒ�æģʽ \n
  * heart_led_ctl_error:�����ƴ���ģʽ \n
  * heart_led_ctl_status:�����ƿ���״̬ \n
  */
typedef struct dev_heart_led_desc dev_heart_led_desc_t;

struct dev_heart_led_desc{
    void (*heart_led_init)      (void);                         /*!< �����Ƴ�ʼ��   */
    void (*heart_led_ctl_nomal) (dev_heart_led_desc_t *handle); /*!< ����������ģʽ */
    void (*heart_led_ctl_busy)  (dev_heart_led_desc_t *handle); /*!< �����Ʒ�æģʽ */
    void (*heart_led_ctl_error) (dev_heart_led_desc_t *handle); /*!< �����ƴ���ģʽ */
    u8    heart_led_ctl_status;                                /*!< �����ƿ���״̬ */
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
  * @brief  HALע�������ƿ��Ʋ���ʼ����
  * @param  ���ڷ��ؿ��Ƶ�ľ��
  * @retval None
  */
void drv_heart_led_init(dev_heart_led_desc_t * handle);
    
	
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif

