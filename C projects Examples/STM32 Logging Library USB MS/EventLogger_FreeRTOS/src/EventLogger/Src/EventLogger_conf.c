 /******************************************************************************
 * @file    cal_def.h
 * @author  Gruppo 2 Sistemi Embedded
 * @version V1.0
 * @brief   EventLogger Configuration
 ******************************************************************************/

#include "EventLogger.h"
#include "stm32f4_discovery.h"

USBH_HandleTypeDef hUSB_Host;
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
char USBDISKPath[4];
FIL log_file;
int OK = 0;

static void CreateLogFile();
void USBH_LogProcess (USBH_HandleTypeDef *pHost, uint8_t vId);

EventLogger_Status_TypeDef  USBH_LogInit        (EventLogger_Handle_TypeDef *plog);
EventLogger_Status_TypeDef  USBH_LogDeInit      (EventLogger_Handle_TypeDef *plog);
EventLogger_Status_TypeDef  Write_FatFS      (EventLogger_Handle_TypeDef *plog);

EventLogger_Interface_TypeDef LOG_Interface =
{
  USBH_LogInit,
  USBH_LogDeInit,
  Write_FatFS
};

/**
 * @addtogroup EventLogger_Conf
 * @{
 */
/**
 * @addtogroup EventLogger Hardware Specific Functions
 * @{
 */
/**
 * @brief Funzione di inizializzazione specifica
 */
EventLogger_Status_TypeDef  USBH_LogInit(EventLogger_Handle_TypeDef *plog){
	if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) != 0){
		plog->LogStatus = LOG_STORAGE_INIT_FAILED;
		return plog->LogStatus;
	}
	else{
		plog->LogStatus = LOG_OK;
	}
	USBH_Init(&hUSB_Host, USBH_LogProcess, 0);
	USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);
	USBH_Start(&hUSB_Host);
	if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK){
		LOG_HANDLE.LogStatus = LOG_FILESYSTEM_INIT_FAILED;
	}

	return plog->LogStatus;
}

/**
 * @brief Funzione di Deinizializzazione specifica
 */
EventLogger_Status_TypeDef  USBH_LogDeInit(EventLogger_Handle_TypeDef *plog){

	EventLogger_LogEvent(plog, MAINTENCE, INFORMATIONAL, 203834, "Disk_Remove()",
			LOG_END);
	OK = 0;
	plog->LogStatus = LOG_OK;

	return plog->LogStatus;
}
/**
 * @brief Funzione di scrittura del log sull'hardware specifico
 */
EventLogger_Status_TypeDef  Write_FatFS      (EventLogger_Handle_TypeDef *plog){

	if(f_open(&log_file, plog->LogFile, FA_WRITE) != FR_OK){
		plog->LogStatus = LOG_FILE_OPEN_FAILED;
		return plog->LogStatus;
	}
	if(f_lseek(&log_file, f_size(&log_file)) != FR_OK){
		plog->LogStatus = LOG_FILE_ACCESS_FAILED;
		return plog->LogStatus;
	}
	f_printf(&log_file, "%s", plog->pLogData->LogString );

	f_close (&log_file);
	plog->LogStatus = LOG_OK;
	return plog->LogStatus;
}
/**
 * @}
 */
/**
 * @}
 */
void USBH_LogProcess (USBH_HandleTypeDef *pHost, uint8_t vId)

{
	switch (vId)

	{

	case HOST_USER_SELECT_CONFIGURATION:

		break;



	case HOST_USER_DISCONNECTION:
#if (LOG_USE_LED == 1)
		BSP_LED_On(LED3);
		BSP_LED_On(LED4);
		BSP_LED_On(LED5);
		BSP_LED_On(LED6);
#endif
#if	(LOG_USE_OS == 0)
		HAL_Delay(1000);
#endif
#if (LOG_USE_LED == 1)
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
#endif
		break;



	case HOST_USER_CLASS_ACTIVE:
		CreateLogFile();
		break;



	case HOST_USER_CONNECTION:
#if (LOG_USE_LED == 1)
		BSP_LED_On(LED3);
		BSP_LED_On(LED4);
		BSP_LED_On(LED5);
		BSP_LED_On(LED6);
#endif
#if	(LOG_USE_OS == 0)
		HAL_Delay(1000);
#endif
#if (LOG_USE_LED == 1)
		BSP_LED_Off(LED3);
		BSP_LED_Off(LED4);
		BSP_LED_Off(LED5);
		BSP_LED_Off(LED6);
#endif
		break;

	default:

		break;

	}
}

void CreateLogFile(){
	if(f_open(&log_file, LOG_HANDLE.LogFile, FA_OPEN_ALWAYS ) != FR_OK)
	{
		LOG_HANDLE.LogStatus = LOG_FILE_OPEN_FAILED;
	}
	else{
		if(f_close(&log_file) != FR_OK) LOG_HANDLE.LogStatus = LOG_FILE_CLOSE_FAILED;
		else {
			OK=1;
			LOG_HANDLE.LogStatus = LOG_OK;
		}
	}
}
