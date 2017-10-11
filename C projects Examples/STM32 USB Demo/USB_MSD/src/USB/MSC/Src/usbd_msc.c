/**
  ******************************************************************************
  * @file    usbd_msc.c
  * @author  MCD Application Team
  * @version V2.4.0
  * @date    28-February-2015
  * @brief   This file provides all the MSC core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                MSC Class  Description
  *          =================================================================== 
  *           This module manages the MSC class V1.0 following the "Universal 
  *           Serial Bus Mass Storage Class (MSC) Bulk-Only Transport (BOT) Version 1.0
  *           Sep. 31, 1999".
  *           This driver implements the following aspects of the specification:
  *             - Bulk-Only Transport protocol
  *             - Subclass : SCSI transparent command set (ref. SCSI Primary Commands - 3 (SPC-3))
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc.h"
#include "usbd_hid.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup MSC_CORE 
  * @brief Mass storage core module
  * @{
  */ 

/** @defgroup MSC_CORE_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup MSC_CORE_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup MSC_CORE_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup MSC_CORE_Private_FunctionPrototypes
  * @{
  */ 
uint8_t  USBD_MSC_Init (USBD_HandleTypeDef *pdev, 
                            uint8_t cfgidx);

uint8_t  USBD_MSC_DeInit (USBD_HandleTypeDef *pdev, 
                              uint8_t cfgidx);

uint8_t  USBD_MSC_Setup (USBD_HandleTypeDef *pdev, 
                             USBD_SetupReqTypedef *req);

uint8_t  USBD_MSC_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum);


uint8_t  USBD_MSC_DataOut (USBD_HandleTypeDef *pdev, 
                               uint8_t epnum);

uint8_t  *USBD_MSC_GetHSCfgDesc (uint16_t *length);

uint8_t  *USBD_MSC_GetFSCfgDesc (uint16_t *length);

uint8_t  *USBD_MSC_GetOtherSpeedCfgDesc (uint16_t *length);

uint8_t  *USBD_MSC_GetDeviceQualifierDescriptor (uint16_t *length);


/**
  * @}
  */ 


/** @defgroup MSC_CORE_Private_Variables
  * @{
  */ 

uint8_t DeInitNumb = 0;

USBD_ClassTypeDef  USBD_MSC = 
{
  USBD_MSC_Init,
  USBD_MSC_DeInit,
  USBD_MSC_Setup,
  NULL, /*EP0_TxSent*/  
  NULL, /*EP0_RxReady*/
  USBD_MSC_DataIn,
  USBD_MSC_DataOut,
  NULL, /*SOF */ 
  NULL,  
  NULL,     
  USBD_MSC_GetHSCfgDesc,
  USBD_MSC_GetFSCfgDesc,  
  USBD_MSC_GetOtherSpeedCfgDesc,
  USBD_MSC_GetDeviceQualifierDescriptor,
};

/* USB Mass storage device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
__ALIGN_BEGIN uint8_t USBD_MSC_CfgHSDesc[USB_MSC_CONFIG_DESC_SIZ+25]  __ALIGN_END =
{
  
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
  57,
  
  0x00,
  0x02,   /* bNumInterfaces: 1 interface */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x32,   /* MaxPower 100 mA */
  
  /********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  0x04,   /* bDescriptorType: */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints*/
  0x08,   /* bInterfaceClass: MSC Class */
  0x06,   /* bInterfaceSubClass : SCSI transparent*/
  0x50,   /* nInterfaceProtocol */
  0x05,          /* iInterface: */
  /********************  Mass Storage Endpoints ********************/
  0x07,   /*Endpoint descriptor length = 7*/
  0x05,   /*Endpoint descriptor type */
  MSC_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_HS_PACKET),
  HIBYTE(MSC_MAX_HS_PACKET),
  0x00,   /*Polling interval in milliseconds */
  
  0x07,   /*Endpoint descriptor length = 7 */
  0x05,   /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_HS_PACKET),
  HIBYTE(MSC_MAX_HS_PACKET),
  0x00,     /*Polling interval in milliseconds*/

  /************** Descriptor of Mouse interface ****************/
  /*Byte 32*/
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x01,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /*Byte 40*/
  /******************** Descriptor of Mouse HID ********************/
  /*Byte 41*/
  0x09,         /*bLength: HID Descriptor size*/
  0x21, 		/*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  50,			/*wItemLength: Total length of Report descriptor*/
  0x00,
  /*Byte 49*/
  /******************** Descriptor of Mouse endpoint ********************/
  /*Byte 50*/
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  0x04, /*wMaxPacketSize: 4 Byte max */
  0x00,
  0x0A          /*bInterval: Polling Interval (10 ms)*/
  /*Byte 56*/

};

