/**
  ******************************************************************************
  * @file    stm32f10x_i2c_config.c
  * @author  晏智雄  
  * @version V1.0
  * @date    2018.6.15
  * @brief   i2c功能模块
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_i2c_config.h"
#include "api_i2c.h"

typedef enum {
	IIC_NACK = 0,
	IIC_ACK
}IIC_REPLAY;

typedef enum {
	IIC_BUS_READY = 0,
	IIC_BUS_BUSY,
	IIC_BUS_ERROR
}IIC_BUS_STATE;

static GPIO_TypeDef *s_pGpioSclPort = {0}, *s_pGpioSdaPort = {0};
static u16 s_usGpioSclPin = 0, s_usGpioSdaPin = 0, s_usI2sSoftwareInitFlg = 0;
static u16 s_usSlaveAddress = 0;
static I2C_TypeDef* s_pHardwareI2c = {0};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  模拟IIC初始化
  * @param  gpio_scl_port
  * @retval None
  */
void I2c_Init(GPIO_TypeDef* gpio_scl_port, u16 gpio_scl_pin, GPIO_TypeDef* gpio_sda_port, u16 gpio_sda_pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);			     
    
 	GPIO_InitStructure.GPIO_Pin = gpio_scl_pin;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gpio_scl_port, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = gpio_sda_pin;
    GPIO_Init(gpio_sda_port, &GPIO_InitStructure);
    s_pGpioSclPort = gpio_scl_port;
    s_usGpioSclPin = gpio_scl_pin;
    s_pGpioSdaPort = gpio_sda_port;
    s_usGpioSdaPin = gpio_sda_pin;
    s_pGpioSdaPort->BSRR = s_usGpioSdaPin;
	s_pGpioSclPort->BSRR = s_usGpioSclPin;
    s_usI2sSoftwareInitFlg = 1;
}
/**
  * @brief  模拟IIC延时函数 f0时一个空即可。不同器件要求不一样 一般是1us左右
  * @param  None
  * @retval None
  */
static void I2c_Delay(void)    
{ 
    u8 timeout = 5;
    while(--timeout)
    {
        __NOP();
    }
}
/**
  * @brief  设置sda线电平
  * @param  level：对应的电平 1：高电平 0：低电平
  * @retval None
  */
static void Set_Sda_Bit(u8 level)
{
    if(level == 1)
    {
        s_pGpioSdaPort->BSRR = s_usGpioSdaPin;
    }
    else if(level == 0)
    {
        s_pGpioSdaPort->BRR = s_usGpioSdaPin;
    }
}
/**
  * @brief  设置scl线电平
  * @param  level：对应的电平 1：高电平 0：低电平
  * @retval None
  */
static void Set_Scl_Bit(u8 level)
{
    if(level == 1)
    {
        s_pGpioSclPort->BSRR = s_usGpioSclPin;
    }
    else if(level == 0)
    {
        s_pGpioSclPort->BRR = s_usGpioSclPin;
    }
}
/**
  * @brief  设置sda线输入输出方向
  * @param  level：对应的方向 1：输出 0：输入
  * @retval None
  */
static void Set_Sda_Direct(u8 direct)
{
    u16 gpio_sda_pin_tmp = (s_usGpioSdaPin >> 1);
    u8  index = 0;
    u32 tmp = 0;
    
    while(gpio_sda_pin_tmp)
    {
        gpio_sda_pin_tmp = (gpio_sda_pin_tmp >> 1);
        index ++;
    }
    if(index >= 8)
    {
        index -= 8;
        
        if(direct == 1)
        {
            tmp = (0xFFFFFFFF ^ (0xF << index * 4));
            s_pGpioSdaPort->CRH &= tmp;//0xFFFF0FFF; 
            tmp = (0x3 << index * 4);
            s_pGpioSdaPort->CRH |= tmp;//0x00003000;
        }
        else if(direct == 0)
        {
            tmp = (0xFFFFFFFF ^ (0xF << index * 4));
            s_pGpioSdaPort->CRH &= tmp;//0xFFFF0FFF; 
            tmp = (0x8 << index * 4);
            s_pGpioSdaPort->CRH |= tmp;//0x00008000;
        }
    }
    else
    {
        if(direct == 1)
        {
            tmp = (0xFFFFFFFF ^ (0xF << index * 4));
            s_pGpioSdaPort->CRL &= tmp;//0xFFFF0FFF; 
            tmp = (0x3 << index * 4);
            s_pGpioSdaPort->CRL |= tmp;//0x00003000;
        }
        else if(direct == 0)
        {
            tmp = (0xFFFFFFFF ^ (0xF << index * 4));
            s_pGpioSdaPort->CRL &= tmp;//0xFFFF0FFF; 
            tmp = (0x8 << index * 4);
            s_pGpioSdaPort->CRL |= tmp;//0x00008000;
        }
    }
}    
/**
  * @brief  模拟IIC开始时序
  * @param  None
  * @retval IIC总线的状态
  */
