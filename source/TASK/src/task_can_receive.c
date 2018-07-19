/**
  ******************************************************************************
  * @file    task_can_receive.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.13
  * @brief   CAN接收数据处理
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include  "task_can_receive.h"
#include  "can_macro.h"
#include  "app_hal_init.h"
/* Private variables ---------------------------------------------------------*/
typedef struct
{
    u16 left_param;
    u16 right_parma;    
}MotorSpeedParam_t;
static u16 s_usLeftMotorSpeed = 0, s_usRightMotorSpeed = 0;
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  can通信电机控制通道
  * @param  None
  * @retval None
  */
static void Can_Command_MOTOR_CTL_CH(can_msg *pmsg)
{
    can_msg tx_msg = {0};  
    
    u8 pro = (pmsg->id & PRO_MASK) >> 4;
    
    switch(pro)
    {
		case CHASSIS_SET_SCRAM_STOP:
			break;
		case CHASSIS_SET_NORMAL_STOP:
			break;
		case CHASSIS_SET_MOTOR_MODE:
			break;
        case CHASSIS_GET_MOTOR_MODE:
			break;
		case CHASSIS_GET_MOTOR_SPEED:
            if(pmsg->type == REMOTE_FRAME)
            {
                MotorSpeedParam_t TxMotorSpeed = {0};
                TxMotorSpeed.left_param = s_usLeftMotorSpeed;
                TxMotorSpeed.left_param = s_usRightMotorSpeed;
                tx_msg.id = (pmsg->id & 0x100FFFFF) & ((pmsg->id & 0x00F00000) << 4) & ((pmsg->id & 0x0F000000) >> 4);/*交换源和目的ID*/
                g_stComm_Can_Bus.can_send_data_frame(tx_msg.id, (u8 *)&TxMotorSpeed, sizeof(TxMotorSpeed));
			}
			break;
		case CHASSIS_SET_MOTOR_SPEED:
            if(pmsg->type == DATA_FRAME)
            {
                MotorSpeedParam_t RxMotorSpeed = {0};
                RxMotorSpeed = *((MotorSpeedParam_t *)pmsg->data);
			}
			break;
		default:
			break;
	}
}
/**
  * @brief  can通信接收数据处理函数
  * @param  None
  * @retval None
  */
static void CanCommandProcess(can_msg *pmsg)
{
    u8 ch = (pmsg->id & CH_MASK) >> 12;
    
    if(((pmsg->id & DEST_ID_MASK) >> 20) != OWN_DEVICE_ID) /*!< 判断目的ID是否为自己的ID */
        return;
    
    switch(ch)
    {
        case CHASSIS_MOTOR_CTL_CH:
			Can_Command_MOTOR_CTL_CH(pmsg);
			break;
		default:
			break;
    }
    
}
/**
  * @brief  can通信接收数据处理任务函数
  * @param  None
  * @retval None
  */
void vCanReceiveTask( void * pvParameters )
{
    can_msg rx_msg = {0};

    while(1)
    {       
        if(g_stComm_Can_Bus.can_receive_data(&rx_msg, 10 / portTICK_RATE_MS) == SIGNED_TYPE_SUCCESS)
        {
            CanCommandProcess(&rx_msg);
        }
    }
}
