/**
  ******************************************************************************
  * @file   stm32f10x_flash_config.c
  * @author  ������  
  * @version V1.0
  * @date    2018.6.13
  * @brief   flash����ģ��
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_flash_config.h"
#include "stm32f10x_flash.h"
#include "api_flash.h"

#include "FreeRTOS.h"
#include "portable.h"


#define STM32_FLASH_BASE        0x08000000 	///<STM32 FLASH����ʼ��ַ
#define DUMMY_BYTE              0xFF
#define SPI_FLASH_CS_LOW()      Set_Spi_Flash_Cs(0)
#define SPI_FLASH_CS_HIGH()     Set_Spi_Flash_Cs(1)

#define EXPAND_WRAPPER( __NEXTLEVEL__, ...)  __NEXTLEVEL__( __VA_ARGS__ )
#define _GET_SPI(x)   SPI##x
#define GET_SPI(x)    EXPAND_WRAPPER(_GET_SPI, x)
/* Private functions ---------------------------------------------------------*/

#if STM32_FLASH_WRITE_EN	///<���ʹ����д   
/**
  * @brief  ��ȡָ����ַ�İ���(16λ����)
  * @param  faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * @retval ����ֵ:��Ӧ����
  */
static u16 Stm_Flash_Read_HalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
/**
  * @brief  ������д��
  * @param  WriteAddr:��ʼ��ַ
  * @param  pBuffer:����ָ��
  * @param  NumToWrite:����(16λ)��  
  * @retval None
  */ 
static void Stm_Flash_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;///<��ַ����2.
	}  
} 
/**
  * @brief  ��ȡҳ��С
  * @retval PageSize
  */
static u32 GetPageSize(void)
{
	u16 *pMemSize = (u16 *)0x1FFFF7E0;

	if(*pMemSize > 128) {
		return 2048;
	} else {
		return 1024;
	}
}
/**
  * @brief  ��ָ����ַ��ʼ����ָ�����ȵ�����
  * @param  ReadAddr:��ʼ��ַ
  * @param  pBuffer:����ָ��
  * @param  NumToWrite:����(16λ)��
  * @retval None
  */ 
void Stm_Flash_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = Stm_Flash_Read_HalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}
/**
  * @brief  ��ָ����ַ��ʼд��ָ�����ȵ�����
  * @param  WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
  * @param  pBuffer:����ָ��
  * @param  NumToWrite:����(16λ)�� (����Ҫд���16λ���ݵĸ���.) 
  * @retval None
  */ 		 
void Stm_flash_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)	
{
	u32 secpos;	   ///<������ַ
	u16 secoff;	   ///<������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; ///<������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   ///<ȥ��0X08000000��ĵ�ַ
    u16 *stm_flash_buff = pvPortMalloc(GetPageSize()/2);//�����2K�ֽ�
    u16 *pMemSize = (u16 *)0x1FFFF7E0;
    
	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * (*pMemSize))))
        return;///<�Ƿ���ַ
    
	FLASH_Unlock();						        ///<����
	offaddr = WriteAddr - STM32_FLASH_BASE;		///<ʵ��ƫ�Ƶ�ַ.
	secpos = offaddr / GetPageSize();			///<������ַ  0~127 for STM32F103RBT6
	secoff = (offaddr % GetPageSize())/2;		///<�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain = GetPageSize() / 2 - secoff;		///<����ʣ��ռ��С   
	if(NumToWrite <= secremain)
        secremain = NumToWrite;                 ///<�����ڸ�������Χ
    
	while(1) 
	{	
		Stm_Flash_Read(secpos * GetPageSize() + STM32_FLASH_BASE, stm_flash_buff, GetPageSize() / 2);///<������������������
		for (i = 0; i < secremain; i++)///<У������
		{
			if(stm_flash_buff[secoff+i]!=0XFFFF)
                break;///<��Ҫ����  	  
		}
		if (i < secremain)///<��Ҫ����
		{
			FLASH_ErasePage(secpos * GetPageSize() + STM32_FLASH_BASE);///<�����������
			for (i = 0; i < secremain; i++)///<����
			{
				stm_flash_buff[i + secoff] = pBuffer[i];	  
			}
			Stm_Flash_Write_NoCheck(secpos * GetPageSize() + STM32_FLASH_BASE, stm_flash_buff, GetPageSize()/2);///<д����������  
		}
        else 
        {
            Stm_Flash_Write_NoCheck(WriteAddr, pBuffer, secremain);///<д�Ѿ������˵�,ֱ��д������ʣ������. 
        }            
		if(NumToWrite==secremain)
        {
            break;///<д�������
        }
		else///<д��δ����
		{
			secpos++;				///<������ַ��1
			secoff = 0;				///<ƫ��λ��Ϊ0 	 
		   	pBuffer += secremain;  	///<ָ��ƫ��
			WriteAddr += secremain;	///<д��ַƫ��	   
		   	NumToWrite -= secremain;	///<�ֽ�(16λ)���ݼ�
			if (NumToWrite > (GetPageSize()/2))
            {
                secremain=GetPageSize()/2;///<��һ����������д����
            }
			else 
            {
                secremain=NumToWrite;///<��һ����������д����
            }
		}	 
	}
    vPortFree(stm_flash_buff);
	FLASH_Lock();///<����
}
#endif
/**
  * @brief  ͨ��spiд��һ���ֽ��������ⲿflash
  * @param  byte:д�������
  * @retval ����ֵ:spi����״̬
  */