static IIC_BUS_STATE I2c_Start(void)
{
	Set_Sda_Direct(1);
	Set_Sda_Bit(1);
	Set_Scl_Bit(1);
    I2c_Delay();
	if((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == RESET)
		return IIC_BUS_BUSY;
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(0);
	I2c_Delay();
	if((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == SET)
		return IIC_BUS_ERROR;

	return IIC_BUS_READY;
}

/**
  * @brief  模拟IIC停止时序
  * @param  None
  * @retval None
  */
static void I2c_Stop(void)
{
	Set_Sda_Direct(1);
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Sda_Bit(1);
	I2c_Delay();	
}
/**
  * @brief  模拟IIC等待应答
  * @param  None
  * @retval 1:成功 0:失败
  */
static u8 I2c_Wait_Ack(void)
{
	u8 ucErrTime=250;
	
	Set_Sda_Direct(0);
	Set_Sda_Bit(1);
    I2c_Delay();	   
	Set_Scl_Bit(1);
    I2c_Delay(); 
	while((s_pGpioSdaPort->IDR & s_usGpioSdaPin) == SET) 
    {
		if(!--ucErrTime) 
        {
			I2c_Stop();
			return 0;
		}
		I2c_Delay();
	}
	Set_Scl_Bit(0);
	
	return 1;  
} 
/**
  * @brief  模拟IIC应答
  * @param  None
  * @retval None
  */
static void I2c_Ack(void)
{
	Set_Scl_Bit(0);
	Set_Sda_Direct(1);
	Set_Sda_Bit(0);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(0);
}
/**
  * @brief  模拟IIC不应答
  * @param  None
  * @retval None
  */    
static void I2c_NAck(void)
{
	Set_Scl_Bit(0);
	Set_Sda_Direct(1);
	Set_Sda_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(1);
	I2c_Delay();
	Set_Scl_Bit(0);
}					 				     

/**
  * @brief  模拟IIC发送一个字节
  * @param  None
  * @retval None
  */ 		  
static void I2c_Send_Byte(u8 txd)
{                        
	u8 t;   
    
	Set_Sda_Direct(1);
	Set_Scl_Bit(0);
	for(t = 0; t < 8; t++) {            
		if(txd & 0x80)
			Set_Sda_Bit(1);
		else
			Set_Sda_Bit(0);
		txd <<= 1; 	  
		I2c_Delay();
		Set_Scl_Bit(1);
		I2c_Delay();
		Set_Scl_Bit(0);
        I2c_Delay();
	}	 
} 	 
   
/**
  * @brief  模拟IIC读取一个字节
  * @param  None
  * @retval 接收到的数据
  */  
static u8 I2c_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	Set_Sda_Direct(0);
	for(i = 0; i < 8; i++ ) {
		Set_Scl_Bit(0);
		I2c_Delay();
		Set_Scl_Bit(1);
		receive <<= 1;
		if(s_pGpioSdaPort->IDR & s_usGpioSdaPin)
			receive++;   
		I2c_Delay();
	}
	if(ack)
		I2c_Ack(); 
	else
		I2c_NAck();
	
	return receive;
}
/**
  * @brief  模拟IIC根据地址读取多个字节
  * @param  None
  * @retval 非零:成功 0:失败
  */  
u8 I2cReadBytes(u8 SlaveAddress, u8 reg, u8 length, u8 *data)
{
    if (s_usI2sSoftwareInitFlg == 1)
    {
        u8 count = 0;
        
        I2c_Start();
        I2c_Send_Byte(SlaveAddress);	
        if(!I2c_Wait_Ack())
            return 0;
        I2c_Send_Byte(reg);		
        if(!I2c_Wait_Ack())
            return 0;	  
        I2c_Start();
        I2c_Send_Byte(SlaveAddress + 1);  
        if(!I2c_Wait_Ack())
            return 0;
        
        for(count = 0; count < length; count++) {
            if(count != length-1)
                data[count] = I2c_Read_Byte(1); 
            else
                data[count]=I2c_Read_Byte(0);	
        }
        I2c_Stop();
        
        return count;
    }

    return 0;
}
/**
  * @brief  模拟IIC根据地址写入多个字节
  * @param  None
  * @retval 1:成功 0:失败
  */  
u8 I2cWriteBytes(u8 SlaveAddress, u8 reg, u8 length, u8* data)
{
    if (s_usI2sSoftwareInitFlg == 1)
    {
        u8 count = 0;
        
        I2c_Start();
        I2c_Send_Byte(SlaveAddress);	  
        if(!I2c_Wait_Ack())
            return 0;
        I2c_Send_Byte(reg); 
        if(!I2c_Wait_Ack())
            return 0;	  
        for(count = 0; count < length; count++) {
            I2c_Send_Byte(data[count]); 
            I2c_Wait_Ack(); 
        }
        I2c_Stop();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        I2c_Delay();
        return 1;
    }
    
    return 0;
}
/**
  * @brief  硬件IIC配置初始化
  * @param  i2c_id:i2c的编号
  * @param  i2c_remap:
            -0:无重映射
            -1:重映射
  * @retval 1:成功 0:失败
  */ 
void I2CConfig(const u8 i2c_id, const u8 i2c_remap, const u16 slave_addr)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
	I2C_InitTypeDef		I2C_InitStructure;
	u8 i2c_id_remap = (i2c_id << 4) | i2c_remap;
    s_usSlaveAddress = slave_addr;
    
    switch (i2c_id_remap)
    {
        case 0x10:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            /*!< I2C configuration */
            I2C_DeInit(I2C1);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C1, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C1;
            I2C_Cmd(I2C1, ENABLE);
        }
            break;
        case 0x11:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
            GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            /*!< I2C configuration */
            I2C_DeInit(I2C1);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C1, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C1;
            I2C_Cmd(I2C1, ENABLE);
        }     
            break;
        case 0x20:
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
            
            /*!< PIN config */	
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
            
            /*!< I2C configuration */
            I2C_DeInit(I2C2);
            
            I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
            I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
            I2C_InitStructure.I2C_OwnAddress1 = slave_addr;
            I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
            I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
            I2C_InitStructure.I2C_ClockSpeed = 400000;		//<= 400KHz
            I2C_Init(I2C2, &I2C_InitStructure);
            
            s_pHardwareI2c = I2C2;
            I2C_Cmd(I2C2, ENABLE);
        }  
            break;
        default:
            break;
    }
}
/**
  * @brief  硬件IIC发送数据
  * @param  addr:寄存器的地址
  * @param  data:待发送的数据
  * @retval 1:成功 0:失败
  */ 
