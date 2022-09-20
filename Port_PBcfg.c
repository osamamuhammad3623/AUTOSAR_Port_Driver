 /******************************************************************************
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 ******************************************************************************/

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

#include "Port.h"

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {

	PORTA , PIN0_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN1_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN2_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN3_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN5_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN6_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTA , PIN7_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,

	PORTB , PIN0_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN1_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN2_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN3_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN5_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN6_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTB , PIN7_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,

	PORTC , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTC , PIN5_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTC , PIN6_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTC , PIN7_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,

	PORTD , PIN0_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN1_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN2_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN3_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN5_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN6_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTD , PIN7_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,

	PORTE , PIN0_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTE , PIN1_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTE , PIN2_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTE , PIN3_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTE , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTE , PIN5_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,

	PORTF , PIN0_INDEX, PORT_PIN_IN, Pull_Up, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTF , PIN1_INDEX, PORT_PIN_OUT, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTF , PIN2_INDEX, PORT_PIN_OUT, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTF , PIN3_INDEX, PORT_PIN_OUT, OFF, STD_HIGH , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable,
	PORTF , PIN4_INDEX, PORT_PIN_IN, OFF, STD_LOW , PORT_PIN_MODE_DIO , Direction_Changeable, Mode_Changeable

};