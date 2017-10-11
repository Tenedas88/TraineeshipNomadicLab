/*
 * config.h
 *
 *  Created on: Apr 26, 2015
 *      Author: davide
 */

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "I2C_OnBoard.h"

#ifndef CONFIG_H_
#define CONFIG_H_


//Master I2C Interface

#define I2C_MasterAddress							0x12
#define I2C_MasterBus								I2C1
#define I2C_MasterBus_CLK_ENABLE()					__I2C1_CLK_ENABLE()
#define I2CM_SCL_GPIO_CLK_ENABLE()					__GPIOB_CLK_ENABLE()
#define I2CM_SDA_GPIO_CLK_ENABLE()					__GPIOB_CLK_ENABLE()
#define I2C_MasterBus_FORCE_RESET()					__I2C1_FORCE_RESET()
#define I2C_MasterBus_RELEASE_RESET()				__I2C1_RELEASE_RESET()

//Master I2C Pins

#define I2C_MasterBus_SCL_PIN						GPIO_PIN_6
#define I2C_MasterBus_SCL_PORT						GPIOB
#define I2C_MasterBus_SCL_AF						GPIO_AF4_I2C1

#define I2C_MasterBus_SDA_PIN						GPIO_PIN_9
#define I2C_MasterBus_SDA_PORT						GPIOB
#define I2C_MasterBus_SDA_AF						GPIO_AF4_I2C1

//Slave I2C Interface

#define I2C_SlaveAddress							0x14
#define I2C_SlaveBus								I2C3
#define I2C_SlaveBus_CLK_ENABLE()					__I2C3_CLK_ENABLE()
#define I2CS_SCL_GPIO_CLK_ENABLE()					__GPIOA_CLK_ENABLE()
#define I2CS_SDA_GPIO_CLK_ENABLE()					__GPIOC_CLK_ENABLE()
#define I2C_SlaveBus_FORCE_RESET()					__I2C3_FORCE_RESET()
#define I2C_SlaveBus_RELEASE_RESET()				__I2C3_RELEASE_RESET()

//Slave I2C Pins
#define I2C_SlaveBus_SCL_PIN						GPIO_PIN_8
#define I2C_SlaveBus_SCL_PORT						GPIOA
#define I2C_SlaveBus_SCL_AF							GPIO_AF4_I2C3

#define I2C_SlaveBus_SDA_PIN						GPIO_PIN_9
#define I2C_SlaveBus_SDA_PORT						GPIOC
#define I2C_SlaveBus_SDA_AF							GPIO_AF4_I2C3

//I2C Resources

#define RXBUFFERSIZE								1
#define TXBUFFERSIZE								1


#endif /* CONFIG_H_ */