u8 HardwareI2cSendData(u8 addr, u8 data)
{
	u8 timeout = 0xFF;
	
    if(0 == s_pHardwareI2c)
    {
        return 0;
    }
    
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}

	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, addr);							///<RREGISTER ADDRESS
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, data);							///<DATA
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0;
		}
	}
	I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);							///<STOP
	
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    I2c_Delay();
    
	return 1;
}
/**
  * @brief  硬件IIC读取数据
  * @param  addr:寄存器的地址
  * @retval 非0:接收到的数据 0:失败
  */ 
u8 HardwareI2cReadData(u8 addr)
{
	u8 data = 0;
	u8 timeout = 0xFF;
	
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Cmd(s_pHardwareI2c, ENABLE);
	I2C_SendData(s_pHardwareI2c, addr); 							///<REGISTER ADDRESS	
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {			///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	timeout = 0xFF;
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Receiver); 		///<AD+R
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {		///<ACK
		if(!(--timeout))
        {
			return 0x0;
		}
	}					
	I2C_AcknowledgeConfig(s_pHardwareI2c, DISABLE);						///<NACK
	I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);							///<STOP
	while(!(I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_BYTE_RECEIVED)))
    {		
		if(!(--timeout))
        {
			return 0x0;
		}
	}
	data = I2C_ReceiveData(s_pHardwareI2c); 							///<DATA
	I2C_AcknowledgeConfig(s_pHardwareI2c, ENABLE);
	
	return data;
}
/**
  * @brief  硬件IIC读取多个数据
  * @param  register_addr:寄存器的地址
  * @param  data_out:接收到的数据地址
  * @param  length:待接收的数据长度
  * @retval 1:成功 0:失败
  */ 
u8 HardwareI2cReadDatas(u8 register_addr, u8 *data_out, u8 length)
{
	u16 timeout = 0xF000, i = 14, j = 0;
    
	while(I2C_GetFlagStatus(s_pHardwareI2c, I2C_FLAG_BUSY))
    {
		if(!(--timeout))
        {
			return 0;
		}
	}
		
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	
	while (!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_SB)) 
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}

	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Transmitter);	///<AD+W
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {	///<ACK
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_SendData(s_pHardwareI2c, register_addr); 					///<REGISTER ADDRESS	
	while ((!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_BTF)))
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_GenerateSTART(s_pHardwareI2c, ENABLE);							///<START
	while (!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_SB)) 
    {
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	I2C_Send7bitAddress(s_pHardwareI2c, s_usSlaveAddress, I2C_Direction_Receiver); 		///<AD+R
	while(!I2C_CheckEvent(s_pHardwareI2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {		///<ACK
		if(!(--timeout)) 
        {
			return 0;
		}
	}
	while(length)
    {

		if(i == 1)
        {
			I2C_AcknowledgeConfig(s_pHardwareI2c, DISABLE);
			I2C_GenerateSTOP(s_pHardwareI2c, ENABLE);					///<STOP
		}
		while((!I2C_GetFlagStatus(s_pHardwareI2c,I2C_FLAG_BTF)))
        {		///<ACK
			if(!(--timeout)) 
            {
				return 0;
			}
		}
		*(data_out+j) = I2C_ReceiveData(s_pHardwareI2c); 				///<DATA
        j++;
		i--;
	}

	I2C_AcknowledgeConfig(s_pHardwareI2c, ENABLE);

	return 1;
}
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

