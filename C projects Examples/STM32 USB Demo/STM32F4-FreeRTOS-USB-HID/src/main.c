//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------
/*
 * @author  Davide Piscopo, Andrea Primativo
 * @date    4-June-2015
 *
 * @brief   Questo Main di esempio utilizza la libreria UsbHidFreeRTOS.h e event_groups.h
 *          L'esempio è costituito da 3 task
 *          vClickButton: gestione della pressione del bottone
 *          vMoveYAxis: gestione del movimento del cursore sull'asse Y
 *          vMoveXAxis: gestione del movimento del cursore sull'asse X
 *
 *          I task si sincronizzano nell'ordine ciclico:
 *
 *          | -> vClickButton -> vMoveYAxis -> vMoveXAxis -> |
 *
 *          Generando la sequenza di operazioni:
 *
 *          | -> Click-> Sposta a destra -> Sposta in alto -> Rilascio -> Sposta a sinistra -> Sposta in basso -> |
 *
 *          La logica dei task può essere cambiata a seconda delle necessità e gestita in maniera
 *          completamente indipendente per ogni possibile campo del Hid-Report
 */

#define WAIT_CLICK (1 << 0)
#define WAIT_X (1 << 1)
#define WAIT_Y (1 << 2)

#include <stdio.h>
#include "diag/Trace.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"

#include "UsbHidFeeRTOS.h"

FreeRTOS_USB_MOUSE_REPORT Report;
EventGroupHandle_t MouseGroup;

// ----- main() ---------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


/*
 * Alterna movimenti Su-Giu
 */
static void vMoveYAxis(void){


	uint8_t state = 0;
	uint8_t direction = 0;

	while(1){
	    xEventGroupWaitBits( MouseGroup,
	                WAIT_Y,
	                pdTRUE,
	                pdTRUE,
	                0xFFFF );

	    if(state == 0){
	    	direction = -1;
	    	state = 1;
	    }
	    else{
	    	direction = 1;
	    	state = 0;
	    }

	    Xmove(&Report, 0);

	    for(int i = 0; i <1000; i++){
	    Ymove(&Report, direction);
	    SendReport(&Report);
	    vTaskDelay(1);
	    }

		xEventGroupSetBits(MouseGroup, WAIT_CLICK);
		vTaskDelay(0);
	}

}
/*
 * Alterna movimenti Destra-Sinistra
 */
static void vMoveXAxis(void){

	uint8_t state = 0;
	uint8_t direction = 0;

	while(1){
	    xEventGroupWaitBits( MouseGroup,
	                WAIT_X,
	                pdTRUE,
	                pdTRUE,
	                0xFFFF );

	    if(state == 0){
	    	direction = -1;
	    	state = 1;
	    }
	    else{
	    	direction = 1;
	    	state = 0;
	    }

	    Ymove(&Report, 0);

	    for(int i = 0; i <1000; i++){
	    Xmove(&Report, direction);
	    SendReport(&Report);
	    vTaskDelay(1);
	    }

		xEventGroupSetBits(MouseGroup, WAIT_Y);
		vTaskDelay(0);
	}

}
/*
 * Alterna Click-Rilascio
 */
static void vClickButton(void){

	uint8_t state = 0;

	while(1){
	    xEventGroupWaitBits( MouseGroup,
	                WAIT_CLICK,
	                pdTRUE,
	                pdTRUE,
	                0xFFFF );

	    if(state == 0){
	    	Click(&Report);
	    	state = 1;}
	    else{
	    	DeClick(&Report);
	    	state = 0;}

	    SendReport(&Report);

		xEventGroupSetBits(MouseGroup, WAIT_X);
		vTaskDelay(0);
	}

}

int
main(int argc, char* argv[])
{
	/*
	 * Inizializzazione
	 */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	MouseGroup = xEventGroupCreate();
	ReportInit(&Report);
	MouseInit(&Report);
	xEventGroupSetBits(MouseGroup, WAIT_CLICK);
	/*
	 * Creazione dei Task
	 */
	xTaskCreate(vMoveXAxis, "XAxis", 200, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vMoveYAxis, "YAxis", 200, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vClickButton, "Clicker", 200, NULL, tskIDLE_PRIORITY, NULL);
	/*
	 * Avvio Scheduler
	 */
	vTaskStartScheduler();
	/*
	 * Idle Loop
	 */
	while(1){}
}

void vApplicationTickHook(void){
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
