/*
 * config.h
 *
 *  Created on: 02/apr/2015
 *      Author: mariobarbareschi
 */


#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

#ifndef CONFIG_H_
#define CONFIG_H_

#define SPIS                             SPI2
#define SPIS_CLK_ENABLE()                __SPI2_CLK_ENABLE()
#define SPIS_SCK_GPIO_CLK_ENABLE()       __GPIOB_CLK_ENABLE()
#define SPIS_NSS_GPIO_CLK_ENABLE()		 __GPIOB_CLK_ENABLE()
#define SPIS_MISO_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define SPIS_MOSI_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()

#define SPIM                             SPI1
#define SPIM_CLK_ENABLE()                __SPI1_CLK_ENABLE()
#define SPIM_SCK_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()
#define SPIM_NSS_GPIO_CLK_ENABLE()		 __GPIOA_CLK_ENABLE()
#define SPIM_MISO_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define SPIM_MOSI_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define SPIM_FORCE_RESET()               __SPI1_FORCE_RESET()
#define SPIM_RELEASE_RESET()             __SPI1_RELEASE_RESET()

#define SPIS_FORCE_RESET()               __SPI2_FORCE_RESET()
#define SPIS_RELEASE_RESET()             __SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */

#define SPIS_SCK_PIN                     GPIO_PIN_13
#define SPIS_SCK_GPIO_PORT               GPIOB
#define SPIS_SCK_AF  					 GPIO_AF5_SPI2

#define SPIM_SCK_PIN                     GPIO_PIN_5
#define SPIM_SCK_GPIO_PORT               GPIOA
#define SPIM_SCK_AF  					 GPIO_AF5_SPI1


#define SPIS_MISO_PIN                    GPIO_PIN_14
#define SPIS_MISO_GPIO_PORT              GPIOB
#define SPIS_MISO_AF                     GPIO_AF5_SPI2

#define SPIM_MISO_PIN                    GPIO_PIN_6
#define SPIM_MISO_GPIO_PORT              GPIOA
#define SPIM_MISO_AF                     GPIO_AF5_SPI1

#define SPIS_MOSI_PIN                    GPIO_PIN_15
#define SPIS_MOSI_GPIO_PORT              GPIOB
#define SPIS_MOSI_AF                     GPIO_AF5_SPI2

#define SPIM_MOSI_PIN                    GPIO_PIN_7
#define SPIM_MOSI_GPIO_PORT              GPIOA
#define SPIM_MOSI_AF                     GPIO_AF5_SPI1

/*definitions for NVIC setting*/
#define SPIM_IRQn                      SPI1_IRQn
#define SPIM_IRQHandler                SPI1_IRQHandler

#define SPIS_IRQn                      SPI2_IRQn
#define SPIS_IRQHandler                SPI2_IRQHandler



#define RXBUFFERSIZE 1
#define TXBUFFERSIZE 1

#endif /* CONFIG_H_ */