/* USB Mass storage device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
uint8_t USBD_MSC_CfgFSDesc[USB_MSC_CONFIG_DESC_SIZ+25]  __ALIGN_END =
{
  
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
  57,
  
  0x00,
  0x02,   /* bNumInterfaces: 1 interface */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x32,   /* MaxPower 100 mA */
  
  /********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  0x04,   /* bDescriptorType: */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints*/
  0x08,   /* bInterfaceClass: MSC Class */
  0x06,   /* bInterfaceSubClass : SCSI transparent*/
  0x50,   /* nInterfaceProtocol */
  0x05,          /* iInterface:?? */
  /********************  Mass Storage Endpoints ********************/
  0x07,   /*Endpoint descriptor length = 7*/
  0x05,   /*Endpoint descriptor type */
  MSC_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x00,   /*Polling interval in milliseconds */
  
  0x07,   /*Endpoint descriptor length = 7 */
  0x05,   /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
  0x02,   /*Bulk endpoint type */
  LOBYTE(MSC_MAX_FS_PACKET),
  HIBYTE(MSC_MAX_FS_PACKET),
  0x00,     /*Polling interval in milliseconds*/
  /************** Descriptor of Mouse interface ****************/
  /*Byte 32*/
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x01,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /*Byte 40*/
  /******************** Descriptor of Mouse HID ********************/
  /*Byte 41*/
  0x09,         /*bLength: HID Descriptor size*/
  0x21, 		/*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  50,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /*Byte 49*/
  /******************** Descriptor of Mouse endpoint ********************/
  /*Byte 50*/
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  0x04, /*wMaxPacketSize: 4 Byte max */
  0x00,
  0x0A          /*bInterval: Polling Interval (10 ms)*/
  /*Byte 56*/
};

__ALIGN_BEGIN uint8_t USBD_MSC_OtherSpeedCfgDesc[USB_MSC_CONFIG_DESC_SIZ+25]   __ALIGN_END  =
{
  
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,   
  57,
  
  0x00,
  0x02,   /* bNumInterfaces: 1 interface */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x32,   /* MaxPower 100 mA */
  
  /********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  0x04,   /* bDescriptorType: */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints*/
  0x08,   /* bInterfaceClass: MSC Class */
  0x06,   /* bInterfaceSubClass : SCSI transparent command set*/
  0x50,   /* nInterfaceProtocol */
  0x05,          /* iInterface: */
  /********************  Mass Storage Endpoints ********************/
  0x07,   /*Endpoint descriptor length = 7*/
  0x05,   /*Endpoint descriptor type */
  MSC_EPIN_ADDR,   /*Endpoint address (IN, address 1) */
  0x02,   /*Bulk endpoint type */
  0x40,
  0x00,
  0x00,   /*Polling interval in milliseconds */
  
  0x07,   /*Endpoint descriptor length = 7 */
  0x05,   /*Endpoint descriptor type */
  MSC_EPOUT_ADDR,   /*Endpoint address (OUT, address 1) */
  0x02,   /*Bulk endpoint type */
  0x40,
  0x00,
  0x00,     /*Polling interval in milliseconds*/
  /************** Descriptor of Mouse interface ****************/
  /*Byte 32*/
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x01,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /*Byte 40*/
  /******************** Descriptor of Mouse HID ********************/
  /*Byte 41*/
  0x09,         /*bLength: HID Descriptor size*/
  0x21, 		/*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  50,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /*Byte 49*/
  /******************** Descriptor of Mouse endpoint ********************/
  /*Byte 50*/
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  0x04, /*wMaxPacketSize: 4 Byte max */
  0x00,
  0x0A          /*bInterval: Polling Interval (10 ms)*/
  /*Byte 56*/
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN  uint8_t USBD_MSC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  MSC_MAX_FS_PACKET,
  0x01,
  0x00,
};

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[9]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  0x21,			 /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  50,			/*wItemLength: Total length of Report descriptor*/
  0x00,
};


