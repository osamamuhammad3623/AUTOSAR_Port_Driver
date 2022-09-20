 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
*                              Port Pin Modes                                   *
*******************************************************************************/
#define PORT_PIN_MODE_ADC		(0U)
#define PORT_PIN_MODE_UART		(1U)
#define PORT_PIN_MODE_SSI		(2U)
#define PORT_PIN_MODE_I2C		(3U) 
#define PORT_PIN_MODE_M0PWM 	(4U)
#define PORT_PIN_MODE_M0FAULT 	(4U)
#define PORT_PIN_MODE_M1PWM 	(5U)
#define PORT_PIN_MODE_GPT   	(7U)
#define PORT_PIN_MODE_CAN		(8U)
#define PORT_PIN_MODE_USB		(8U)
#define PORT_PIN_MODE_NMI		(8U)
#define PORT_PIN_MODE_DIO		(9U)

/*******************************************************************************
*                              Pre-Compile configurations                      *
*******************************************************************************/
/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/* Pre-compile option for SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)

/* Pre-compile option for SetPinMode API */
#define PORT_SET_PIN_MODE_API               (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API               (STD_ON)

/* Parameter to indicate if the direction is changeable on a port pin during runtime */
#define PORT_PIN_DIRECTION_CHANGEABLE       (STD_ON)

/* Pre-compile option for The initial direction of the pin */
#define PORT_PIN_DIRECTION                  (PORT_PIN_IN)

/* Parameter to indicate if the mode is changeable on a port pin during runtime */
#define PORT_PIN_MODE_CHANGEABLE            (STD_ON)

/* the initial Port pin mode */
#define PORT_PIN_INITIAL_MODE               (PORT_PIN_MODE_DIO)

/* Number of the configured Port Channels */
/* 43 pins - 4 JTAG pins for TM4C123 (PC0-PC3) */
#define PORT_PINS_NUMBER                     (39U)

/* Ports index */
#define PORTA           (uint8)0
#define PORTB           (uint8)1
#define PORTC           (uint8)2
#define PORTD           (uint8)3
#define PORTE           (uint8)4
#define PORTF           (uint8)5

/* Pin index */
#define PIN0_INDEX      (uint8)0
#define PIN1_INDEX      (uint8)1
#define PIN2_INDEX      (uint8)2
#define PIN3_INDEX      (uint8)3
#define PIN4_INDEX      (uint8)4
#define PIN5_INDEX      (uint8)5
#define PIN6_INDEX      (uint8)6
#define PIN7_INDEX      (uint8)7

#endif /* PORT_CFG_H */
