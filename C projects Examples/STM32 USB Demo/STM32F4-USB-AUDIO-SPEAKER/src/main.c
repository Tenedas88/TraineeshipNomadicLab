//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 * @date    24-May-2015
 *
 * @brief	Questo Main gestisce il componente della STM32F4 relativo al Jack Audio per la
 * 			riproduzione musicale. I dati sono acquisiti in streaming tramite la classe USB
 * 			audio 1.0 e inviati tramite DMA al componente.
 */
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_audio.h"
#include "usbd_audio_if.h"

USBD_HandleTypeDef USBD_Device;

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(void)
{
  
  /**
  * Inizializzazione Firmware USB
  */
  USBD_Init(&USBD_Device, &AUDIO_Desc, 0);

  USBD_RegisterClass(&USBD_Device, USBD_AUDIO_CLASS);
  
  USBD_AUDIO_RegisterInterface(&USBD_Device, &USBD_AUDIO_fops);
  
  USBD_Start(&USBD_Device);
  
  /**
   * Idle Loop
   */
  while (1){}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
