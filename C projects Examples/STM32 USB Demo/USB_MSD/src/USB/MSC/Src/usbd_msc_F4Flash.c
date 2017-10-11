/**
  ******************************************************************************
  * @file    usbd_msc_storage_template.c
  * @author  MCD Application Team
  * @version V2.4.0
  * @date    28-February-2015
  * @brief   Memory management layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include <usbd_msc_F4Flash.h>
#include "stm32f4_discovery.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Mass Storage Memory Layout */
#define MSC_MemorySize  1024*100
#define MSC_BlockSize   512
#define MSC_BlockCount  (MSC_MemorySize / MSC_BlockSize)

__attribute__((__section__(".user_data"))) volatile const uint8_t FLASH_Memory[MSC_MemorySize];

#define MSC_MAX_PACKET  64
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* -----------MSC FLASH MEMORY---------- */

/* -----------MSC RAM MEMORY---------- */
uint8_t RAM_Memory[MSC_MemorySize];


/* Private function prototypes -----------------------------------------------*/


/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  MSC_BlockCount
#define STORAGE_BLK_SIZ                  MSC_BlockSize

int8_t STORAGE_Init (uint8_t lun);

int8_t STORAGE_DeInit (void);

int8_t STORAGE_GetCapacity (uint8_t lun, 
                           uint32_t *block_num, 
                           uint16_t *block_size);

int8_t  STORAGE_IsReady (uint8_t lun);

int8_t  STORAGE_IsWriteProtected (uint8_t lun);

int8_t STORAGE_Read (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_Write (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);

int8_t STORAGE_GetMaxLun (void);

/* USB Mass storage Standard Inquiry Data */
int8_t  STORAGE_Inquirydata[] = {//36
  
  /* LUN 0 */
  0x00,			 /* Direct Access Device */
  0x80,			/* RMB = 1: Removable Medium */
  0x02,			/* Version: 00-> No conformance claim to standard */
  0x01,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x80,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
}; 

USBD_StorageTypeDef USBD_MSC_F4Memory_fops =
{
  STORAGE_Init,
  STORAGE_DeInit,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata,
  
};
/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Init (uint8_t lun)
{


	/**
	 * Copai della memoria Flash sulla RAM
	 */

	uint32_t n;

	/**
	 * Inizializzazione RAM
	 */

	for (n = 0; n < MSC_MemorySize; n++) {
		    RAM_Memory[n] = 0;
		  }

	HAL_FLASH_Unlock();

	/**
	 * Copia dei valori in Flash sulla RAM
	 */
    for (n = 0; n < MSC_MemorySize; n++) {
    	RAM_Memory[n] = FLASH_Memory[n];
	  }


	HAL_FLASH_Lock();

    //BSP_LED_Toggle(LED3);
	BSP_LED_Toggle(LED4);
	BSP_LED_Toggle(LED5);
	BSP_LED_Toggle(LED6);



  return 0;
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_DeInit (void)
{
	uint32_t n;


	/**
	 * Copai della RAM sulla Flash
	 */
	HAL_FLASH_Unlock();

	FLASH_Erase_Sector(FLASH_SECTOR_6,VOLTAGE_RANGE_3);


	  for (n = 0; n < MSC_MemorySize; n++) {
		  HAL_FLASH_Program(TYPEPROGRAM_BYTE, (uint8_t*) &FLASH_Memory[n], RAM_Memory[n]);	//Copy RAM to FLASH
	  }
	  HAL_FLASH_Lock();

		BSP_LED_Toggle(LED3);
		//BSP_LED_Toggle(LED4);
		//BSP_LED_Toggle(LED5);
		//BSP_LED_Toggle(LED6);

  return 0;
}


/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetCapacity (uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (0);
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsReady (uint8_t lun)
{
 	return (0);

}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsWriteProtected (uint8_t lun)
{
  return  0;
}

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Read (uint8_t lun, 
                 uint8_t *buf, 
                 uint32_t blk_addr,                       
                 uint16_t blk_len)
{
	/**
	 * Calcolo dell' effettivo inidirizzo da cui leggere:
	 * l'indirizzo logico blk_addr viene moltiplicato per la grandezza effettiva del blocco.
	 * Analogamente si calcola la lunghezza effettiva del trasferimento.
	 */
		uint32_t offset;
		uint32_t length;

		offset = blk_addr * MSC_BlockSize;
		length = blk_len * MSC_BlockSize;

	for(uint32_t i=0; i<length; i++ ){
		buf[i] = RAM_Memory[offset + i];
	}
	BSP_LED_Toggle(LED4);
  return 0;
}
/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Write (uint8_t lun, 
                  uint8_t *buf, 
                  uint32_t blk_addr,
                  uint16_t blk_len)
{

	/**
		 * Calcolo dell' effettivo inidirizzo a cui scrivere:
		 * l'indirizzo logico blk_addr viene moltiplicato per la grandezza effettiva del blocco.
		 * Analogamente si calcola la lunghezza effettiva del trasferimento.
		 */
		uint32_t offset;
		uint32_t length;

		offset = blk_addr * MSC_BlockSize;
		length = blk_len * MSC_BlockSize;

		for(uint32_t i=0; i<length; i++){
			RAM_Memory[offset + i] = buf[i];
		}

		BSP_LED_Toggle(LED5);

		return 0;

	//HAL_FLASH_Program(FLASH_PROC_PROGRAM, blk_addr,  *buf);
}
/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the STORAGE card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetMaxLun (void)
{
  return (STORAGE_LUN_NBR - 1);
  BSP_LED_Toggle(LED6);
}

/* Private functions ---------------------------------------------------------*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

