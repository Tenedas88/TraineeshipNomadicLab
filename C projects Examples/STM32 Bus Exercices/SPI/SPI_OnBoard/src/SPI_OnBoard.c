/*
 * SPI_OnBoard.c
 *
 *  Created on: May 6, 2015
 *      Author: davide
 */

#include "stm32f4xx_hal.h"

static HAL_StatusTypeDef SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
  uint32_t tickstart = 0;

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until flag is set */
  if(Status == RESET)
  {
    while(__HAL_SPI_GET_FLAG(hspi, Flag) == RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable the SPI and reset the CRC: the CRC value should be cleared
             on both master and slave sides in order to resynchronize the master
             and slave for their respective CRC calculation */

          /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
          __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);

          /* Reset CRC Calculation */
          if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
          {
            SPI_RESET_CRC(hspi);
          }

          hspi->State= HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while(__HAL_SPI_GET_FLAG(hspi, Flag) != RESET)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Disable the SPI and reset the CRC: the CRC value should be cleared
             on both master and slave sides in order to resynchronize the master
             and slave for their respective CRC calculation */

          /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
          __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);

          /* Reset CRC Calculation */
          if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
          {
            SPI_RESET_CRC(hspi);
          }

          hspi->State= HAL_SPI_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hspi);

          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}


