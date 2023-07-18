
/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_ctlreq.h"
#include "usbd_cdc_msc.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_CDC
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_CDC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_CDC_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_CDC_Private_Macros
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_CDC_Private_FunctionPrototypes
  * @{
  */
static uint8_t  *USBD_CDC_MSC_GetFSCfgDesc(uint16_t *length);

static uint8_t  *USBD_CDC_MSC_GetHSCfgDesc(uint16_t *length);

static uint8_t  *USBD_CDC_MSC_GetOtherSpeedCfgDesc(uint16_t *length);

static uint8_t  *USBD_CDC_MSC_GetOtherSpeedCfgDesc(uint16_t *length);

uint8_t  *USBD_CDC_MSC_GetDeviceQualifierDescriptor(uint16_t *length);

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_CDC_MSC_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/**
  * @}
  */

/** @defgroup USBD_CDC_Private_Variables
  * @{
  */

static uint8_t  USBD_CDC_MSC_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  uint8_t ret;
  /* MSC initialization */
  ret = USBD_MSC_Init (pdev, cfgidx);
  if(ret != USBD_OK)
          return ret;

  /* CDC initialization */
  ret = USBD_CDC_Init (pdev, cfgidx);
  if(ret != USBD_OK)
          return ret;

  return USBD_OK;
}
static uint8_t  USBD_CDC_MSC_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* CDC De-initialization */
  USBD_CDC_DeInit(pdev, cfgidx);
  /* MSC De-initialization */
  USBD_MSC_DeInit(pdev, cfgidx);
  return USBD_OK;
}
static uint8_t  USBD_CDC_MSC_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  // Route requests to MSC interface or its endpoints to MSC class implementaion
  if(((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_INTERFACE && req->wIndex == MSC_INTERFACE_INDEX) ||
          ((req->bmRequest & USB_REQ_RECIPIENT_MASK) == USB_REQ_RECIPIENT_ENDPOINT && ((req->wIndex & 0x7F) == MSC_EPOUT_ADDR)))
  {
          return USBD_MSC_Setup(pdev, req);
  }
  return USBD_CDC_Setup(pdev, req);
}
static uint8_t  USBD_CDC_MSC_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  if(epnum == MSC_EPOUT_ADDR)
          return USBD_MSC_DataIn(pdev, epnum);
  return USBD_CDC_DataIn(pdev, epnum);
}
static uint8_t  USBD_CDC_MSC_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  if(epnum == MSC_EPOUT_ADDR)
          return USBD_MSC_DataOut(pdev, epnum);
  return USBD_CDC_DataOut(pdev, epnum);
}
/* CDC interface class callbacks structure */
USBD_ClassTypeDef  USBD_CDC_MSC =
{
  USBD_CDC_MSC_Init,
  USBD_CDC_MSC_DeInit,
  USBD_CDC_MSC_Setup,
  NULL,                 /* EP0_TxSent, */
  USBD_CDC_EP0_RxReady,
  USBD_CDC_MSC_DataIn,
  USBD_CDC_MSC_DataOut,
  NULL,
  NULL,
  NULL,
  USBD_CDC_MSC_GetHSCfgDesc,
  USBD_CDC_MSC_GetFSCfgDesc,
  USBD_CDC_MSC_GetOtherSpeedCfgDesc,
  USBD_CDC_MSC_GetDeviceQualifierDescriptor,
};

/* USB CDC_MSC device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_CDC_MSC_CfgHSDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  USB_CDC_MSC_CONFIG_DESC_SIZ,                /* wTotalLength:no of returned bytes */
  0x00,
  0x03,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x04,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */
  /*---------------------------------------------------------------------------*/

/********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,   /* bDescriptorType: */
  MSC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
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
  /*---------------------------------------------------------------------------*/
  /******** IAD should be positioned just before the CDC interfaces ******
                               	IAD to associate the two CDC interfaces */
	0x08, /* bLength */
	0x0B, /* bDescriptorType */
	CDC_INTERFACE_INDEX, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	0x02, /* bFunctionClass */
	0x02, /* bFunctionSubClass */
	0x01, /* bFunctionProtocol */
	0x00, /* iFunction (Index of string descriptor describing this function) */
	/* 08 bytes */

  /*---------------------------------------------------------------------------*/
  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  CDC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x01,   /* iInterface: */

  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  CDC_INTERFACE_INDEX + 1,   /* bDataInterface: 1 */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_INDEX,   /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_INDEX + 1,   /* bSlaveInterface0: Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  CDC_HS_BINTERVAL,                           /* bInterval: */
  /*---------------------------------------------------------------------------*/

  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  CDC_INTERFACE_INDEX + 1,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00                               /* bInterval: ignore for Bulk transfer */
  
  
} ;


