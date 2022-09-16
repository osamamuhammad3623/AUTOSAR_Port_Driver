#include "Port.h"
#include "Port_Regs.h"
#include "Common_Macros.h"

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
		Port_Status = PORT_INITIALIZED;
		Port_PortPins = ConfigPtr->pins; /* address of the first Channels structure --> pins[0] */

		/* a pointer to indicate what port we will operate on  */
		volatile uint32* current_port = NULL_PTR;

		for(Port_PinType index = 0; index < PORT_PINS_NUMBER; index++){

			switch (ConfigPtr->pins[index].port_num)
			{
			case PORTA:
				current_port = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;
				break;
			case PORTB:
				current_port = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;
				break;
			case PORTC:
				current_port = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;
				break;
			case PORTD:
				current_port = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;
				break;
			case PORTE:
				current_port = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
				break;
			case PORTF:
				current_port = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
				break;
			default:
				break;
			}

			/* enable port clock */
			SYSCTL_REGCGC2_REG |= (1<<ConfigPtr->pins[index].port_num);
			uint8 dummy_delay=0; /* wait for 4 clk cycles till clock activation */

			if( ((Port_PortPins[index].port_num == 3) && (Port_PortPins[index].pin_num == 7)) || \
			 	((Port_PortPins[index].port_num == 5) && (Port_PortPins[index].pin_num == 0)) ) /* PD7 or PF0 */
			{
				*(volatile uint32 *)((volatile uint8 *)current_port + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;  /* unlock the GPIO-CR register */   
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_COMMIT_REG_OFFSET) , Port_PortPins[index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if( (Port_PortPins[index].port_num == 2) && \
					(Port_PortPins[index].pin_num <= 3) ) /* PC0 to PC3 */
			{
				/* Do Nothing ...  this is the JTAG pins */
			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}

			/* set the default pin direction first */
			if(PORT_PIN_DIRECTION == PORT_PIN_IN){
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DIR_REG_OFFSET),Port_PortPins[index].pin_num);

				if(Port_PortPins[index].internal_resistor_type == Pull_Up){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
				
				}else if (Port_PortPins[index].internal_resistor_type == Pull_Down){
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
				}
				else{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
				}

			}else if (PORT_PIN_DIRECTION == PORT_PIN_OUT){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DIR_REG_OFFSET),Port_PortPins[index].pin_num);

				if (Port_PortPins[index].init_value == STD_HIGH){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DATA_REG_OFFSET),Port_PortPins[index].pin_num);
					
				}else if (Port_PortPins[index].init_value == STD_LOW){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DATA_REG_OFFSET),Port_PortPins[index].pin_num);
				
				}else{
					/* do nothing */
				}

			}else{
				/* do nothing */
			}

			/* if pin direction is changeable, set the direction according to the pin configuration */
#if (PORT_PIN_DIRECTION_CHANGEABLE == STD_ON)
			if (Port_PortPins[index].dir_changeability == STD_ON){

				if(Port_PortPins[index].direction == PORT_PIN_IN){
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DIR_REG_OFFSET),Port_PortPins[index].pin_num);

					if(Port_PortPins[index].internal_resistor_type == Pull_Up){
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
					
					}else if (Port_PortPins[index].internal_resistor_type == Pull_Down){
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
					}
					else{
						/* Port_PortPins[index].internal_resistor_type == Off */
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[index].pin_num);
						CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[index].pin_num);
					}

				}else if (Port_PortPins[index].direction == PORT_PIN_OUT){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DIR_REG_OFFSET),Port_PortPins[index].pin_num);

					if (Port_PortPins[index].init_value == STD_HIGH){
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DATA_REG_OFFSET),Port_PortPins[index].pin_num);
						
					}else if (Port_PortPins[index].init_value == STD_LOW){
						SET_BIT(*(volatile uint32 *)((volatile uint8 *)current_port + PORT_DATA_REG_OFFSET),Port_PortPins[index].pin_num);
					
					}else{
						/* do nothing */
					}

				}else{
					/* do nothing */
				}

			}
			else{
				/* do nothing */
			}
#endif

			/* set the default/initial pin mode first */
				/* code here */
			

			/* if mode is changeable, set the mode according to pin configuration */
#if (PORT_PIN_MODE_CHANGEABLE == STD_ON)

#endif

		}

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

#if (PORT_PIN_DIRECTION_CHANGEABLE == STD_ON)
	if (Port_PortPins[Pin].dir_changeability == STD_ON){

		if(Direction == PORT_PIN_IN){
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_DIR_REG_OFFSET),Port_PortPins[Pin].pin_num);

			if(Port_PortPins[Pin].internal_resistor_type == Pull_Up){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[Pin].pin_num);
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[Pin].pin_num);
			
			}else if (Port_PortPins[Pin].internal_resistor_type == Pull_Down){
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[Pin].pin_num);
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[Pin].pin_num);
			}
			else{
				/* Port_PortPins[Pin].internal_resistor_type == Off */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[Pin].pin_num);
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[Pin].pin_num);
			}

		}else if (Direction == PORT_PIN_OUT){
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_DIR_REG_OFFSET),Port_PortPins[Pin].pin_num);

			if (Port_PortPins[Pin].init_value == STD_HIGH){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_DATA_REG_OFFSET),Port_PortPins[Pin].pin_num);
				
			}else if (Port_PortPins[Pin].init_value == STD_LOW){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[Pin].port_num + PORT_DATA_REG_OFFSET),Port_PortPins[Pin].pin_num);
			
			}else{
				/* do nothing */
			}

		}else{
			/* do nothing */
		}
	}else{
		/* do nothing */
	}

#endif /* (PORT_PIN_DIRECTION_CHANGEABLE == STD_ON) */
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

	for(int i=0; i < PORT_PINS_NUMBER; i++){

		if(Port_PortPins[i].direction == PORT_PIN_IN){
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_DIR_REG_OFFSET),Port_PortPins[i].pin_num);

			if(Port_PortPins[i].internal_resistor_type == Pull_Up){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[i].pin_num);
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[i].pin_num);
			
			}else if (Port_PortPins[i].internal_resistor_type == Pull_Down){
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[i].pin_num);
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[i].pin_num);
			}
			else{
				/* Port_PortPins[i].internal_resistor_type == Off */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_UP_REG_OFFSET ),Port_PortPins[i].pin_num);
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins[i].pin_num);
			}

		}else if (Port_PortPins[i].direction == PORT_PIN_OUT){
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_DIR_REG_OFFSET),Port_PortPins[i].pin_num);

			if (Port_PortPins[i].init_value == STD_HIGH){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_DATA_REG_OFFSET),Port_PortPins[i].pin_num);
				
			}else if (Port_PortPins[i].init_value == STD_LOW){
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_PortPins[i].port_num + PORT_DATA_REG_OFFSET),Port_PortPins[i].pin_num);
			
			}else{
				/* do nothing */
			}

		}else{
			/* do nothing */
		}
	}

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
	boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, 
		PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID, 
		PORT_E_UNINIT);
		error=TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/* check if pin mode is changeable */
	if (Port_PortPins[Pin].mode_changeability == Mode_Unchangeable){
		Det_ReportError(PORT_MODULE_ID, 
		PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID, 
		PORT_E_MODE_UNCHANGEABLE);
		error=TRUE;
	}else{
		/* No Action Required */
	}
#endif

}