static u8 Spi_Flash_Send_Byte(u8 byte)
{

    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(GET_SPI(FLASH_SPI_ID), SPI_I2S_FLAG_TXE) == RESET);

    /* Send byte through the SPI2 peripheral */
    SPI_I2S_SendData(GET_SPI(FLASH_SPI_ID), byte);

    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(GET_SPI(FLASH_SPI_ID), SPI_I2S_FLAG_RXNE) == RESET);

    /* Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(GET_SPI(FLASH_SPI_ID));
}
/**
  * @brief  flashд��ʹ��
  * @param  None
  * @retval None
  */
static void Spi_Flash_Write_Enable(void)
{
    /*!< Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_WRITE_ENABLE);

    /*!< Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();
}
/**
  * @brief  �ȴ�flashд�����
  * @param  None
  * @retval None
  */
static void Spi_Flash_Wait_For_Write_End(void)
{
    u8 FLASH_Status = 0;

    /*!< Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /*!< Send "Read Status Register" instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_READ_STATAUS_REG);

    /*!< Loop as long as the memory is busy with a write cycle */
    do
    {
        /*!< Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        FLASH_Status = Spi_Flash_Send_Byte(DUMMY_BYTE);	 
    }
    while ((FLASH_Status & FLASH_CHIP_WIP_FLAG) == SET); /*!< Write in progress */

    /*!< Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();
}
/**
  * @brief  ����flash������
  * @param  None
  * @retval None
  */
static void Spi_Flash_Page_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    /*!< Enable the write access to the FLASH */
    Spi_Flash_Write_Enable();

    /*!< Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();
    /*!< Send "Write to Memory " instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_PAGE_PROGRAM);
    /*!< Send WriteAddr high nibble address byte to write to */
    Spi_Flash_Send_Byte((WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    Spi_Flash_Send_Byte((WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    Spi_Flash_Send_Byte(WriteAddr & 0xFF);

    if(NumByteToWrite > FLASH_CHIP_PER_WRITE_PAGE_SIZE)
    {
        NumByteToWrite = FLASH_CHIP_PER_WRITE_PAGE_SIZE;
    }

    /*!< while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /*!< Send the current byte */
        Spi_Flash_Send_Byte(*pBuffer);
        /*!< Point on the next byte to be written */
        pBuffer++;
    }

    /* Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();

    /* Wait the end of Flash writing */
    Spi_Flash_Wait_For_Write_End();
}
/**
  * @brief  д���ݽ�flash
  * @param  pBuffer:д�����ݵĵ�ַ
  * @param  WriteAddr:д���flash��ַ
  * @param  NumByteToWrite:д�����ݵĳ���
  * @retval None
  */
void Spi_Flash_Buffer_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % FLASH_CHIP_PAGE_SIZE;
    count = FLASH_CHIP_PAGE_SIZE - Addr;
    NumOfPage =  NumByteToWrite / FLASH_CHIP_PAGE_SIZE;
    NumOfSingle = NumByteToWrite % FLASH_CHIP_PAGE_SIZE;

    if (Addr == 0) /*!< WriteAddr is SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < SPI_FLASH_PageSize */
        {
            Spi_Flash_Page_Write(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /*!< NumByteToWrite > SPI_FLASH_PageSize */
        {
            while (NumOfPage--)
            {
                Spi_Flash_Page_Write(pBuffer, WriteAddr, FLASH_CHIP_PAGE_SIZE);
                WriteAddr +=  FLASH_CHIP_PAGE_SIZE;
                pBuffer += FLASH_CHIP_PAGE_SIZE;
            }

            Spi_Flash_Page_Write(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /*!< WriteAddr is not SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < SPI_FLASH_PageSize */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
            {
            temp = NumOfSingle - count;

            Spi_Flash_Page_Write(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            Spi_Flash_Page_Write(pBuffer, WriteAddr, temp);
            }
            else
            {
                Spi_Flash_Page_Write(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /*!< NumByteToWrite > SPI_FLASH_PageSize */
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / FLASH_CHIP_PAGE_SIZE;
            NumOfSingle = NumByteToWrite % FLASH_CHIP_PAGE_SIZE;

            Spi_Flash_Page_Write(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                Spi_Flash_Page_Write(pBuffer, WriteAddr, FLASH_CHIP_PAGE_SIZE);
                WriteAddr +=  FLASH_CHIP_PAGE_SIZE;
                pBuffer += FLASH_CHIP_PAGE_SIZE;
            }

            if (NumOfSingle != 0)
            {
                Spi_Flash_Page_Write(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}
/**
  * @brief  ��flashָ����ַ��ȡ����
  * @param  pBuffer:��ȡ���ݺ��ŵĵ�ַ
  * @param  ReadAddr:��ȡ��flash��ַ
  * @param  NumByteToWrite:д�����ݵĳ���
  * @retval None
  */
void Spi_Flash_Buffer_Read(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
    /* Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /* Send "Read from Memory " instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_READ_DATA);

    /* Send ReadAddr high nibble address byte to read from */
    Spi_Flash_Send_Byte((ReadAddr & 0xFF0000) >> 16);
    /* Send ReadAddr medium nibble address byte to read from */
    Spi_Flash_Send_Byte((ReadAddr& 0xFF00) >> 8);
    /* Send ReadAddr low nibble address byte to read from */
    Spi_Flash_Send_Byte(ReadAddr & 0xFF);

    while (NumByteToRead--) /* while there is data to be read */
    {
        /* Read a byte from the FLASH */
        *pBuffer = Spi_Flash_Send_Byte(DUMMY_BYTE);
        /* Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /* Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();
}
/**
  * @brief  ����flash������
  * @param  SectorAddr:����ĵ�ַ
  * @retval None
  */
void Spi_Flash_Sector_Erase(u32 SectorAddr)
{
    /*!< Send write enable instruction */
    Spi_Flash_Write_Enable();
    Spi_Flash_Wait_For_Write_End();
    /*!< Sector Erase */
    /*!< Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_SECTOR_ERASE);
    /*!< Send SectorAddr high nibble address byte */
    Spi_Flash_Send_Byte((SectorAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    Spi_Flash_Send_Byte((SectorAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    Spi_Flash_Send_Byte(SectorAddr & 0xFF);
    /*!< Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();
    /*!< Wait the end of Flash writing */
    Spi_Flash_Wait_For_Write_End();
}
/**
  * @brief  flash�������ģʽ
  * @param  None
  * @retval None
  */
void Spi_Flash_Power_Down(void)   
{ 
    /*!< Select the FLASH: Chip Select low */
    SPI_FLASH_CS_LOW();

    /*!< Send "Power Down" instruction */
    Spi_Flash_Send_Byte(FLASH_CHIP_POWER_DOWN_ADDR);

    /*!< Deselect the FLASH: Chip Select high */
    SPI_FLASH_CS_HIGH();
}  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/
