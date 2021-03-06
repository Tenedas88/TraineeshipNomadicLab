//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 *
 * @brief	Questo Main gestisce due componenti I2C sullo stesso SoC che inviano e trasmettono
 * 			in polling.
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

I2C_HandleTypeDef I2cMasterHandle, I2cSlaveHandle;

uint8_t *RxMasterBuffer, *RxSlaveBuffer;
uint8_t *TxMasterBuffer, *TxSlaveBuffer;

uint8_t KeepLoop = 1;
HAL_StatusTypeDef Debug;

void finalize(){
	HAL_I2C_DeInit(&I2cMasterHandle);
	HAL_I2C_DeInit(&I2cSlaveHandle);
	free(RxMasterBuffer);
	free(TxMasterBuffer);
	free(RxSlaveBuffer);
	free(TxSlaveBuffer);
	BSP_LED_On(LED3);
	BSP_LED_On(LED4);
	BSP_LED_On(LED5);
	BSP_LED_On(LED6);
	while(1){
	}
}

void initialization(){

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


	  //I2C Master Interface Init

	  I2cMasterHandle.Instance             = I2C_MasterBus;

	  I2cMasterHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	  I2cMasterHandle.Init.ClockSpeed      = 400000;
	  I2cMasterHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	  I2cMasterHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
	  I2cMasterHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	  I2cMasterHandle.Init.NoStretchMode   = I2C_NOSTRETCH_ENABLED;
	  I2cMasterHandle.Init.OwnAddress1     = I2C_MasterAddress;
	  I2cMasterHandle.Init.OwnAddress2     = 0xFE;

	  if(HAL_I2C_Init(&I2cMasterHandle) != HAL_OK)
	    {
	      /* Initialization Error */
	      finalize();
	    }

	  //I2C Slave Interface Init

	  I2cSlaveHandle.Instance             = I2C_SlaveBus;

	  I2cSlaveHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	  I2cSlaveHandle.Init.ClockSpeed      = 400000;
	  I2cSlaveHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	  I2cSlaveHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
	  I2cSlaveHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	  I2cSlaveHandle.Init.NoStretchMode   = I2C_NOSTRETCH_ENABLED;
	  I2cSlaveHandle.Init.OwnAddress1     = I2C_SlaveAddress;
	  I2cSlaveHandle.Init.OwnAddress2     = 0xFE;

	  if(HAL_I2C_Init(&I2cSlaveHandle) != HAL_OK)
	    {
	      /* Initialization Error */
	      finalize();
	    }

	  //Board Physicals Init

		BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
		BSP_LED_Init(LED3);
		BSP_LED_Init(LED4);
		BSP_LED_Init(LED5);
		BSP_LED_Init(LED6);

		//Resource Init

		TxMasterBuffer = (uint8_t*)malloc(sizeof(uint8_t)*TXBUFFERSIZE);
		RxMasterBuffer = (uint8_t*)malloc(sizeof(uint8_t)*RXBUFFERSIZE);

		TxSlaveBuffer = (uint8_t*)malloc(sizeof(uint8_t)*TXBUFFERSIZE);
		RxSlaveBuffer = (uint8_t*)malloc(sizeof(uint8_t)*RXBUFFERSIZE);

		TxMasterBuffer[0]=0x00;
		RxMasterBuffer[0]=0x03;
		TxSlaveBuffer[0]=0x00;
		RxSlaveBuffer[0]=0x01;

#ifdef DEBUG
		BSP_LED_On(LED5);
		BSP_LED_On(LED6);
#endif
}

//Slave trasmette Master Riceve
int main(int argc, char* argv[])
{
    initialization();

    while(KeepLoop){

    	while (BSP_PB_GetState(BUTTON_KEY) != 1){}
		while (BSP_PB_GetState(BUTTON_KEY) != 0){}

		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);

		Debug = HAL_I2C_Slave_Transmit_OnBoard(&I2cMasterHandle, &I2cSlaveHandle, (uint16_t)I2C_SlaveAddress, (uint8_t*)TxSlaveBuffer, (uint8_t*) RxMasterBuffer, TXBUFFERSIZE, 1000);
		BSP_LED_On(RxMasterBuffer[0]);


		TxSlaveBuffer[0] = (TxSlaveBuffer[0]+1)%4;
    }

}

//Master Trasmette Slave Riceve
//int main(int argc, char* argv[])
//{
//    initialization();
//
//    while(KeepLoop){
//
//    	while (BSP_PB_GetState(BUTTON_KEY) != 1){}
//		while (BSP_PB_GetState(BUTTON_KEY) != 0){}
//
//		BSP_LED_Off(LED3);
//		BSP_LED_Off(LED4);
//		BSP_LED_Off(LED5);
//		BSP_LED_Off(LED6);
//
//		Debug = HAL_I2C_Master_Transmit_OnBoard(&I2cMasterHandle, &I2cSlaveHandle, (uint16_t)I2C_SlaveAddress, (uint8_t*)TxMasterBuffer, (uint8_t*) RxSlaveBuffer, TXBUFFERSIZE, 1000);
//		BSP_LED_On(RxSlaveBuffer[0]);
//
//
//		TxMasterBuffer[0] = (TxMasterBuffer[0]+1)%4;
//    }
//
//}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
