//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 * @date    24-May-2015
 *
 * @brief	Questo Main gestisce l'accelerometro della STM32F4 e l'user button al fine di
 * 			generare Report per un USB device GamePad.
 * 			La valutazione delle coordinate e della pressione del bottone avviene nella
 * 			callback dell'interruzione sul timer.
 * 			Il calcolo non avviene ad ogni chiamata ma ogni cento dato che la frame di USB
 * 			è pari ad un 1ms ed il clock è impostato a 168Mhz.
 */
#include <stdio.h>
#include "diag/Trace.h"
#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_accelerometer.h"

#include "usbd_core.h"
#include "usbd_hid.h"
#include "usbd_desc.h"

USBD_HandleTypeDef USBD_Device;
uint16_t sampling_rate = 0;
int16_t *posBuffer;
int8_t *report;

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

void HAL_SYSTICK_Callback(void);

int main(int argc, char* argv[]){


  /**
   * Allocazione Buffer
   */
  posBuffer = malloc(sizeof(uint16_t)*3);

  report= malloc(sizeof(uint8_t)*5);

  /**
   * Inizializzazione Componenti
   */

  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  BSP_ACCELERO_Init();

  /**
   * Inizializzazione Firmware USB
   */

  USBD_Init(&USBD_Device, &HID_Desc, 0);

  USBD_RegisterClass(&USBD_Device, &USBD_HID);

  USBD_Start(&USBD_Device);

  /**
   * Idle Loop
   */
  while (1){}
}

void HAL_SYSTICK_Callback(void){

	sampling_rate++;

	if(sampling_rate == 100){

	/**
	 * Acquisizione dati accelerometro
	 **/
	posBuffer[0] = 0;
	posBuffer[1] = 0;
	posBuffer[2] = 0;

	BSP_ACCELERO_GetXYZ(posBuffer);

	/**
	 * Orientamento asse Y
	 */

	if(-posBuffer[1] > 128)
		if(-posBuffer[1] >= 508)
			report[2] = 0x7f;
		else
			report[2] = floor(-posBuffer[1]/4);
	else if(-posBuffer[1] < -128)
		if(-posBuffer[1] <= -508)
			report[2] = 0x81;
		else
			report[2] = floor(-posBuffer[1]/4);
	else
		report[2] = 0x00;

	/**
	 * Orientamento asse X
	 */

	if(posBuffer[0] > 128)
		if(posBuffer[0] >= 508)
			report[1] = 0x7f;
		else
			report[1] = floor(posBuffer[0]/4);
	else if(posBuffer[0] < -128)
		if(posBuffer[0] <= -508)
			report[1] = 0x81;
		else
			report[1] = floor(posBuffer[0]/4);
	else
		report[1] = 0x00;

	sampling_rate = 0;
	}

	/**
	 * Acquisizione pressione UserButton
	 */
	if(BSP_PB_GetState(BUTTON_KEY) == 1){
		report[0] = 0x01;
	}
	else{
		report[0] = 0x00;
	}

	/**
	 * Invio del report USB all'host
	 */
	USBD_HID_SendReport (&USBD_Device, (uint8_t*)report, 3);

}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
