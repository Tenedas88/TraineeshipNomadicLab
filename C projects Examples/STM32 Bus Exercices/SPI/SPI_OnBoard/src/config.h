/*
 * config.h
 *
 *  Created on: May 6, 2015
 *      Author: davide
 */

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "SPI_OnBoard.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define SpiMaster								SPI1
#define SpiMaster_CLK_ENABLE()                	__HAL_RCC_SPI1_CLK_ENABLE()
#define SpiMaster_MISO_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define SpiMaster_MOSI_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define SpiMaster_SCK_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()

#define SpiMaster_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SpiMaster_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()


/**
 * Definition for SPI MASTER PINS
 */

#define SpiMaster_MISO_PIN                    GPIO_PIN_6
#define SpiMaster_MISO_GPIO_PORT              GPIOA
#define SpiMaster_MISO_AF                     GPIO_AF5_SPI1

#define SpiMaster_MOSI_PIN                    GPIO_PIN_7
#define SpiMaster_MOSI_GPIO_PORT              GPIOA
#define SpiMaster_MOSI_AF                     GPIO_AF5_SPI1

#define SpiMaster_SCK_PIN                    GPIO_PIN_5
#define SpiMaster_SCK_GPIO_PORT              GPIOA
#define SpiMaster_SCK_AF                     GPIO_AF5_SPI1


#define SpiSlave								SPI2
#define SpiSlave_CLK_ENABLE()                	__HAL_RCC_SPI2_CLK_ENABLE()
#define SpiSlave_MISO_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define SpiSlave_MOSI_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define SpiSlave_SCK_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()

#define SpiSlave_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SpiSlave_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/**
 * Definition for SPI SLAVE PINS
 */

#define SpiSlave_MISO_PIN                    GPIO_PIN_14
#define SpiSlave_MISO_GPIO_PORT              GPIOB
#define SpiSlave_MISO_AF                     GPIO_AF5_SPI2

#define SpiSlave_MOSI_PIN                    GPIO_PIN_15
#define SpiSlave_MOSI_GPIO_PORT              GPIOB
#define SpiSlave_MOSI_AF                     GPIO_AF5_SPI2

#define SpiSlave_SCK_PIN                    GPIO_PIN_13
#define SpiSlave_SCK_GPIO_PORT              GPIOB
#define SpiSlave_SCK_AF                     GPIO_AF5_SPI2

#define RXBUFFERSIZE						1
#define TXBUFFERSIZE						1




#endif /* CONFIG_H_ */
