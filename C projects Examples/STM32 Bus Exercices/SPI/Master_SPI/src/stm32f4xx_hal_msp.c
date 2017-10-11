/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComPolling/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    13-March-2015
  * @brief   HAL MSP module.    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @defgroup SPI_FullDuplex_ComPolling
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief SPI MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  SpiMaster_SCK_CLK_ENABLE();
  SpiMaster_MISO_CLK_ENABLE();
  SpiMaster_MOSI_CLK_ENABLE();
  //SpiMaster_NSS_CLK_ENABLE();
  /* Enable SPI clock */
  SpiMaster_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* SPI SCK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = SpiMaster_SCK_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = SpiMaster_SCK_AF;
  
  HAL_GPIO_Init(SpiMaster_SCK_GPIO_PORT, &GPIO_InitStruct);
    
  /* SPI MISO GPIO pin configuration  */
  GPIO_InitStruct.Pin = SpiMaster_MISO_PIN;
  GPIO_InitStruct.Alternate = SpiMaster_MISO_AF;
  
  HAL_GPIO_Init(SpiMaster_MISO_GPIO_PORT, &GPIO_InitStruct);
  
  /* SPI MOSI GPIO pin configuration  */
  GPIO_InitStruct.Pin = SpiMaster_MOSI_PIN;
  GPIO_InitStruct.Alternate = SpiMaster_MOSI_AF;
    
  HAL_GPIO_Init(SpiMaster_MOSI_GPIO_PORT, &GPIO_InitStruct);

  /* SPI NSS GPIO pin configuration  */
//  GPIO_InitStruct.Pin = SpiMaster_NSS_PIN;
//  GPIO_InitStruct.Alternate = SpiMaster_NSS_AF;
//
//  HAL_GPIO_Init(SpiMaster_NSS_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief SPI MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to its default state
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /*##-1- Reset peripherals ##################################################*/
  SpiMaster_FORCE_RESET();
  SpiMaster_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* Configure SPI SCK as alternate function  */
  HAL_GPIO_DeInit(SpiMaster_SCK_GPIO_PORT, SpiMaster_SCK_PIN);
  /* Configure SPI MISO as alternate function  */
  HAL_GPIO_DeInit(SpiMaster_MISO_GPIO_PORT, SpiMaster_MISO_PIN);
  /* Configure SPI MOSI as alternate function  */
  HAL_GPIO_DeInit(SpiMaster_MOSI_GPIO_PORT, SpiMaster_MOSI_PIN);
  /* Configure SPI MOSI as alternate function  */
  //HAL_GPIO_DeInit(SpiMaster_NSS_GPIO_PORT, SpiMaster_NSS_PIN);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
