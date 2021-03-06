//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 *
 * @brief	Questo Main gestisce due componenti SPI Master e Slave che inviano e trasmetteno.
 */
#include <stdio.h>
#include "diag/Trace.h"

#include "config.h"

#define DEBUG

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via ITM).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

SPI_HandleTypeDef SpiMasterHandle, SpiSlaveHandle;
HAL_StatusTypeDef Debug;

uint8_t *txMasterBuffer, *rxMasterBuffer, *txSlaveBuffer, *rxSlaveBuffer;
uint8_t KeepLoop = 1;

void finalize(){
	HAL_SPI_DeInit(&SpiMasterHandle);
	HAL_SPI_DeInit(&SpiSlaveHandle);
	free(txMasterBuffer);
	free(rxMasterBuffer);
	free(txSlaveBuffer);
	free(rxSlaveBuffer);
	BSP_LED_On(LED3);
	BSP_LED_On(LED4);
	BSP_LED_On(LED5);
	BSP_LED_On(LED6);
	while(1)
	{}

}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

void setup(){

	SystemClock_Config();

	SpiMasterHandle.Instance               = SpiMaster;
	SpiMasterHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	SpiMasterHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	SpiMasterHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	SpiMasterHandle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	SpiMasterHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	SpiMasterHandle.Init.CRCPolynomial     = 7;
	SpiMasterHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	SpiMasterHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiMasterHandle.Init.NSS               = SPI_NSS_SOFT;
	SpiMasterHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
	SpiMasterHandle.Init.Mode              = SPI_MODE_MASTER;

	  if(HAL_SPI_Init(&SpiMasterHandle) != HAL_OK)
	  {
	    finalize();
	  }

		SpiSlaveHandle.Instance               = SpiSlave;
		SpiSlaveHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
		SpiSlaveHandle.Init.Direction         = SPI_DIRECTION_2LINES;
		SpiSlaveHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
		SpiSlaveHandle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
		SpiSlaveHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SpiSlaveHandle.Init.CRCPolynomial     = 7;
		SpiSlaveHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
		SpiSlaveHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SpiSlaveHandle.Init.NSS               = SPI_NSS_SOFT;
		SpiSlaveHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
		SpiSlaveHandle.Init.Mode              = SPI_MODE_SLAVE;

		  if(HAL_SPI_Init(&SpiSlaveHandle) != HAL_OK)
		  {
		    finalize();
		  }

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	txMasterBuffer = (uint8_t*)malloc(sizeof(uint8_t)*TXBUFFERSIZE);
	rxMasterBuffer = (uint8_t*)malloc(sizeof(uint8_t)*RXBUFFERSIZE);

	txSlaveBuffer = (uint8_t*)malloc(sizeof(uint8_t)*TXBUFFERSIZE);
	rxSlaveBuffer = (uint8_t*)malloc(sizeof(uint8_t)*RXBUFFERSIZE);

	txMasterBuffer[0]=0x01;
	rxMasterBuffer[0]=0x00;
	txSlaveBuffer[0]=0x01;
	rxSlaveBuffer[0]=0x02;

#ifdef DEBUG
	BSP_LED_On(LED4);
	BSP_LED_On(LED5);
#endif

}
int
main(int argc, char* argv[])
{

	setup();

  while (KeepLoop)
    {
		while (BSP_PB_GetState(BUTTON_KEY) != 1){}
		while (BSP_PB_GetState(BUTTON_KEY) != 0){}

		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);

		while((Debug = HAL_SPI_TransmitReceive_OnBoard(&SpiMasterHandle, &SpiSlaveHandle, (uint8_t*)txMasterBuffer, (uint8_t*)rxSlaveBuffer, TXBUFFERSIZE, 5000))!=HAL_OK){
		}


		BSP_LED_On(rxSlaveBuffer[0]);
		txMasterBuffer[0] = (txMasterBuffer[0]+1)%4;
    }

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
