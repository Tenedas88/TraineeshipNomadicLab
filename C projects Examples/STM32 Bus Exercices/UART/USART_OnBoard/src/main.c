//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 *
 * @brief	Questo Main gestisce due componenti UART Master e Slave che inviano
 * 			e ricevono sotto interruzioni.
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

HAL_StatusTypeDef Debug;
UART_HandleTypeDef UartMasterHandle, UartSlaveHandle;
__IO ITStatus UartMasterReady = RESET;
__IO ITStatus UartSlaveReady = RESET;

uint8_t *txMasterBuffer, *rxMasterBuffer, *txSlaveBuffer, *rxSlaveBuffer;;
uint8_t KeepLoop = 1;

void finalize(){
	HAL_UART_DeInit(&UartMasterHandle);
	HAL_UART_DeInit(&UartMasterHandle);
	free(txMasterBuffer);
	free(rxMasterBuffer);
	free(txSlaveBuffer);
	free(rxSlaveBuffer);
	BSP_LED_On(LED3);
	BSP_LED_On(LED4);
	BSP_LED_On(LED5);
	BSP_LED_On(LED6);
	KeepLoop = 0;
	while(1)
	{}
}

void UsartMaster_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartMasterHandle);
}

void UsartSlave_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartSlaveHandle);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if(UartHandle->Instance == UsartMaster){
		    txMasterBuffer[0] = (txMasterBuffer[0]+1)%4;
			UartMasterReady = SET;
	}
	else{
			txSlaveBuffer[0] = (txSlaveBuffer[0]+1)%4;
			UartSlaveReady = SET;
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if(UartHandle->Instance == UsartMaster){
		BSP_LED_On(rxMasterBuffer[0]);
	    UartMasterReady = SET;
	}
	else{
		BSP_LED_On(rxSlaveBuffer[0]);
		UartSlaveReady = SET;
	}

}

 void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  finalize();
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
	  /* Configure the system clock to 168 MHz */
	  SystemClock_Config();

	  UartMasterHandle.Instance          = UsartMaster;

	  UartMasterHandle.Init.BaudRate     = 9600;
	  UartMasterHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartMasterHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartMasterHandle.Init.Parity       = UART_PARITY_NONE;
	  UartMasterHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartMasterHandle.Init.Mode         = UART_MODE_TX_RX;
	  UartMasterHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if(HAL_UART_Init(&UartMasterHandle) != HAL_OK)
	  {
	    finalize();
	  }

	  UartSlaveHandle.Instance          = UsartSlave;

	  UartSlaveHandle.Init.BaudRate     = 9600;
	  UartSlaveHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartSlaveHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartSlaveHandle.Init.Parity       = UART_PARITY_NONE;
	  UartSlaveHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartSlaveHandle.Init.Mode         = UART_MODE_TX_RX;
	  UartSlaveHandle.Init.OverSampling = UART_OVERSAMPLING_16;


	  if(HAL_UART_Init(&UartSlaveHandle) != HAL_OK)
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
	  rxSlaveBuffer[0]=0x00;

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

		if((Debug = HAL_UART_Transmit_IT(&UartMasterHandle, (uint8_t*)txMasterBuffer, TXBUFFERSIZE))!= HAL_OK)
		{
		    finalize();
		}

		if((Debug =HAL_UART_Receive_IT(&UartSlaveHandle, (uint8_t*)rxSlaveBuffer, RXBUFFERSIZE))!= HAL_OK)
		{
		    finalize();
		}

		while(UartMasterReady != SET){}
		UartMasterReady = RESET;

		while(UartSlaveReady != SET){}
		UartSlaveReady = RESET;



    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
