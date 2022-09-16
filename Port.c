#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_PinConfig * Port_PortPins = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;


/**********************************************************************
Service name:       Port_Init
Service ID[hex]:    0x00
Sync/Async:         Synchronous
Reentrancy:         Non Reentrant
Parameters (in):    ConfigPtr Pointer to configuration set.
Parameters (inout): None
Parameters (out):   None
Return value:       None
Description:        Initializes the Port Driver module.
**********************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID,
		PORT_INSTANCE_ID,
		PORT_INIT_SID,
		PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Port_Status       = PORT_INITIALIZED;
		Port_PortPins = ConfigPtr->pins; /* address of the first Channels structure --> pins[0] */
	}
}


/**********************************************************************
Service name:       Port_SetPinDirection
Service ID[hex]:    0x01
Sync/Async:         Synchronous
Reentrancy:         Reentrant
Parameters (in):    Pin - Port Pin number,
                    Direction - Port Pin Direction
Parameters (inout): None
Parameters (out):   None
Return value:       None
Description:        Sets the port pin direction
**********************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, 
		PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID, 
		PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
#endif
}
#endif /* PORT_SET_PIN_DIRECTION_API == STD_ON */


/**********************************************************************
Service name:       Port_RefreshPortDirection
Service ID[hex]:    0x02
Sync/Async:         Synchronous
Reentrancy:         Non Reentrant
Parameters (in):    None
Parameters (inout): None
Parameters (out):   None
Return value:       None
Description:        Refreshes port direction.
**********************************************************************/
void Port_RefreshPortDirection(void){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, 
		PORT_INSTANCE_ID,
		PORT_REFRESH_PIN_DIRECTION_SID, 
		PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
#endif

}


/**********************************************************************
Service name:       Port_GetVersionInfo
Service ID[hex]:    0x03
Sync/Async:         Synchronous
Reentrancy:         Non Reentrant
Parameters (in):    None
Parameters (inout): None
Parameters (out):   versioninfo - Pointer to where to store the version information of this module.
Return value:       None
Description:        Returns the version information of this module.
**********************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID,
                        PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif


/**********************************************************************
Service name:       Port_SetPinMode
Service ID[hex]:    0x04
Sync/Async:         Synchronous
Reentrancy:         Reentrant
Parameters (in):    Pin - Port pin ID number,
                    Mode - New Port Pin mode to be set on port pin.
Parameters (inout): None
Parameters (out):   None
Return value:       None
Description:        Sets the port pin mode.
**********************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, 
		PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID, 
		PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}
#endif

}