HAL_StatusTypeDef HAL_SPI_TransmitReceive_OnBoard(SPI_HandleTypeDef *hspiMaster, SPI_HandleTypeDef *hspiSlave, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout){

	// [ILG]
	  #if defined ( __GNUC__ )
	  #pragma GCC diagnostic push
	  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	  #endif
	  __IO uint16_t tmpreg;
	  // [ILG]
	  #if defined ( __GNUC__ )
	  #pragma GCC diagnostic pop
	  #endif

	  uint32_t tmp = 0;

	  if(hspiMaster->State == HAL_SPI_STATE_READY && hspiSlave->State == HAL_SPI_STATE_READY)
	  {
	    if((pTxData == NULL ) || (Size == 0))
	    {
	      return  HAL_ERROR;
	    }

	    /* Check the parameters */
	    assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspiMaster->Init.Direction));

	    /* Process Locked */
	    __HAL_LOCK(hspiMaster);
	    __HAL_LOCK(hspiSlave);

	    /* Configure communication */
	    hspiMaster->State = HAL_SPI_STATE_BUSY_TX;
	    hspiMaster->ErrorCode   = HAL_SPI_ERROR_NONE;
	    hspiSlave->State = HAL_SPI_STATE_BUSY_RX;
	    hspiSlave->ErrorCode   = HAL_SPI_ERROR_NONE;

	    hspiMaster->pTxBuffPtr = pTxData;
	    hspiMaster->TxXferSize = Size;
	    hspiMaster->TxXferCount = Size;

	    hspiSlave->pRxBuffPtr  = pRxData;
	    hspiSlave->RxXferSize  = Size;
	    hspiSlave->RxXferCount = Size;

	    /*Init field not used in handle to zero */
	    hspiMaster->TxISR = 0;
	    hspiMaster->RxISR = 0;
	    hspiMaster->RxXferSize   = 0;
	    hspiMaster->RxXferCount  = 0;

	    hspiSlave->RxISR = 0;
	    hspiSlave->TxISR = 0;
	    hspiSlave->TxXferSize   = 0;
	    hspiSlave->TxXferCount  = 0;

	    /* Reset CRC Calculation */
	    if(hspiMaster->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	    {
	      SPI_RESET_CRC(hspiMaster);
	    }

	    if(hspiSlave->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	    {
	      SPI_RESET_CRC(hspiSlave);
	    }

	    /* Configure communication direction : 1Line */
	    if(hspiMaster->Init.Direction == SPI_DIRECTION_1LINE)
	    {
	      SPI_1LINE_TX(hspiMaster);
	    }

	    if(hspiSlave->Init.Direction == SPI_DIRECTION_1LINE)
	    {
	      SPI_1LINE_RX(hspiSlave);
	    }

	    if((hspiSlave->Init.Mode == SPI_MODE_MASTER) && (hspiSlave->Init.Direction == SPI_DIRECTION_2LINES))
	    {
	      /* Process Unlocked */
	      __HAL_UNLOCK(hspiSlave);

	      /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
	      return HAL_SPI_TransmitReceive(hspiSlave, pTxData, pRxData, Size, Timeout);
	    }

	    /* Check if the SPI is already enabled */
	    if((hspiMaster->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
	    {
	      /* Enable SPI peripheral */
	      __HAL_SPI_ENABLE(hspiMaster);
	    }

	    if((hspiSlave->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
	    {
	      /* Enable SPI peripheral */
	      __HAL_SPI_ENABLE(hspiSlave);
	    }

	    /* Transmit data in 8 Bit mode */
	       if(hspiMaster->Init.DataSize == SPI_DATASIZE_8BIT)
	       {
	         if((hspiMaster->Init.Mode == SPI_MODE_SLAVE)|| (hspiMaster->TxXferCount == 0x01))
	         {
	        	 hspiMaster->Instance->DR = (*hspiMaster->pTxBuffPtr++);
	        	 hspiMaster->TxXferCount--;
	        	        /* Wait until RXNE flag is set */
	        	        if(SPI_WaitOnFlagUntilTimeout(hspiSlave, SPI_FLAG_RXNE, RESET, Timeout) != HAL_OK)
	        	        {
	        	          return HAL_TIMEOUT;
	        	        }

	        	        (*hspiSlave->pRxBuffPtr++) = hspiSlave->Instance->DR;
	        	        hspiSlave->RxXferCount--;
	         }
	         while(hspiMaster->TxXferCount > 0)
	         {
	           /* Wait until TXE flag is set to send data */
	           if(SPI_WaitOnFlagUntilTimeout(hspiMaster, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
	           {
	             return HAL_TIMEOUT;
	           }
	           hspiMaster->Instance->DR = (*hspiMaster->pTxBuffPtr++);
	           hspiMaster->TxXferCount--;

	           /* Wait until RXNE flag is set */
	           if(SPI_WaitOnFlagUntilTimeout(hspiSlave, SPI_FLAG_RXNE, RESET, Timeout) != HAL_OK)
	           {
	          	   return HAL_TIMEOUT;
	          	}
       	        (*hspiSlave->pRxBuffPtr++) = hspiSlave->Instance->DR;
       	        hspiSlave->RxXferCount--;

	         }
	         /* Enable CRC Transmission */
	         if(hspiMaster->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	         {
	        	 hspiMaster->Instance->CR1 |= SPI_CR1_CRCNEXT;
	         }
	         if(hspiSlave->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	         {
	           hspiSlave->Instance->CR1 |= SPI_CR1_CRCNEXT;
	         }
	       }
	       /* Transmit data in 16 Bit mode*/
	       else
	       {
	         if((hspiMaster->Init.Mode == SPI_MODE_SLAVE) || (hspiMaster->TxXferCount == 0x01))
	         {
	        	 hspiMaster->Instance->DR = *((uint16_t*)hspiMaster->pTxBuffPtr);
	        	 hspiMaster->pTxBuffPtr+=2;
	           hspiMaster->TxXferCount--;
	           /* Wait until RXNE flag is set to read data */
	           if(SPI_WaitOnFlagUntilTimeout(hspiSlave, SPI_FLAG_RXNE, RESET, Timeout) != HAL_OK)
	           {
	             return HAL_TIMEOUT;
	           }

	           *((uint16_t*)hspiSlave->pRxBuffPtr) = hspiSlave->Instance->DR;
	           hspiSlave->pRxBuffPtr+=2;
	           hspiSlave->RxXferCount--;
	         }
	         while(hspiMaster->TxXferCount > 0)
	         {
	           /* Wait until TXE flag is set to send data */
	           if(SPI_WaitOnFlagUntilTimeout(hspiMaster, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
	           {
	             return HAL_TIMEOUT;
	           }
	           hspiMaster->Instance->DR = *((uint16_t*)hspiMaster->pTxBuffPtr);
	           hspiMaster->pTxBuffPtr+=2;
	           hspiMaster->TxXferCount--;
	           /* Wait until RXNE flag is set to read data */
	           if(SPI_WaitOnFlagUntilTimeout(hspiSlave, SPI_FLAG_RXNE, RESET, Timeout) != HAL_OK)
	           {
	             return HAL_TIMEOUT;
	           }

	           *((uint16_t*)hspiSlave->pRxBuffPtr) = hspiSlave->Instance->DR;
	           hspiSlave->pRxBuffPtr+=2;
	           hspiSlave->RxXferCount--;
	         }
	         /* Enable CRC Transmission */
	         if(hspiMaster->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	         {
	        	 hspiMaster->Instance->CR1 |= SPI_CR1_CRCNEXT;
	         }
	         if(hspiSlave->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	         {
	           hspiSlave->Instance->CR1 |= SPI_CR1_CRCNEXT;
	         }
	       }

	       /* Wait until RXNE flag is set: CRC Received */
	       if(hspiSlave->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
	       {
	         if(SPI_WaitOnFlagUntilTimeout(hspiSlave, SPI_FLAG_RXNE, RESET, Timeout) != HAL_OK)
	         {
	        	 hspiSlave->ErrorCode |= HAL_SPI_ERROR_CRC;
	           return HAL_TIMEOUT;
	         }

	       /* Read CRC to Flush RXNE flag */
	        tmpreg = hspiSlave->Instance->DR;
	        UNUSED(tmpreg);
	       }

	      if((hspiSlave->Init.Mode == SPI_MODE_MASTER)&&((hspiSlave->Init.Direction == SPI_DIRECTION_1LINE)||(hspiSlave->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
	      {
	        /* Disable SPI peripheral */
	        __HAL_SPI_DISABLE(hspiSlave);
	      }

	      /* Wait until TXE flag is set to send data */
	      if(SPI_WaitOnFlagUntilTimeout(hspiMaster, SPI_FLAG_TXE, RESET, Timeout) != HAL_OK)
	      {
	        hspiMaster->ErrorCode |= HAL_SPI_ERROR_FLAG;
	        return HAL_TIMEOUT;
	      }

	      /* Wait until Busy flag is reset before disabling SPI */
	      if(SPI_WaitOnFlagUntilTimeout(hspiMaster, SPI_FLAG_BSY, SET, Timeout) != HAL_OK)
	      {
	        hspiMaster->ErrorCode |= HAL_SPI_ERROR_FLAG;
	        return HAL_TIMEOUT;
	      }

	      /* Clear OVERRUN flag in 2 Lines communication mode because received is not read */
	      if(hspiMaster->Init.Direction == SPI_DIRECTION_2LINES)
	      {
	        __HAL_SPI_CLEAR_OVRFLAG(hspiMaster);
	      }

	      hspiSlave->State = HAL_SPI_STATE_READY;
	      hspiMaster->State = HAL_SPI_STATE_READY;

	      tmp = __HAL_SPI_GET_FLAG(hspiSlave, SPI_FLAG_CRCERR);
	      /* Check if CRC error occurred */
	      if((hspiSlave->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE) && (tmp != RESET))
	      {
	    	  hspiSlave->ErrorCode |= HAL_SPI_ERROR_CRC;

	        /* Reset CRC Calculation */
	        SPI_RESET_CRC(hspiSlave);

	        /* Process Unlocked */
	        __HAL_UNLOCK(hspiSlave);

	        return HAL_ERROR;
	      }

	      /* Process Unlocked */
	      __HAL_UNLOCK(hspiSlave);
	      __HAL_UNLOCK(hspiMaster);

	    return HAL_OK;
	  }
	  else
		  return HAL_BUSY;
}
