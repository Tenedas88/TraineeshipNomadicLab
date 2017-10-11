#include "UsbHidFeeRTOS.h"
#include "usbd_core.h"
#include "usbd_hid.h"
#include "usbd_desc.h"

static USBD_HandleTypeDef USBD_Device;

void MouseInit(){

	  /**
	   * USB Firmware Initialization
	   */

	  USBD_Init(&USBD_Device, &HID_Desc, 0);

	  USBD_RegisterClass(&USBD_Device, &USBD_HID);

	  USBD_Start(&USBD_Device);

}

void ButtonInit(FreeRTOS_USB_MOUSE_REPORT *report)
{report -> button = 0x00;}

void XInit(FreeRTOS_USB_MOUSE_REPORT *report){report -> X = 0;}

void YInit(FreeRTOS_USB_MOUSE_REPORT *report){report -> Y = 0;}

void ReportInit(FreeRTOS_USB_MOUSE_REPORT *report){
	ButtonInit(report);
	XInit(report);
	YInit(report);
}

void Click(FreeRTOS_USB_MOUSE_REPORT *report){
	report -> button = 0x01;
}

void DeClick(FreeRTOS_USB_MOUSE_REPORT *report){
	report -> button = 0x00;
}

void Xmove(FreeRTOS_USB_MOUSE_REPORT *report, int8_t distance){
	report -> X = STEP * distance;
}

void Ymove(FreeRTOS_USB_MOUSE_REPORT *report, int8_t distance){
	report -> Y = STEP * distance;
}


void SendReport(FreeRTOS_USB_MOUSE_REPORT *report){
	USBD_HID_SendReport (&USBD_Device, (uint8_t*)report, 3);
}
