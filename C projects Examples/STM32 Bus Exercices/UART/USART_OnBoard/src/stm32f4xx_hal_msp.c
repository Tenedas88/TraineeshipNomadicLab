/**
  ******************************************************************************
  * @file    UART/UART_TwoBoards_ComIT/Src/stm32f4xx_hal_msp.c
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

/** @defgroup UART_TwoBoards_ComIT
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
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  if(huart->Instance == UsartMaster){
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable UsartMaster GPIO TX/RX clock */
  UsartMaster_TX_CLK_ENABLE();
  UsartMaster_RX_CLK_ENABLE();
  UsartMaster_CLK_ENABLE();


  /*##-2- Configure peripheral Master GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = UsartMaster_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = UsartMaster_TX_AF;

  HAL_GPIO_Init(UsartMaster_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = UsartMaster_RX_PIN;
  GPIO_InitStruct.Alternate = UsartMaster_RX_AF;

  HAL_GPIO_Init(UsartMaster_RX_GPIO_PORT, &GPIO_InitStruct);

  /*##-4- Configure the NVIC for UART ########################################*/
  /* NVIC for USART2 */
  HAL_NVIC_SetPriority(UsartMaster_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(UsartMaster_IRQn);
  }
  else{
  /* Enable UsartSlave GPIO TX/RX clock */
  UsartSlave_TX_CLK_ENABLE();
  UsartSlave_RX_CLK_ENABLE();
  /* Enable USART2 clock */
  UsartSlave_CLK_ENABLE();

  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = UsartSlave_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = UsartSlave_TX_AF;
  
  HAL_GPIO_Init(UsartSlave_TX_GPIO_PORT, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = UsartSlave_RX_PIN;
  GPIO_InitStruct.Alternate = UsartSlave_RX_AF;
    
  HAL_GPIO_Init(UsartSlave_RX_GPIO_PORT, &GPIO_InitStruct);

  /* NVIC for USART1 */
  HAL_NVIC_SetPriority(UsartSlave_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(UsartSlave_IRQn);
  }
}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if(huart->Instance == UsartMaster){
  /*##-1- Reset peripherals ##################################################*/
  UsartMaster_FORCE_RESET();
  UsartMaster_RELEASE_RESET();


  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(UsartMaster_TX_GPIO_PORT, UsartMaster_TX_PIN);

  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(UsartMaster_RX_GPIO_PORT, UsartMaster_RX_PIN);

  
  /*##-3- Disable the NVIC for UART ##########################################*/
  HAL_NVIC_DisableIRQ(UsartMaster_IRQn);
  }
  else{
  UsartSlave_FORCE_RESET();
  UsartSlave_RELEASE_RESET();

  HAL_GPIO_DeInit(UsartSlave_TX_GPIO_PORT, UsartSlave_TX_PIN);
  HAL_GPIO_DeInit(UsartSlave_RX_GPIO_PORT, UsartSlave_RX_PIN);

  HAL_NVIC_DisableIRQ(UsartSlave_IRQn);
  }
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
