/*
 * config.h
 *
 *  Created on: May 6, 2015
 *      Author: davide
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */

/* Definition for UsartMaster clock resources */
#define UsartMaster                           	USART6
#define UsartMaster_CLK_ENABLE()              	__HAL_RCC_USART6_CLK_ENABLE();
#define UsartMaster_RX_CLK_ENABLE()      		__HAL_RCC_GPIOC_CLK_ENABLE()
#define UsartMaster_TX_CLK_ENABLE()      		__HAL_RCC_GPIOC_CLK_ENABLE()

#define UsartMaster_FORCE_RESET()            	__HAL_RCC_USART6_FORCE_RESET()
#define UsartMaster_RELEASE_RESET()          	__HAL_RCC_USART6_RELEASE_RESET()

/* Definition for UsartMaster Pins */
#define UsartMaster_TX_PIN                    	GPIO_PIN_6
#define UsartMaster_TX_GPIO_PORT              	GPIOC
#define UsartMaster_TX_AF                     	GPIO_AF8_USART6
#define UsartMaster_RX_PIN                    	GPIO_PIN_7
#define UsartMaster_RX_GPIO_PORT              	GPIOC
#define UsartMaster_RX_AF                     	GPIO_AF8_USART6

/* Definition for UsartMaster's NVIC */
#define UsartMaster_IRQn                      USART6_IRQn
#define UsartMaster_IRQHandler                USART6_IRQHandler

/* Definition for UsartSlave clock resources */
#define UsartSlave                           	USART3
#define UsartSlave_CLK_ENABLE()              	__HAL_RCC_USART3_CLK_ENABLE();
#define UsartSlave_RX_CLK_ENABLE()      		__HAL_RCC_GPIOB_CLK_ENABLE()
#define UsartSlave_TX_CLK_ENABLE()      		__HAL_RCC_GPIOB_CLK_ENABLE()

#define UsartSlave_FORCE_RESET()            	__HAL_RCC_USART3_FORCE_RESET()
#define UsartSlave_RELEASE_RESET()          	__HAL_RCC_USART3_RELEASE_RESET()

/* Definition for UsartMaster Pins */
#define UsartSlave_TX_PIN                    	GPIO_PIN_10
#define UsartSlave_TX_GPIO_PORT              	GPIOB
#define UsartSlave_TX_AF                     	GPIO_AF7_USART3
#define UsartSlave_RX_PIN                    	GPIO_PIN_11
#define UsartSlave_RX_GPIO_PORT              	GPIOB
#define UsartSlave_RX_AF                     	GPIO_AF7_USART3

/* Definition for UsartMaster's NVIC */
#define UsartSlave_IRQn                      USART3_IRQn
#define UsartSlave_IRQHandler                USART3_IRQHandler

/* Size of Transmission buffer */
#define TXBUFFERSIZE                      1
/* Size of Reception buffer */
#define RXBUFFERSIZE                      1

#endif /* CONFIG_H_ */
