/*
 * I2C_OnBoard.h
 *
 *  Created on: Apr 27, 2015
 *      Author: davide
 */

#ifndef I2C_ONBOARD_H_
#define I2C_ONBOARD_H_

#include "stm32f4xx_hal_def.h"

HAL_StatusTypeDef HAL_I2C_Master_Transmit_OnBoard(I2C_HandleTypeDef *hi2cMaster, I2C_HandleTypeDef *hi2cSlave, uint16_t DevAddress, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_OnBoard(I2C_HandleTypeDef *hi2cMaster, I2C_HandleTypeDef *hi2cSlave, uint16_t DevAddress, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

#endif /* I2C_ONBOARD_H_ */
