/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Board specific LED driver header for the Fletchtronics BUMBLEB.
 *  \copydetails Group_LEDs_BUMBLEB
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_BUMBLEB BUMBLEB
 *  \brief Board specific LED driver header for the Fletchtronics BUMBLEB.
 *
 *  Board specific LED driver header for the Fletchtronics BUMBLEB (http://fletchtronics.net/bumble-b). The BUMBLEB
 *  third-party board does not include any on-board peripherals, but does have an officially recommended external
 *  peripheral layout for buttons, LEDs and a Joystick.
 *
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>N/A</td><td>User Supplied</td><td>High</td><td>PORTB.4</td></tr>
 *    <tr><td>LEDS_LED2</td><td>N/A</td><td>User Supplied</td><td>High</td><td>PORTB.5</td></tr>
 *    <tr><td>LEDS_LED3</td><td>N/A</td><td>User Supplied</td><td>High</td><td>PORTB.6</td></tr>
 *    <tr><td>LEDS_LED4</td><td>N/A</td><td>User Supplied</td><td>High</td><td>PORTB.7</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_BUMBLEB_H__
#define __LEDS_BUMBLEB_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        0x10			//(1 << 5)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        0x00			

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        0x01			

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        0x04			

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED5        0x02	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED6        0x08	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED7        0x08	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED8        0x20	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED9        0x20	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED10        0x40	

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED11        0x02	

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_D   (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4 | LEDS_LED5 | LEDS_LED6 )
			#define LEDS_ALL_B   (LEDS_LED7 | LEDS_LED8)
			#define LEDS_ALL_C   (LEDS_LED9 | LEDS_LED10)
			#define LEDS_ALL_E   (LEDS_LED11)


			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				DDRD  |=  LEDS_ALL_D; // tout en sortie (1)
				PORTD &= ~LEDS_ALL_D; // tout éteint (0)

				DDRB  |=  LEDS_ALL_B; 
				PORTB &= ~LEDS_ALL_B;  

				DDRC  |=  LEDS_ALL_C; 
				PORTC &= ~LEDS_ALL_C;  

				DDRE  |=  LEDS_ALL_E; 
				PORTE &= ~LEDS_ALL_E;  
			}

			static inline void LEDs_Disable(void)
			{
				DDRD  |= ~LEDS_ALL_D;
				PORTD &= ~LEDS_ALL_D; 

				DDRB  |= ~LEDS_ALL_B; 
				PORTB &= ~LEDS_ALL_B;  

				DDRC  |= ~LEDS_ALL_C; 
				PORTC &= ~LEDS_ALL_C;  

				DDRE  |= ~LEDS_ALL_E; 
				PORTE &= ~LEDS_ALL_E;  
			}

			static inline void LEDs_TurnOnLEDs_D(const uint8_t LedMask)
			{
				PORTD |= LedMask;
			}

			static inline void LEDs_TurnOnLEDs_B(const uint8_t LedMask)
			{
				PORTB |= LedMask;
			}

			static inline void LEDs_TurnOnLEDs_C(const uint8_t LedMask)
			{
				PORTC |= LedMask;
			}

			static inline void LEDs_TurnOnLEDs_E(const uint8_t LedMask)
			{
				PORTE |= LedMask;
			}





			static inline void LEDs_TurnOffLEDs_D(const uint8_t LedMask)
			{
				PORTD &= ~LedMask;
			}

				static inline void LEDs_TurnOffLEDs_B(const uint8_t LedMask)
			{
				PORTB &= ~LedMask;
			}

				static inline void LEDs_TurnOffLEDs_C(const uint8_t LedMask)
			{
				PORTC &= ~LedMask;
			}

				static inline void LEDs_TurnOffLEDs_E(const uint8_t LedMask)
			{
				PORTE &= ~LedMask;
			}





			static inline void LEDs_SetAllLEDs_D(const uint8_t LedMask)
			{
				PORTD = ((PORTD & ~LEDS_ALL_D) | LedMask);
			}

			static inline void LEDs_SetAllLEDs_B(const uint8_t LedMask)
			{
				PORTB = ((PORTB & ~LEDS_ALL_B) | LedMask);
			}

			static inline void LEDs_SetAllLEDs_C(const uint8_t LedMask)
			{
				PORTC = ((PORTC & ~LEDS_ALL_C) | LedMask);
			}

			static inline void LEDs_SetAllLEDs_E(const uint8_t LedMask)
			{
				PORTE = ((PORTE & ~LEDS_ALL_E) | LedMask);
			}




			static inline void LEDs_ChangeLEDs_D(const uint8_t LedMask,
			                                   const uint8_t ActiveMask)
			{
				PORTD = ((PORTD & ~LedMask) | ActiveMask);
			}

			static inline void LEDs_ChangeLEDs_B(const uint8_t LedMask,
			                                   const uint8_t ActiveMask)
			{
				PORTB = ((PORTB & ~LedMask) | ActiveMask);
			}

			static inline void LEDs_ChangeLEDs_C(const uint8_t LedMask,
			                                   const uint8_t ActiveMask)
			{
				PORTC = ((PORTC & ~LedMask) | ActiveMask);
			}

			static inline void LEDs_ChangeLEDs_E(const uint8_t LedMask,
			                                   const uint8_t ActiveMask)
			{
				PORTE = ((PORTE & ~LedMask) | ActiveMask);
			}



			static inline void LEDs_ToggleLEDs_D(const uint8_t LEDMask)
			{
				PIND  = LEDMask;
			}

			static inline void LEDs_ToggleLEDs_B(const uint8_t LEDMask)
			{
				PINB  = LEDMask;
			}

			static inline void LEDs_ToggleLEDs_C(const uint8_t LEDMask)
			{
				PINC  = LEDMask;
			}

			static inline void LEDs_ToggleLEDs_E(const uint8_t LEDMask)
			{
				PINE  = LEDMask;
			}



			static inline uint8_t LEDs_GetLEDs_D(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs_D(void)
			{
				return (PORTD & LEDS_ALL_D);
			}

			static inline uint8_t LEDs_GetLEDs_B(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs_B(void)
			{
				return (PORTB & LEDS_ALL_B);
			}

			static inline uint8_t LEDs_GetLEDs_C(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs_C(void)
			{
				return (PORTC & LEDS_ALL_C);
			}

			static inline uint8_t LEDs_GetLEDs_E(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs_E(void)
			{
				return (PORTE & LEDS_ALL_E);
			}


		#endif
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

