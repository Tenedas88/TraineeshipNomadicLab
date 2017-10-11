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

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

static void User_Process(void const *argument);

int
main(int argc, char* argv[])
{

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);
	EventLogger_Init(&LOG_HANDLE, &LOG_Interface);
	init_time(100);

	osThreadDef(User_Thread, User_Process, osPriorityNormal, 0, (2 * configMINIMAL_STACK_SIZE));
	osThreadCreate(osThread(User_Thread), NULL);


	/* Start scheduler */
	osKernelStart();

  // Infinite loop
  while (1)
    {
    }
}

static void User_Process(void const *argument){

	int log_written = 0;
	while(1){
		if(STOP == 0){
		if(log_written == 0){

			EventLogger_LogEvent(&LOG_HANDLE, APPLICATION, WARNING, 36, "send_msg()",
					LOG_INT, "SOURCE", 40,
					LOG_STRING, "MSG", "Ciao",
					LOG_END);
			log_written = 1;
		}
		else{
			log_written = 0;
		}
		}

		BSP_LED_Toggle(LED5);

		osDelay(10000);
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	STOP = 1;
	EventLogger_DeInit(&LOG_HANDLE);
}

void vApplicationTickHook(void){
	Time_SYSTICK_Callback();
}

void vApplicationIdleHook(void){
}

void vApplicationMallocFailedHook(void){
	taskDISABLE_INTERRUPTS();
	while(1){}
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName){
	(void) pcTaskName;
	(void) pxTask;

	taskDISABLE_INTERRUPTS();

	while(1){}
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