/**
 * @brief	Descrittore del Report composto da 3 byte cosi strutturati:
 *
 * 			MSB  LSB
 * 			0000000x| bit per il bottone
 * 			1-byte| Asse X
 * 			1-byte|	Asse Y
 */
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[50]  __ALIGN_END =
{
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x09,   0x01,

  0xA1,   0x00,
  0x05,   0x09,
  0x19,   0x01,
  0x29,   0x01,

  0x15,   0x00,
  0x25,   0x01,
  0x95,   0x01,
  0x75,   0x01,

  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x07,
  0x81,   0x01,

  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,

  0x15,   0x81,
  0x25,   0x7F,
  0x75,   0x08,
  0x95,   0x02,

  0x81,   0x06,
  0xC0,   0xc0
};

/**
  * @}
  */ 


/** @defgroup MSC_CORE_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_MSC_Init
  *         Initialize  the mass storage configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
uint8_t  USBD_MSC_Init (USBD_HandleTypeDef *pdev, 
                            uint8_t cfgidx)
{
  int16_t ret = 0;
  //if(cfgidx == 1){
  if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
  {
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   MSC_EPOUT_ADDR,
                   USBD_EP_TYPE_BULK,
                   MSC_MAX_HS_PACKET);
    
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   MSC_EPIN_ADDR,
                   USBD_EP_TYPE_BULK,
                   MSC_MAX_HS_PACKET);  
  }
  else
  {
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   MSC_EPOUT_ADDR,
                   USBD_EP_TYPE_BULK,
                   MSC_MAX_FS_PACKET);
    
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   MSC_EPIN_ADDR,
                   USBD_EP_TYPE_BULK,
                   MSC_MAX_FS_PACKET);  
  }
  
  USBD_LL_OpenEP(pdev,
                 HID_EPIN_ADDR,
                 USBD_EP_TYPE_INTR,
                 0x04);
  pdev->pClassData = USBD_malloc(sizeof (USBD_MSC_BOT_HandleTypeDef)+sizeof(USBD_HID_HandleTypeDef));

  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
	  ((USBD_HID_HandleTypeDef *)((pdev->pClassData)+sizeof (USBD_MSC_BOT_HandleTypeDef)))->state = HID_IDLE;
    /* Init the BOT  layer */
    MSC_BOT_Init(pdev);
    ret = 0;
  }
  //}
  //else if(cfgidx == 2){
	  /* Open EP IN */
	  /*USBD_LL_OpenEP(pdev,
	                 0x81,
	                 USBD_EP_TYPE_INTR,
	                 0x04);

	  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));

	  if(pdev->pClassData == NULL)
	  {
	    ret = 1;
	  }
	  else
	  {
	    ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
	  }*/
  //}
  return ret;
}

/**
  * @brief  USBD_MSC_DeInit
  *         DeInitilaize  the mass storage configuration
  * @param  pdev: device instance
  * @param  cfgidx: configuration index
  * @retval status
  */
