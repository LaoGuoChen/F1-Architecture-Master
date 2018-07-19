/**
  ******************************************************************************
  * @file    stm32f10x_adc_config.c
  * @author  êÌÖÇÐÛ  
  * @version V1.0
  * @date    2018.6.21
  * @brief   ²âÊÔÏß³Ì
  ******************************************************************************
  */

#include "task_test.h"
#include  "FreeRTOS.h"
#include  "task.h"
#include  "app_hal_init.h"

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SPI_FLASH_WriteEnable(void)
{
    u8 spi_send_data = 0x06;
    
    g_stSpi_Flash_Dev.spi_set_cs(0);

    /* Send "Write Enable" instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);
}
void SPI_FLASH_WaitForWriteEnd(void)
{
    u8 FLASH_Status = 0;
    u8 spi_send_data = 0x05;
    u16 timeout = 0xD000;
    
    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);

    /* Send "Read Status Register" instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    spi_send_data = 0xFF;
    /* Loop as long as the memory is busy with a write cycle */
    do
    {
        /* Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        FLASH_Status = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);	 
    }
    while (((FLASH_Status & 0x01) == SET) && (--timeout)); /* Write in progress */

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);
}
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    u8 spi_send_data = 0x02;
    
    /* Enable the write access to the FLASH */
    SPI_FLASH_WriteEnable();

    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);
    /* Send "Write to Memory " instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send WriteAddr high nibble address byte to write to */
    spi_send_data = (WriteAddr & 0xFF0000) >> 16;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send WriteAddr medium nibble address byte to write to */
    spi_send_data = (WriteAddr & 0xFF00) >> 8;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send WriteAddr low nibble address byte to write to */
    spi_send_data = WriteAddr & 0xFF;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    if(NumByteToWrite > 256)
    {
        NumByteToWrite = 256;
    }

    /* while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /* Send the current byte */
        spi_send_data = *pBuffer;
        g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
        /* Point on the next byte to be written */
        pBuffer++;
    }

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);

    /* Wait the end of Flash writing */
    SPI_FLASH_WaitForWriteEnd();
}
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % 256;
    count = 256 - Addr;
    NumOfPage =  NumByteToWrite / 256;
    NumOfSingle = NumByteToWrite % 256;

    if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, 256);
                WriteAddr +=  256;
                pBuffer += 256;
            }

            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
            if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
            {
                temp = NumOfSingle - count;

                SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;

                SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / 256;
            NumOfSingle = NumByteToWrite % 256;

            SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, 256);
                WriteAddr +=  256;
                pBuffer += 256;
            }

            if (NumOfSingle != 0)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
    u8 spi_send_data = 0x03;
    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);

    /* Send "Read from Memory " instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send ReadAddr high nibble address byte to read from */
    spi_send_data = (ReadAddr & 0xFF0000) >> 16;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send ReadAddr medium nibble address byte to read from */
    spi_send_data = (ReadAddr& 0xFF00) >> 8;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send ReadAddr low nibble address byte to read from */
    spi_send_data = ReadAddr & 0xFF;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    
    spi_send_data = 0xFF;
    while (NumByteToRead--) /* while there is data to be read */
    {
        /* Read a byte from the FLASH */
        *pBuffer = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
        /* Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);
}
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
    u8 spi_send_data = 0x06;
    
    /* Send write enable instruction */
    g_stSpi_Flash_Dev.spi_set_cs(0);
    /* Send "Write Enable" instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);
    
    SPI_FLASH_WaitForWriteEnd();
    /* Sector Erase */
    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);
    /* Send Sector Erase instruction */
    spi_send_data = 0x20;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send SectorAddr high nibble address byte */
    spi_send_data = (SectorAddr & 0xFF0000) >> 16;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send SectorAddr medium nibble address byte */
    spi_send_data = (SectorAddr & 0xFF00) >> 8;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Send SectorAddr low nibble address byte */
    spi_send_data = SectorAddr & 0xFF;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);
    /* Wait the end of Flash writing */
    SPI_FLASH_WaitForWriteEnd();
}
u32 SPI_FLASH_ReadDeviceID(void)
{
    u32 Temp = 0;
    u8  spi_send_data = 0x06;
    
    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);

    /* Send "RDID " instruction */
    spi_send_data = 0xAB;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    spi_send_data = 0xFF;
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Read a byte from the FLASH */
    Temp = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);

    return Temp;
}
u32 SPI_FLASH_ReadID(void)
{
    u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
    u8  spi_send_data = 0x9F;

    /* Select the FLASH: Chip Select low */
    g_stSpi_Flash_Dev.spi_set_cs(0);

    /* Send "RDID " instruction */
    g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);
    /* Read a byte from the FLASH */
    spi_send_data = 0xFF;
    Temp0 = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Read a byte from the FLASH */
    Temp1 = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Read a byte from the FLASH */
    Temp2 = g_stSpi_Flash_Dev.spi_send(g_stSpi_Flash_Dev.spi_id, &spi_send_data);

    /* Deselect the FLASH: Chip Select high */
    g_stSpi_Flash_Dev.spi_set_cs(1);

    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

    return Temp;
}
/**
  * @brief  ²âÊÔÏß³Ì
  * @param  None
  * @retval None
  */
u32 spi_send_tmp = 0xC000c100;
u32 SPI_FLASH_DeviceID = 0;
u32 SPI_FLASH_FlashID = 0;

void vTestTask(void * pvParameters )
{    
    SPI_FLASH_DeviceID = SPI_FLASH_ReadDeviceID();//Get SPI Flash Device ID 
	vTaskDelay( 1 / portTICK_RATE_MS );	
	SPI_FLASH_FlashID = SPI_FLASH_ReadID();// Get SPI Flash ID 
    if (SPI_FLASH_FlashID == 0xEF4018)	 //W25Q128 
    {
        vTaskDelay( 1 / portTICK_RATE_MS );	
    }
    
    SPI_FLASH_SectorErase(0);
    SPI_FLASH_BufferWrite((u8 *)&spi_send_tmp, 0, 4);
    spi_send_tmp = 0;
    SPI_FLASH_BufferRead((u8 *)&spi_send_tmp, 0, 4);    
    
    while(1)
    {
        /* Select the FLASH: Chip Select low */
        if (spi_send_tmp == 0xC000c100)
        {
            vTaskDelay( 10 / portTICK_RATE_MS );
        }
        vTaskDelay( 10 / portTICK_RATE_MS );
    }
}
  
/************************* (C) COPYRIGHT 2018 HWJ *********END OF FILE*********/

