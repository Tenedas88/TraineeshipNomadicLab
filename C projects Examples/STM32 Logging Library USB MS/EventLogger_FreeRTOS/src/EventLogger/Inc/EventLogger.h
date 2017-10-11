 /******************************************************************************
 * @file    cal_def.h
 * @author  Gruppo 2 Sistemi Embedded
 * @version V1.0
 * @brief   EventLogger
 ******************************************************************************/
#ifndef EVENTLOGGER_INC_EVENTLOGGER_H_
#define EVENTLOGGER_INC_EVENTLOGGER_H_

/**
 * @addtogroup EventLogger_Conf
 * @{
 */

/**
 * @addtogroup EventLogger Defines
 * @{
 */

#include "EventLogger_conf.h"
#if (LOG_USE_OS == 1 )
#include "cmsis_os.h"
#endif

/* Event Facilities Defines*/
#define APPLICATION 1
#define NETWORK		APPLICATION+1
#define DATALINK	NETWORK+1
#define SECURITY	DATALINK+1
#define MAINTENCE	SECURITY+1

/* Event Severity Defines*/
#define ALERT			1
#define CRITICAL		ALERT+1
#define ERROR			CRITICAL+1
#define WARNING			ERROR+1
#define NOTICE			WARNING+1
#define INFORMATIONAL	NOTICE+1
#define DEBUGGING		INFORMATIONAL+1
#ifndef LOG_LEVEL
#define LOG_LEVEL		DEBUGGING
#endif

/* Event Description Defines */

#define LOG_INT		0
#define	LOG_STRING	LOG_INT+1
#define LOG_END 	LOG_STRING+1

/* EventLogger Defines */
#if (LOG_USE_BUFFERING == 1) && (LOG_USE_OS == 1)
#ifndef LOGTASKPRIO
#define LOGTASKPRIO osPriorityLow
#endif
#ifndef LOGTASKSTACK
#define LOGTASKSTACK (8 * configMINIMAL_STACK_SIZE)
#endif
#ifndef LOGTASKPERIOD
#define LOGTASKPERIOD	10
#endif
#endif
#ifndef LOG_MAX_DIM
#define LOG_MAX_DIM 	128
#endif
#ifndef LOGFILE_DEFAULT
#define LOGFILE_DEFAULT "Log.txt"
#endif

typedef enum
{
	LOG_OK = 0,
	LOG_BUSY,
	LOG_STORAGE_INIT_FAILED,
	LOG_FILESYSTEM_INIT_FAILED,
	LOG_FILE_OPEN_FAILED,
	LOG_FILE_ACCESS_FAILED,
	LOG_BUFFER_FULL,
	LOG_FILE_WRITE_FAILED,
	LOG_FILE_CLOSE_FAILED,
	LOG_FILESYSTEM_DEINIT_FAILED,
	LOG_STORAGE_DEINIT_FAILED,
	LOG_INVALID_TYPE
} EventLogger_Status_TypeDef;

typedef struct{
	char		LogString[LOG_MAX_DIM];
}EventLogger_Log_TypeDef;

struct _EventLogger_Handle_TypeDef;

typedef struct
{
  EventLogger_Status_TypeDef  (*Init)        (struct _EventLogger_Handle_TypeDef *plog);
  EventLogger_Status_TypeDef  (*DeInit)      (struct _EventLogger_Handle_TypeDef *plog);
  EventLogger_Status_TypeDef  (*WriteLog)    (struct _EventLogger_Handle_TypeDef *plog);
} EventLogger_Interface_TypeDef;

typedef struct _EventLogger_Handle_TypeDef{
	char*								LogFile;
	EventLogger_Status_TypeDef			LogStatus;
	EventLogger_Interface_TypeDef*		Interface;
	EventLogger_Log_TypeDef    			*pLogData;
#if (LOG_USE_OS == 1)
	osMessageQId          os_event;
	osThreadId            thread;
#endif
} EventLogger_Handle_TypeDef;

/**
 * @}
 */

/* Exported Variables */
EventLogger_Handle_TypeDef LOG_HANDLE;
extern EventLogger_Handle_TypeDef LOG_HANDLE;
extern EventLogger_Interface_TypeDef LOG_Interface;

/**
 * @addtogroup EventLogger Interface
 * @{
 */
/* Interface */
EventLogger_Status_TypeDef EventLogger_Init(EventLogger_Handle_TypeDef *plog, EventLogger_Interface_TypeDef *ploginterface);
EventLogger_Status_TypeDef EventLogger_DeInit(EventLogger_Handle_TypeDef *plog);
EventLogger_Status_TypeDef EventLogger_LogEvent(EventLogger_Handle_TypeDef *plog, uint Facility,
												uint Severity, uint node_id, char* function_id,
												...);
/**
 * @}
 */
/**
 * @}
 */

#endif /* EVENTLOGGER_INC_EVENTLOGGER_H_ */
