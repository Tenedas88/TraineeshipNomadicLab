//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 *
 * @brief	Questo Main gestisce un componente SPI Slave che riceve.
 */
#include <stdio.h>
#include "diag/Trace.h"

#include "config.h"
// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
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



SPI_HandleTypeDef  SlaveSpiHandle;
uint8_t  *slaveTxBuffer, *slaveRxBuffer;
uint8_t check_loop = 1;

void setup();
void loop();
uint8_t isLoop();
void finalize();

int main(int argc, char* argv[]){
	setup();
	while(isLoop()){
		loop();
	}
	finalize();
}

void setup(){

	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_OscInitTypeDef RCC_OscInitStruct;

	  /* Enable Power Control clock */
	  __PWR_CLK_ENABLE();

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

//SLAVE
	   SlaveSpiHandle.Instance               = SPIS;
	   SlaveSpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	   SlaveSpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	   SlaveSpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	   SlaveSpiHandle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	   SlaveSpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
	   SlaveSpiHandle.Init.CRCPolynomial     = 7;
	   SlaveSpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	   SlaveSpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	   SlaveSpiHandle.Init.NSS               = SPI_NSS_SOFT;
	   SlaveSpiHandle.Init.TIMode            = SPI_TIMODE_DISABLED;
	   SlaveSpiHandle.Init.Mode              = SPI_MODE_SLAVE;


	  if(HAL_SPI_Init(&SlaveSpiHandle) != HAL_OK)
	    {
	      /* Initialization Error */
	      finalize();
	    }


	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);


	slaveTxBuffer = (uint8_t*)malloc(sizeof(uint8_t)*TXBUFFERSIZE);
    slaveRxBuffer = (uint8_t*)malloc(sizeof(uint8_t)*RXBUFFERSIZE);


	slaveTxBuffer[0]=0x02;
	slaveRxBuffer[0]=0x00;
}

void loop(){

	//while (BSP_PB_GetState(BUTTON_KEY ) != 1);
	//while (BSP_PB_GetState(BUTTON_KEY ) != 0);


	 while(HAL_SPI_Receive(&SlaveSpiHandle, slaveRxBuffer, TXBUFFERSIZE, 10000)!= HAL_OK);

	 BSP_LED_Off(LED3);
 	 BSP_LED_Off(LED4);
	 BSP_LED_Off(LED5);
	 BSP_LED_Off(LED6);


	 BSP_LED_On(slaveRxBuffer[0]);
	 *slaveTxBuffer = (*slaveTxBuffer+1)%4;

//	 while (BSP_PB_GetState(BUTTON_KEY ) != 1);
//	 while (BSP_PB_GetState(BUTTON_KEY ) != 0);

//	 HAL_SPI_Transmit(&SlaveSpiHandle, slaveTxBuffer, TXBUFFERSIZE, 10000);
//
//	 while(HAL_SPI_Receive(&SlaveSpiHandle, slaveRxBuffer, TXBUFFERSIZE, 10000)!= HAL_OK);
//
//	 BSP_LED_Off(slaveRxBuffer[0]);
//
//	 while (BSP_PB_GetState(BUTTON_KEY ) != 1);
//	 while (BSP_PB_GetState(BUTTON_KEY ) != 0);


	}

uint8_t isLoop(){

	return check_loop;
}

void finalize(){

	BSP_LED_On(LED3);
	BSP_LED_On(LED4);
	BSP_LED_On(LED5);
	BSP_LED_On(LED6);
	check_loop = 0;

	HAL_SPI_DeInit(&SlaveSpiHandle);


	free(slaveRxBuffer);
	free(slaveTxBuffer);
}



#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
