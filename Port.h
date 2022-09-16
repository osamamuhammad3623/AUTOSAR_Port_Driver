 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 ******************************************************************************/
#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * assuming random Id .. */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
******************************************************************************/
/* Service ID for PORT init */
#define PORT_INIT_SID                   (uint8)0x00

/* Service ID for PORT set pin direction */
#define PORT_SET_PIN_DIRECTION_SID      (uint8)0x01

/* Service ID for PORT refresh pin direction */
#define PORT_REFRESH_PIN_DIRECTION_SID  (uint8)0x02

/* Service ID for PORT get version info */
#define PORT_GET_VERSION_INFO_SID       (uint8)0x03

/* Service ID for PORT set pin mode */
#define PORT_SET_PIN_MODE_SID           (uint8)0x04


/*******************************************************************************
 *                      DET Error Codes                                        *
*******************************************************************************/
/* DET error if Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                0x0A

/* DET error if Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE   0x0B

/* DET error if API Port_Init service is called with wrong parameter */
#define PORT_E_PARAM_CONFIG             0x0C

/* DET error if API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE       0x0D
#define PORT_E_MODE_UNCHANGEABLE        0x0E

/* DET error if API service called without module initialization */
#define PORT_E_UNINIT                   0x0F

/* DET error if APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER            0x10


/*******************************************************************************
 *                              Module Data Types                              *
*******************************************************************************/
/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinDirectionType used by the PORT APIs */
typedef enum{
  PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/* Type definition for Port_InternalResistorType used by the Port APIs */
typedef enum{
  OFF, Pull_Up, Pull_Down 
}Port_InternalResistorType;

/* Type definition to indicate if pin direction can change during runtime */
typedef enum{
  Direction_Changeable, Direction_Unchangeable
}Port_PinDirectionChangeability;

/* Type definition to indicate if pin mode can change during runtime */
typedef enum{
  Mode_Changeable, Mode_Unchangeable
}Port_ModeChangeability;

/* Structure required for initializing a pin:
  1. Port number
  2. Pin number
  3. Pin direction (input/output)
  4. Internal resistor type (off, pull up or pull down)
  5. Pin initial value (Low/High)
  6. Pin mode (DIO, ADC, UART, CAN, etc..)
  7. Pin direction Changeability
  8. Pin mode Changeability
*/
typedef struct
{
  uint8 port_num;
  uint8 pin_num;
  Port_PinDirectionType direction;
  Port_InternalResistorType internal_resistor_type; 
  uint8 init_value;
  Port_PinModeType pin_mode;
  Port_PinDirectionChangeability dir_changeability;
  Port_ModeChangeability mode_changeability;
}Port_PinConfig;

/* Type of the external data structure containing the initialization data for this module. */
typedef struct 
{
  Port_PinConfig pins[PORT_PINS_NUMBER];
}Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
*******************************************************************************/
/* A function that Initializes the Port Driver module */
void Port_Init( const Port_ConfigType* ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* A function that Sets the port pin direction */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction); 
#endif

/* A function that Refreshes port direction */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/* A function that Returns the version information of this module */
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo); 
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* A function that Sets the port pin mode */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode);
#endif

/*******************************************************************************
 *                       External Variables                                    *
*******************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */