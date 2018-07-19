/**
  ******************************************************************************
  * @file    task_motor_control.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.2
  * @brief   电机控制任务
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include  "task_motor_control.h"
#include  "app_hal_init.h"
#include  "stm32f10x_can_config.h"
#include  "api_can.h"
#include  "api_i2c.h"
#include  "api_exti.h"
#include  "api_tim.h"

#include  "FreeRTOS.h"
#include  "task.h"
#include  "queue.h"

#include  "stdio.h"

/* Private variables ---------------------------------------------------------*/
static volatile u16 s_vusReadMagneticData = 0;
u8  s_vusReadCommDataTable[USART5_QUEUE_LENGTH * (USART5_QUEUE_TYPE_L / sizeof(u8))] = {0};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  电机控制任务函数
  * @param  None
  * @retval None
  */
//can_msg rx_msg = {0};
u8 ret = 0;
u8 angel_tmp = 0x55;
void vMotorCtlTask( void * pvParameters )
{
    /*!< 模拟IIC测试 */
//    SimulateI2cInit(GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
//    SimulateI2cWriteBytes(0xA0, 0xFF, 1, &angel_tmp);
//    angel_tmp = 0;
//    SimulateI2cReadBytes(0xA0, 0xFF, 1, &angel_tmp);
//    if (angel_tmp == 0x55)
//    {
//        vTaskDelay( 10 / portTICK_RATE_MS );
//    }
        /*!< 硬件IIC测试 */
    HardwareI2cInit(2, 0, 0xA0);  
    HardwareI2cSendDataShell(0xFF, angel_tmp);
    angel_tmp = 0;

    /*!< 外部中断测试 */
//    ExtiInit(GPIOA, GPIO_Pin_2, 2);
    /*!< 定时器定时测试 */
//    InitTimerToTimeApi(1000, 72);
     /*!< 定时器PWM输出测试 */
//    InitTimToPwmApi(1, 0x06, 0, 100, 72);
//    TIM1->CCR2 = 50;
//    TIM1->CCR3 = 85;
    /*!< 定时器输入捕获测试 */
//    InitTimToCapApi(2, 0x0C, 0, 100, 72);
    
    while(1)
    {       
        HardwareI2cReadDatasShell(0xFF, &angel_tmp, 1);
        
        vTaskDelay( 100 / portTICK_RATE_MS );
        
        /*!< 测试串口打印和通信 */        
//        printf("hello world !!!!\r\n");        
//        if(NULL == g_stComm_Lidar_Board_Ctl.xQueue)
//        {
//            vTaskDelay( 100 / portTICK_RATE_MS );
//            break;
//        }
        /*!< 磁编码测试ADC和DMA */
//        s_vusReadMagneticData = g_stMagnetic_Encoder_Desc.read_magnetic_encoder_data(g_stMagnetic_Encoder_Desc.rec_data_index);
        /*!< 串口测试 */
//        ret_status = xQueueReceive( g_stComm_Lidar_Board_Ctl.xQueue, &s_vusReadCommDataTable[4], 100 / portTICK_RATE_MS);
//        if( ret_status == pdPASS )
//        {
//            rev_data_cnt++;
//            s_vusReadCommDataTable[0] = rev_data_cnt & 0xFF;
//            s_vusReadCommDataTable[1] = ((rev_data_cnt & 0xFF00) >> 8);
//            s_vusReadCommDataTable[2] = ((rev_data_cnt & 0xFF0000) >> 16);
//            s_vusReadCommDataTable[3] = ((rev_data_cnt & 0xFF000000) >> 24);
//            g_stComm_Lidar_Board_Ctl.usart_send(g_stComm_Lidar_Board_Ctl.usart_id, &s_vusReadCommDataTable[0], 4);
//        }
    }
}

/*!< 定时器定时测试 */
//u32 tim_cnt = 0;
//void TIM5_IRQHandler(void)
//{
//	if(TIM5->SR & 0x0001)//溢出中断
//	{
//		TIM5->SR &=~(1<<0);//清除中断标志位
//		{
//            tim_cnt++;
//        }
//    }
//}

/*!< 定时器输入捕获测试 */
//u8  TIM2CH3_CAPTURE_STA = 0;	//输入捕获状态	
//u16	TIM2CH3_CAPTURE_VAL = 0;	//输入捕获值
//void TIM2_IRQHandler(void)
//{    
//    if ((TIM2CH3_CAPTURE_STA & 0x80) == 0)//还未成功捕获	
//    {
//        if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//		 
//		{	    
//			if(TIM2CH3_CAPTURE_STA & 0x40)//已经捕获到高电平了
//			{
//				if((TIM2CH3_CAPTURE_STA & 0x3F)==0x3F)//高电平太长了
//				{
//					TIM2CH3_CAPTURE_STA |= 0x80;//标记成功捕获了一次
//					TIM2CH3_CAPTURE_VAL=0XFFFF;
//				}else TIM2CH3_CAPTURE_STA++;
//			}	 
//		}
//        
//        if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET) //捕获边沿
//        {	 
//            if(TIM2CH3_CAPTURE_STA & 0x40) 	 
//            {			
//                TIM2CH3_CAPTURE_STA |= 0x80;
//                TIM2CH3_CAPTURE_VAL = TIM_GetCapture3(TIM2);
//                TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//            }
//            else								 
//            {
//                TIM2CH3_CAPTURE_STA = 0;
//                TIM2CH3_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM2,0);
//                TIM2CH3_CAPTURE_STA |= 0x40;
//                TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Falling);	 //CC1P=1 设置为下降沿捕获
//            }
//        }
//    }
//	TIM_ClearITPendingBit(TIM2, TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
//}

