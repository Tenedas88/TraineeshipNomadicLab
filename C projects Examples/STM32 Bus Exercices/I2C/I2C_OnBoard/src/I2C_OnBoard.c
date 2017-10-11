#include "stm32f4xx_hal.h"

static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout);

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(Status == RESET)
  {
    while(__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          hi2c->State= HAL_I2C_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2c);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_I2C_GET_FLAG(hi2c, Flag) != RESET)
    {
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          hi2c->State= HAL_I2C_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2c);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Get tick */
  tickstart = HAL_GetTick();

  while(__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
  {
    if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
    {
      /* Generate Stop */
      hi2c->Instance->CR1 |= I2C_CR1_STOP;

      /* Clear AF Flag */
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

      hi2c->ErrorCode = HAL_I2C_ERROR_AF;
      hi2c->State= HAL_I2C_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        hi2c->State= HAL_I2C_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_OnBoard(I2C_HandleTypeDef *hi2cMaster, I2C_HandleTypeDef *hi2cSlave, uint16_t DevAddress, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{

  if((hi2cMaster->State == HAL_I2C_STATE_READY) && (hi2cSlave->State == HAL_I2C_STATE_READY))
  {
    if((pTxData == NULL) || (Size == 0))
    {
      return  HAL_ERROR;
    }

      if(__HAL_I2C_GET_FLAG(hi2cMaster, I2C_FLAG_BUSY) == SET)
      {
        return HAL_BUSY;
      }

    /* Process Locked */
    __HAL_LOCK(hi2cMaster);
    __HAL_LOCK(hi2cSlave);

    hi2cMaster->State = HAL_I2C_STATE_BUSY_TX;
    hi2cMaster->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2cSlave->State = HAL_I2C_STATE_BUSY_RX;
    hi2cSlave->ErrorCode = HAL_I2C_ERROR_NONE;

    /*Slave Ack Enabled*/
    hi2cSlave->Instance->CR1 |= I2C_CR1_ACK;

    /* Generate Start */
    hi2cMaster->Instance->CR1 |= I2C_CR1_START;

    /*Master Wait until SB flag is set */
    if(I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_SB, RESET, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
     }

      /* Send slave address */
      hi2cMaster->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);

      /* Wait until ADDR flag is set */
      if(I2C_WaitOnMasterAddressFlagUntilTimeout(hi2cMaster, I2C_FLAG_ADDR, Timeout) != HAL_OK)
      {
        if(hi2cMaster->ErrorCode == HAL_I2C_ERROR_AF)
        {
          return HAL_ERROR;
        }
        else
        {
          return HAL_TIMEOUT;
        }
      }

    /* Clear ADDR flag */
    __HAL_I2C_CLEAR_ADDRFLAG(hi2cMaster);
    __HAL_I2C_CLEAR_ADDRFLAG(hi2cSlave);

    while(Size > 0)
    {
       /*Wait until TXE flag is set */
      if(I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_TXE, RESET, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Write data to DR */
      hi2cMaster->Instance->DR = (*pTxData++);

      if(I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
      {
        return HAL_TIMEOUT;
      }

      /* Read data from DR */
      (*pRxData++) = hi2cSlave->Instance->DR;
      Size--;

    }

    /* Wait until TXE flag is set */
    if(I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_TXE, RESET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* Generate Stop */
    hi2cMaster->Instance->CR1 |= I2C_CR1_STOP;

    /*Wait until STOP flag is set */
    if(I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_STOPF, RESET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    /* Clear STOP flag */
    __HAL_I2C_CLEAR_STOPFLAG(hi2cSlave);

    /* Disable Address Acknowledge */
    hi2cSlave->Instance->CR1 &= ~I2C_CR1_ACK;

    /* Wait until BUSY flag is reset SLAVE*/
    if(I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_BUSY, SET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    hi2cSlave->State = HAL_I2C_STATE_READY;
    /* Process Unlocked */
    __HAL_UNLOCK(hi2cSlave);

    /* Wait until BUSY flag is reset MASTER*/
    if(I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_BUSY, SET, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }

    hi2cMaster->State = HAL_I2C_STATE_READY;
    /* Process Unlocked */
    __HAL_UNLOCK(hi2cMaster);



    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_OnBoard(I2C_HandleTypeDef *hi2cMaster, I2C_HandleTypeDef *hi2cSlave, uint16_t DevAddress, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
	if ((hi2cMaster->State == HAL_I2C_STATE_READY) && (hi2cSlave->State == HAL_I2C_STATE_READY))
	{
		if ((pTxData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2cMaster, I2C_FLAG_BUSY) == SET)
		{
			return HAL_BUSY;
		}

		/* Process Locked */
		__HAL_LOCK(hi2cMaster);
		__HAL_LOCK(hi2cSlave);

		hi2cMaster->State = HAL_I2C_STATE_BUSY_TX;
		hi2cMaster->ErrorCode = HAL_I2C_ERROR_NONE;

		hi2cSlave->State = HAL_I2C_STATE_BUSY_RX;
		hi2cSlave->ErrorCode = HAL_I2C_ERROR_NONE;

		/*Slave Ack Enabled*/
		hi2cSlave->Instance->CR1 |= I2C_CR1_ACK;

		/* Generate Start */
		hi2cMaster->Instance->CR1 |= I2C_CR1_START;

		/*Master Wait until SB flag is set */
		if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_SB, RESET, Timeout)
				!= HAL_OK) {
			return HAL_TIMEOUT;
		}

		/* Send slave address */
		hi2cMaster->Instance->DR = I2C_7BIT_ADD_READ(DevAddress);

		/* Wait until ADDR flag is set */
		if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2cMaster, I2C_FLAG_ADDR,
				Timeout) != HAL_OK) {
			if (hi2cMaster->ErrorCode == HAL_I2C_ERROR_AF) {
				return HAL_ERROR;
			} else {
				return HAL_TIMEOUT;
			}
		}

		if (Size == 1) {
			/* Disable Acknowledge */
			hi2cMaster->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2cMaster);

			/* Generate Stop */
			hi2cMaster->Instance->CR1 |= I2C_CR1_STOP;
		} else if (Size == 2) {
			/* Disable Acknowledge */
			hi2cMaster->Instance->CR1 &= ~I2C_CR1_ACK;

			/* Enable Pos */
			hi2cMaster->Instance->CR1 |= I2C_CR1_POS;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2cMaster);
		} else {
			/* Enable Acknowledge */
			hi2cMaster->Instance->CR1 |= I2C_CR1_ACK;

			/* Clear ADDR flag */
			__HAL_I2C_CLEAR_ADDRFLAG(hi2cMaster);
		}

		while (Size > 0){
			if (Size <= 3) {
				/* One byte */
				if (Size == 1) {

					/* Wait until TXE flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_TXE,
							RESET, Timeout) != HAL_OK) {
						return HAL_TIMEOUT;
					}

					/* Write data to DR */
					hi2cSlave->Instance->DR = (*pTxData++);

					/* Wait until RXNE flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_RXNE,
							RESET, Timeout) != HAL_OK) {
						return HAL_TIMEOUT;
					}

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;
				}
				/* Two bytes */
				else if (Size == 2) {
					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_BTF,
							RESET, Timeout) != HAL_OK) {
						return HAL_TIMEOUT;
					}

					/* Generate Stop */
					hi2cMaster->Instance->CR1 |= I2C_CR1_STOP;

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;
				}
				/* 3 Last bytes */
				else {
					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_BTF,
							RESET, Timeout) != HAL_OK) {
						return HAL_TIMEOUT;
					}

					/* Disable Acknowledge */
					hi2cMaster->Instance->CR1 &= ~I2C_CR1_ACK;

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;

					/* Wait until BTF flag is set */
					if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_BTF,
							RESET, Timeout) != HAL_OK) {
						return HAL_TIMEOUT;
					}

					/* Generate Stop */
					hi2cMaster->Instance->CR1 |= I2C_CR1_STOP;

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;

					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;
				}
			} else {
				/* Wait until RXNE flag is set */
				if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_RXNE, RESET,
						Timeout) != HAL_OK) {
					return HAL_TIMEOUT;
				}

				/* Read data from DR */
				(*pRxData++) = hi2cMaster->Instance->DR;
				Size--;

				if (__HAL_I2C_GET_FLAG(hi2cMaster, I2C_FLAG_BTF) == SET) {
					/* Read data from DR */
					(*pRxData++) = hi2cMaster->Instance->DR;
					Size--;
				}
			}
	}

	/* Disable Pos */
	hi2cMaster->Instance->CR1 &= ~I2C_CR1_POS;

	/* Wait until AF flag is set */
	if (I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_AF, RESET, Timeout)
			!= HAL_OK) {
		return HAL_TIMEOUT;
	}

	/* Clear AF flag */
	__HAL_I2C_CLEAR_FLAG(hi2cSlave, I2C_FLAG_AF);

	/* Disable Address Acknowledge */
	hi2cSlave->Instance->CR1 &= ~I2C_CR1_ACK;

	/* Wait until BUSY flag is reset SLAVE*/
	if (I2C_WaitOnFlagUntilTimeout(hi2cSlave, I2C_FLAG_BUSY, SET, Timeout)
			!= HAL_OK) {
		return HAL_TIMEOUT;
	}

	hi2cSlave->State = HAL_I2C_STATE_READY;
	/* Process Unlocked */
	__HAL_UNLOCK(hi2cSlave);

	/* Wait until BUSY flag is reset MASTER*/
	if (I2C_WaitOnFlagUntilTimeout(hi2cMaster, I2C_FLAG_BUSY, SET, Timeout)
			!= HAL_OK) {
		return HAL_TIMEOUT;
	}

	hi2cMaster->State = HAL_I2C_STATE_READY;
	/* Process Unlocked */
	__HAL_UNLOCK(hi2cMaster);

	return HAL_OK;
}
	               else
	               {
	                 return HAL_BUSY;
	               }
}
//HAL_StatusTypeDef HAL_I2C_Master_Receive_OnBoard(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//{
//  if(hi2c->State == HAL_I2C_STATE_READY)
//  {
//    if((pData == NULL) || (Size == 0))
//    {
//      return  HAL_ERROR;
//    }
//
//    if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//    {
//      return HAL_BUSY;
//    }
//
//    /* Process Locked */
//    __HAL_LOCK(hi2c);
//
//    hi2c->State = HAL_I2C_STATE_BUSY_RX;
//    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//    /* Send Slave Address */
//    if(I2C_MasterRequestRead(hi2c, DevAddress, Timeout) != HAL_OK)
//    {
//      if(hi2c->ErrorCode == HAL_I2C_ERROR_AF)
//      {
//        /* Process Unlocked */
//        __HAL_UNLOCK(hi2c);
//        return HAL_ERROR;
//      }
//      else
//      {
//        /* Process Unlocked */
//        __HAL_UNLOCK(hi2c);
//        return HAL_TIMEOUT;
//      }
//    }
//
//    if(Size == 1)
//    {
//      /* Disable Acknowledge */
//      hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//      /* Clear ADDR flag */
//      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//      /* Generate Stop */
//      hi2c->Instance->CR1 |= I2C_CR1_STOP;
//    }
//    else if(Size == 2)
//    {
//      /* Disable Acknowledge */
//      hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//      /* Enable Pos */
//      hi2c->Instance->CR1 |= I2C_CR1_POS;
//
//      /* Clear ADDR flag */
//      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//    }
//    else
//    {
//      /* Enable Acknowledge */
//      hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//      /* Clear ADDR flag */
//      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//    }
//
//    while(Size > 0)
//    {
//      if(Size <= 3)
//      {
//        /* One byte */
//        if(Size == 1)
//        {
//          /* Wait until RXNE flag is set */
//          if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
//          {
//            return HAL_TIMEOUT;
//          }
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//        }
//        /* Two bytes */
//        else if(Size == 2)
//        {
//          /* Wait until BTF flag is set */
//          if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
//          {
//            return HAL_TIMEOUT;
//          }
//
//          /* Generate Stop */
//          hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//        }
//        /* 3 Last bytes */
//        else
//        {
//          /* Wait until BTF flag is set */
//          if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
//          {
//            return HAL_TIMEOUT;
//          }
//
//          /* Disable Acknowledge */
//          hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//
//          /* Wait until BTF flag is set */
//          if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout) != HAL_OK)
//          {
//            return HAL_TIMEOUT;
//          }
//
//          /* Generate Stop */
//          hi2c->Instance->CR1 |= I2C_CR1_STOP;
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//        }
//      }
//      else
//      {
//        /* Wait until RXNE flag is set */
//        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
//        {
//          return HAL_TIMEOUT;
//        }
//
//        /* Read data from DR */
//        (*pData++) = hi2c->Instance->DR;
//        Size--;
//
//        if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
//        {
//          /* Read data from DR */
//          (*pData++) = hi2c->Instance->DR;
//          Size--;
//        }
//      }
//    }
//
//    /* Disable Pos */
//    hi2c->Instance->CR1 &= ~I2C_CR1_POS;
//
//    /* Wait until BUSY flag is reset */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    hi2c->State = HAL_I2C_STATE_READY;
//
//    /* Process Unlocked */
//    __HAL_UNLOCK(hi2c);
//
//    return HAL_OK;
//  }
//  else
//  {
//    return HAL_BUSY;
//  }
//}
//
//HAL_StatusTypeDef HAL_I2C_Slave_Transmit_OnBoard(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//{
//  if(hi2c->State == HAL_I2C_STATE_READY)
//  {
//    if((pData == NULL) || (Size == 0))
//    {
//      return  HAL_ERROR;
//    }
//
//    if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//    {
//      return HAL_BUSY;
//    }
//
//    /* Process Locked */
//    __HAL_LOCK(hi2c);
//
//    hi2c->State = HAL_I2C_STATE_BUSY_TX;
//    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//    /* Enable Address Acknowledge */
//    hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//    /* Wait until ADDR flag is set */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    /* Clear ADDR flag */
//    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//    /* If 10bit addressing mode is selected */
//    if(hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_10BIT)
//    {
//      /* Wait until ADDR flag is set */
//      if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout) != HAL_OK)
//      {
//        return HAL_TIMEOUT;
//      }
//
//      /* Clear ADDR flag */
//      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//    }
//
//    while(Size > 0)
//    {
//      /* Wait until TXE flag is set */
//      if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TXE, RESET, Timeout) != HAL_OK)
//      {
//        return HAL_TIMEOUT;
//      }
//
//      /* Write data to DR */
//      hi2c->Instance->DR = (*pData++);
//      Size--;
//
//      if((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (Size != 0))
//      {
//        /* Write data to DR */
//        hi2c->Instance->DR = (*pData++);
//        Size--;
//      }
//    }
//
//    /* Wait until AF flag is set */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_AF, RESET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    /* Clear AF flag */
//    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
//
//    /* Disable Address Acknowledge */
//    hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//    /* Wait until BUSY flag is reset */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    hi2c->State = HAL_I2C_STATE_READY;
//
//    /* Process Unlocked */
//    __HAL_UNLOCK(hi2c);
//
//    return HAL_OK;
//  }
//  else
//  {
//    return HAL_BUSY;
//  }
//}
//
//HAL_StatusTypeDef HAL_I2C_Slave_Receive_OnBoard(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//{
//  if(hi2c->State == HAL_I2C_STATE_READY)
//  {
//    if((pData == NULL) || (Size == 0))
//    {
//      return  HAL_ERROR;
//    }
//
//    if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) == SET)
//    {
//      return HAL_BUSY;
//    }
//
//    /* Process Locked */
//    __HAL_LOCK(hi2c);
//
//    hi2c->State = HAL_I2C_STATE_BUSY_RX;
//    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
//
//    /* Enable Address Acknowledge */
//    hi2c->Instance->CR1 |= I2C_CR1_ACK;
//
//    /* Wait until ADDR flag is set */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    /* Clear ADDR flag */
//    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
//
//    while(Size > 0)
//    {
//      /* Wait until RXNE flag is set */
//      if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout) != HAL_OK)
//      {
//        return HAL_TIMEOUT;
//      }
//
//      /* Read data from DR */
//      (*pData++) = hi2c->Instance->DR;
//      Size--;
//
//      if((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (Size != 0))
//      {
//        /* Read data from DR */
//        (*pData++) = hi2c->Instance->DR;
//        Size--;
//      }
//    }
//
//    /* Wait until STOP flag is set */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_STOPF, RESET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    /* Clear STOP flag */
//    __HAL_I2C_CLEAR_STOPFLAG(hi2c);
//
//    /* Disable Address Acknowledge */
//    hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
//
//    /* Wait until BUSY flag is reset */
//    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, Timeout) != HAL_OK)
//    {
//      return HAL_TIMEOUT;
//    }
//
//    hi2c->State = HAL_I2C_STATE_READY;
//
//    /* Process Unlocked */
//    __HAL_UNLOCK(hi2c);
//
//    return HAL_OK;
//  }
//  else
//  {
//    return HAL_BUSY;
//  }
//}
