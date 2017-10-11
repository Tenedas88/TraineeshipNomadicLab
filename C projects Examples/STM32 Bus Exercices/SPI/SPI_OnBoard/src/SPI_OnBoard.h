/*
 * SPI_OnBoard.h
 *
 *  Created on: May 6, 2015
 *      Author: davide
 */

#ifndef SPI_ONBOARD_H_
#define SPI_ONBOARD_H_

#include "stm32f4xx_hal_def.h"

HAL_StatusTypeDef HAL_SPI_TransmitReceive_OnBoard(SPI_HandleTypeDef *hspiMaster, SPI_HandleTypeDef *hspiSlave, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

#endif /* SPI_ONBOARD_H_ */
