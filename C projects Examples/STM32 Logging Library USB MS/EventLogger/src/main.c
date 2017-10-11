//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

#include "EventLogger.h"
#include "clock.h"
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

void user_logic();
void setup();

int
main(int argc, char* argv[])
{
	setup();


		while (1)
		{

			USBH_Process(&hUSB_Host);

			switch(OK){
			case 0: OK=0;	break;
			case 1: user_logic(); break;
			default: break;


			}

		}
}

void user_logic(){


	while(1){

			BSP_LED_On(LED4);

			EventLogger_LogEvent(&LOG_HANDLE, APPLICATION, WARNING, 36, "send_msg()",
					LOG_INT, "SOURCE", 40,
					LOG_STRING, "MSG", "Ciao",
					LOG_END);

			HAL_Delay(3500);

			EventLogger_LogEvent(&LOG_HANDLE, NETWORK, INFORMATIONAL, 203834, "receive_ack()",
					LOG_STRING, "MSG", "Mamm't",
					LOG_END);

			BSP_LED_On(LED6);

			OK = 0;
			while(OK == 0)
				USBH_Process(&hUSB_Host);
	}
}

void setup(){

			init_time(100);
			BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
			BSP_LED_Init(LED3);
			BSP_LED_Init(LED4);
			BSP_LED_Init(LED5);
			BSP_LED_Init(LED6);

			EventLogger_Init(&LOG_HANDLE, &LOG_Interface);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	EventLogger_DeInit(&LOG_HANDLE);

	BSP_LED_On(LED5);
}

void HAL_SYSTICK_Callback(void)
{
	Time_SYSTICK_Callback();
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