/* USB CDC_MSC device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_CDC_MSC_CfgFSDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  USB_CDC_MSC_CONFIG_DESC_SIZ,                /* wTotalLength:no of returned bytes */
  0x00,
  0x03,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x02,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */
  /*---------------------------------------------------------------------------*/
/********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,   /* bDescriptorType: */
  MSC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
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

  /*---------------------------------------------------------------------------*/
  /******** IAD should be positioned just before the CDC interfaces ******
                               	IAD to associate the two CDC interfaces */
	0x08, /* bLength */
	0x0B, /* bDescriptorType */
	CDC_INTERFACE_INDEX, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	0x02, /* bFunctionClass */
	0x02, /* bFunctionSubClass */
	0x01, /* bFunctionProtocol */
	0x00, /* iFunction (Index of string descriptor describing this function) */
	/* 08 bytes */
  /*---------------------------------------------------------------------------*/

  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  CDC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x01,   /* iInterface: */

  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  CDC_INTERFACE_INDEX + 1,   /* bDataInterface: 1 */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_INDEX,   /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_INDEX + 1,   /* bSlaveInterface0: Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  CDC_FS_BINTERVAL,                           /* bInterval: */
  /*---------------------------------------------------------------------------*/

  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  CDC_INTERFACE_INDEX + 1,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),
  0x00                               /* bInterval: ignore for Bulk transfer */

} ;

__ALIGN_BEGIN uint8_t USBD_CDC_MSC_OtherSpeedCfgDesc[USB_CDC_MSC_CONFIG_DESC_SIZ] __ALIGN_END =
{
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,
  USB_CDC_MSC_CONFIG_DESC_SIZ,
  0x00,
  0x03,   /* bNumInterfaces: 2 interfaces */
  0x01,   /* bConfigurationValue: */
  0x04,   /* iConfiguration: */
  0xC0,   /* bmAttributes: */
  0x32,   /* MaxPower 100 mA */
  /*---------------------------------------------------------------------------*/
 
/********************  Mass Storage interface ********************/
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,   /* bDescriptorType: */
  MSC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
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
  /*---------------------------------------------------------------------------*/
  /******** IAD should be positioned just before the CDC interfaces ******
                               	IAD to associate the two CDC interfaces */
	0x08, /* bLength */
	0x0B, /* bDescriptorType */
	CDC_INTERFACE_INDEX, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	0x02, /* bFunctionClass */
	0x02, /* bFunctionSubClass */
	0x01, /* bFunctionProtocol */
	0x00, /* iFunction (Index of string descriptor describing this function) */
	/* 08 bytes */

  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  CDC_INTERFACE_INDEX,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x01,   /* iInterface: */

  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  CDC_INTERFACE_INDEX + 1,   /* bDataInterface: 1 */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  CDC_INTERFACE_INDEX,   /* bMasterInterface: Communication class interface */
  CDC_INTERFACE_INDEX + 1,   /* bSlaveInterface0: Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,         /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  CDC_FS_BINTERVAL,                           /* bInterval: */

  /*---------------------------------------------------------------------------*/

  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  CDC_INTERFACE_INDEX + 1,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  0x40,                              /* wMaxPacketSize: */
  0x00,
  0x00,                              /* bInterval: ignore for Bulk transfer */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,     /* bDescriptorType: Endpoint */
  CDC_IN_EP,                        /* bEndpointAddress */
  0x02,                             /* bmAttributes: Bulk */
  0x40,                             /* wMaxPacketSize: */
  0x00,
  0x00                              /* bInterval */
  
 
};

/**
  * @}
  */

/** @defgroup USBD_CDC_Private_Functions
  * @{
  */


/**
  * @brief  USBD_CDC_MSC_GetFSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_CDC_MSC_GetFSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_CDC_MSC_CfgFSDesc);
  return USBD_CDC_MSC_CfgFSDesc;
}

/**
  * @brief  USBD_CDC_MSC_GetHSCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_CDC_MSC_GetHSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_CDC_MSC_CfgHSDesc);
  return USBD_CDC_MSC_CfgHSDesc;
}

/**
  * @brief  USBD_CDC_MSC_GetCfgDesc
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_CDC_MSC_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_CDC_MSC_OtherSpeedCfgDesc);
  return USBD_CDC_MSC_OtherSpeedCfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_CDC_MSC_GetDeviceQualifierDescriptor(uint16_t *length)
{
  *length = sizeof(USBD_CDC_MSC_DeviceQualifierDesc);
  return USBD_CDC_MSC_DeviceQualifierDesc;
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
