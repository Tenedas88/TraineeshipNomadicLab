//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//


// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 * @date    4-June-2015
 *
 * @brief   Questo Main utilizza la classe USB device Mass Storage e la memoria Flash disponibile
 * 			sull'STM32F4 per realizzare il firmware di una chiavetta USB di 100kb.
 *			All'avvio la RAM viene inizializzata con i valori contenuti nella FLASH e viene
 *			utilizzata per lo storage dinamico dei dati.
 *			Alla disconnessione dall'host il contenuto della RAM viene salvato sulla FLASH.
 *
 *			Si è scelto questo tipo di politica poichè la FLASH contenuta sull STM32F4 necessiterebbe
 *			di troppe Cancellazioni/riscritture dovute alla tecnologia con una conseguente usura
 *			del componente.
 */
#include <stdio.h>
#include "usbd_msc_F4Flash.h"
#include "diag/Trace.h"


#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"



#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"


USBD_HandleTypeDef USBD_Device;
uint8_t Report[3];

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	int Count = 0;

	  /**
	   *  Inizializzazione LED3, LED4, LED5 and LED6
	   */
	  BSP_LED_Init(LED3);
	  BSP_LED_Init(LED4);
	  BSP_LED_Init(LED5);
	  BSP_LED_Init(LED6);


	  /**
	   *  Inizializzazione Firmware
	   *  */
	USBD_Device.dev_speed = USBD_SPEED_FULL;
	USBD_Init(&USBD_Device, &MSD_Desc, 0);
	USBD_RegisterClass(&USBD_Device, &USBD_MSC);
	USBD_MSC_RegisterStorage(&USBD_Device, &USBD_MSC_F4Memory_fops);
	USBD_Start(&USBD_Device);

	Report[0] = 0x00;
	Report[1] = 0x00;
	Report[2] = 0x01;
  /**
   * Idle Loop
   */
  while (1)
    {

	 /*while(Count < 1000){
		  Count++;
		  if(Count == 100){
			  USBD_HID_SendReport (&USBD_Device, (uint8_t*)Report, 3);
			  Count = 0;
		  }
	  }*/
    }

}




#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