uint8_t  USBD_MSC_DeInit (USBD_HandleTypeDef *pdev, 
                              uint8_t cfgidx)
{
	//if(cfgidx == 1){
  /* Close MSC EPs */
  USBD_LL_CloseEP(pdev,
                  MSC_EPOUT_ADDR);

  /* Open EP IN */
  USBD_LL_CloseEP(pdev,
                  MSC_EPIN_ADDR);

  USBD_LL_CloseEP(pdev, HID_EPIN_ADDR);


    /* De-Init the BOT layer */
  	 MSC_BOT_DeInit(pdev);
	//}
	//else if(cfgidx == 2){
		  /* Close HID EPs */

	//}

		    /* De-Init the BOT layer */
		  //MSC_BOT_DeInit(pdev);
  /* Free MSC Class Resources */
  if(pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData  = NULL;
  }

  return 0;
}
/**
* @brief  USBD_MSC_Setup
*         Handle the MSC specific requests
* @param  pdev: device instance
* @param  req: USB request
* @retval status
*/
uint8_t  USBD_MSC_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{

	  uint16_t len = 0;
	  uint8_t  *pbuf = NULL;
  USBD_MSC_BOT_HandleTypeDef     *hmsc = (USBD_MSC_BOT_HandleTypeDef*) pdev->pClassData;
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef *)((pdev->pClassData)+sizeof (USBD_MSC_BOT_HandleTypeDef));
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {

  /* Class request */
  case USB_REQ_TYPE_CLASS :
	  if((uint8_t)(req->wIndex) == 1){
    switch (req->bRequest)
    {
    	case HID_REQ_SET_PROTOCOL:
          hhid->Protocol = (uint8_t)(req->wValue);
          break;

     case HID_REQ_GET_PROTOCOL:
          USBD_CtlSendData (pdev,
                            (uint8_t *)&hhid->Protocol,
                            1);
          break;

        case HID_REQ_SET_IDLE:
          hhid->IdleState = (uint8_t)(req->wValue >> 8);
          break;

        case HID_REQ_GET_IDLE:
          USBD_CtlSendData (pdev,
                            (uint8_t *)&hhid->IdleState,
                            1);
          break;

        default:
           USBD_CtlError(pdev , req);
           return USBD_FAIL;
           break;
    }
	  }
    else if((uint8_t)(req->wIndex) == 0){
    	 switch (req->bRequest)
    	    {
             case BOT_GET_MAX_LUN :

        	if((req->wValue  == 0) &&
         (req->wLength == 1) &&
         ((req->bmRequest & 0x80) != 0x80))
        	{
        hmsc->max_lun = ((USBD_StorageTypeDef *)pdev->pUserData)->GetMaxLun();
        USBD_CtlSendData (pdev,
                          (uint8_t *)&hmsc->max_lun,
                          1);
      }
      else
      {
         USBD_CtlError(pdev , req);
         return USBD_FAIL; 
      }
      break;
      
    case BOT_RESET :
      if((req->wValue  == 0) && 
         (req->wLength == 0) &&
        ((req->bmRequest & 0x80) != 0x80))
      {      
         MSC_BOT_Reset(pdev);
      }
      else
      {
         USBD_CtlError(pdev , req);
         return USBD_FAIL; 
      }
      break;

    default:
       USBD_CtlError(pdev , req);
       return USBD_FAIL;
       break;
    }
    }
	  break;

  /* Interface & Endpoint request */
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {

    case USB_REQ_GET_DESCRIPTOR:
          if( req->wValue >> 8 == HID_REPORT_DESC)
          {
            len = MIN(HID_MOUSE_REPORT_DESC_SIZE , req->wLength);
            pbuf = HID_MOUSE_ReportDesc;
          }
          else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
          {
            pbuf = USBD_HID_Desc;
            len = MIN(USB_HID_DESC_SIZ , req->wLength);
          }

          USBD_CtlSendData (pdev,
                            pbuf,
                            len);

          break;

    case USB_REQ_GET_INTERFACE :
    	if((uint8_t)(req->wIndex) == 0){
      USBD_CtlSendData (pdev,
                        (uint8_t *)&hmsc->interface,
                        1);
    	}
    	else if((uint8_t)(req->wIndex) == 1){
    	      USBD_CtlSendData (pdev,
    	                        (uint8_t *)&hhid->AltSetting,
    	                        1);
    	}
      break;
      
    case USB_REQ_SET_INTERFACE :
    	if((uint8_t)(req->wIndex) == 0){
      hmsc->interface = (uint8_t)(req->wValue);
    	}
    	else if((uint8_t)(req->wIndex) == 1){
      hhid->AltSetting = (uint8_t)(req->wValue);
    	}
      break;
    
    case USB_REQ_CLEAR_FEATURE:
    	if((uint8_t)(req->wIndex) == 0){
      // Flush the FIFO and Clear the stall status
      USBD_LL_FlushEP(pdev, (uint8_t)req->wIndex);
      
      // Reactivate the EP
      USBD_LL_CloseEP (pdev , (uint8_t)req->wIndex);
      if((((uint8_t)req->wIndex) & 0x80) == 0x80)
      {
        if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
        {
          // Open EP IN
          USBD_LL_OpenEP(pdev,
                         MSC_EPIN_ADDR,
                         USBD_EP_TYPE_BULK,
                         MSC_MAX_HS_PACKET);  
        }
        else
        {   
          // Open EP IN
          USBD_LL_OpenEP(pdev,
                         MSC_EPIN_ADDR,
                         USBD_EP_TYPE_BULK,
                         MSC_MAX_FS_PACKET);  
        }
      }
      else
      {
        if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
        {
          // Open EP IN
          USBD_LL_OpenEP(pdev,
                         MSC_EPOUT_ADDR,
                         USBD_EP_TYPE_BULK,
                         MSC_MAX_HS_PACKET);  
        }
        else
        {   
          // Open EP IN
          USBD_LL_OpenEP(pdev,
                         MSC_EPOUT_ADDR,
                         USBD_EP_TYPE_BULK,
                         MSC_MAX_FS_PACKET);  
        }
      }
      
      // Handle BOT error
      MSC_BOT_CplClrFeature(pdev, (uint8_t)req->wIndex);
    	}
      break;
      
    }  
    break;
   
  default:
    break;
  }
  return 0;
}

