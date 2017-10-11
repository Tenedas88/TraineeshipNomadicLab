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
#include "EventLogger_conf.h"
#include "clock.h"

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#if (LOG_USE_OS == 1)
static void User_Process(void const *argument);
static void User_Process2(void const *argument);
#endif

int start, end, mean;
int time[100];
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

#if (LOG_USE_OS == 1)
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	osThreadDef(User_Thread2, User_Process2, osPriorityNormal, 0, 4*configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(User_Thread2), NULL);
	osThreadDef(User_Thread, User_Process, osPriorityHigh, 0, 4*configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(User_Thread), NULL);


	/* Start scheduler */
	osKernelStart();
#else
	int logs = 0;
	while(1){
		USBH_Process(&hUSB_Host);
		if((OK == 1) && (logs < 10)){
			BSP_LED_On(LED4);
			//if(((EventLogger_Handle_TypeDef *)argument)-> LogStatus != LOG_BUFFER_FULL){
			start = HAL_GetTick();
			EventLogger_LogEvent(&LOG_HANDLE, APPLICATION, WARNING, 36, "Task2",
					LOG_INT, "SOURCE", 40,
					LOG_STRING, "MSG", "Stattzitt",
					LOG_END);
			end = HAL_GetTick();
			time[logs] = end-start;
			logs = logs+1;
			//}
			BSP_LED_On(LED5);
		}
		if(logs == 10){
			for(int i = 0; i < 100; i++){
				mean += time[i];
				mean /= 100;
			}
			logs = 0;
		}
	}
#endif

  // Infinite loop
  while (1)
    {
    }
}

#if (LOG_USE_OS == 1)
static void User_Process(void const *argument){

	int logs = 0;
	while(1){
		if((OK == 1) && (logs < 10)){
			BSP_LED_On(LED4);
			//if(((EventLogger_Handle_TypeDef *)argument)-> LogStatus != LOG_BUFFER_FULL){
			start = HAL_GetTick();
			EventLogger_LogEvent(&LOG_HANDLE, APPLICATION, WARNING, 36, "Task 1",
					LOG_INT, "SOURCE", 40,
					LOG_STRING, "MSG", "Ciao",
					LOG_END);
			end = HAL_GetTick();
			time[logs] = end-start;
			logs = logs+1;
			//}
			BSP_LED_On(LED5);
		}
		if(logs == 10){
			/*for(int i = 0; i < 100; i++){
				mean += time[i];
				mean /= 100;
			}*/
			logs = 0;
			osDelay(1000);

		}
		osDelay(0);
	}

}

static void User_Process2(void const *argument){

	int logs = 0;
	while(1){
		if((OK == 1) && (logs < 10)){
			BSP_LED_On(LED4);
			//if(((EventLogger_Handle_TypeDef *)argument)-> LogStatus != LOG_BUFFER_FULL){
			start = HAL_GetTick();
			EventLogger_LogEvent(&LOG_HANDLE, APPLICATION, WARNING, 36, "Task2",
					LOG_INT, "SOURCE", 40,
					LOG_STRING, "MSG", "Stattzitt",
					LOG_END);
			end = HAL_GetTick();
			time[logs] = end-start;
			logs = logs+1;
			//}
			BSP_LED_On(LED5);
		}
		if(logs == 10){
			/*for(int i = 0; i < 100; i++){
				mean += time[i];
				mean /= 100;
			}*/
			logs = 0;
			osDelay(1000);
		}
		osDelay(1);
	}

}
#else
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	EventLogger_DeInit(&LOG_HANDLE);
	OK = 0;
	BSP_LED_Toggle(LED5);
}

#if (LOG_USE_OS == 1)
void vApplicationTickHook(void){
	IncTime();
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
#else
void HAL_SYSTICK_Callback(void)
{
	IncTime();
}
#endif

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
