/*
 * config.h
 *
 *  Created on: May 4, 2015
 *      Author: davide
 */

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define SpiMaster								SPI1
#define SpiMaster_CLK_ENABLE()                	__HAL_RCC_SPI1_CLK_ENABLE()
#define SpiMaster_MISO_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define SpiMaster_MOSI_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define SpiMaster_SCK_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
//#define SpiMaster_NSS_CLK_ENABLE()				__GPIOA_CLK_ENABLE()

#define SpiMaster_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SpiMaster_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()


/**
 * Definition for SPI PINS
 **/

#define SpiMaster_MISO_PIN                    GPIO_PIN_6
#define SpiMaster_MISO_GPIO_PORT              GPIOA
#define SpiMaster_MISO_AF                     GPIO_AF5_SPI1

#define SpiMaster_MOSI_PIN                    GPIO_PIN_7
#define SpiMaster_MOSI_GPIO_PORT              GPIOA
#define SpiMaster_MOSI_AF                     GPIO_AF5_SPI1

#define SpiMaster_SCK_PIN                    GPIO_PIN_5
#define SpiMaster_SCK_GPIO_PORT              GPIOA
#define SpiMaster_SCK_AF                     GPIO_AF5_SPI1

//#define SpiMaster_NSS_PIN                    GPIO_PIN_4
//#define SpiMaster_NSS_GPIO_PORT              GPIOA
//#define SpiMaster_NSS_AF                     GPIO_AF5_SPI1

#define RXBUFFERSIZE						1
#define TXBUFFERSIZE						1

#endif /* CONFIG_H_ */