/**
* @brief  USBD_MSC_DataIn
*         handle data IN Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_MSC_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
	if(epnum == (uint8_t)(HID_EPIN_ADDR & 0x7F)){
		((USBD_HID_HandleTypeDef *)((pdev->pClassData)+sizeof (USBD_MSC_BOT_HandleTypeDef)))->state = HID_IDLE;
	}
	else if(epnum == (uint8_t)(MSC_EPIN_ADDR & 0x7F))
		MSC_BOT_DataIn(pdev , epnum);
  return 0;
}

/**
* @brief  USBD_MSC_DataOut
*         handle data OUT Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_MSC_DataOut (USBD_HandleTypeDef *pdev, 
                               uint8_t epnum)
{
  MSC_BOT_DataOut(pdev , epnum);
  return 0;
}

/**
* @brief  USBD_MSC_GetHSCfgDesc 
*         return configuration descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_MSC_GetHSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MSC_CfgHSDesc);
  return USBD_MSC_CfgHSDesc;
}

/**
* @brief  USBD_MSC_GetFSCfgDesc 
*         return configuration descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_MSC_GetFSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MSC_CfgFSDesc);
  return USBD_MSC_CfgFSDesc;
}

/**
* @brief  USBD_MSC_GetOtherSpeedCfgDesc 
*         return other speed configuration descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_MSC_GetOtherSpeedCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_MSC_OtherSpeedCfgDesc);
  return USBD_MSC_OtherSpeedCfgDesc;
}
/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_MSC_GetDeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (USBD_MSC_DeviceQualifierDesc);
  return USBD_MSC_DeviceQualifierDesc;
}

/**
  * @brief  USBD_HID_SendReport
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USBD_HandleTypeDef  *pdev,
                                 uint8_t *report,
                                 uint16_t len)
{
	USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef *)((pdev->pClassData)+sizeof (USBD_MSC_BOT_HandleTypeDef));

  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    if(hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit (pdev,
                        HID_EPIN_ADDR,
                        report,
                        len);
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetPollingInterval
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0;

  /* HIGH-speed endpoints */
  if(pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers.
    Values between 1..16 are allowed. Values correspond to interval
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1 <<(HID_HS_BINTERVAL - 1)))/8);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }

  return ((uint32_t)(polling_interval));
}

/**
* @brief  USBD_MSC_RegisterStorage
* @param  fops: storage callback
* @retval status
*/
uint8_t  USBD_MSC_RegisterStorage  (USBD_HandleTypeDef   *pdev, 
                                    USBD_StorageTypeDef *fops)
{
  if(fops != NULL)
  {
    pdev->pUserData= fops;
  }
  return 0;
}

/**
  * @}
  */ 


/**
  * @}
  */ 


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
