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
 *  \brief Board specific Buttons driver header for the Fletchtronics BUMBLEB.
 *  \copydetails Group_Buttons_BUMBLEB
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_BUMBLEB BUMBLEB
 *  \brief Board specific Buttons driver header for the Fletchtronics BUMBLEB.
 *
 *  Board specific buttons driver header for the Fletchtronics BUMBLEB (http://fletchtronics.net/bumble-b). The BUMBLEB
 *  third-party board does not include any on-board peripherals, but does have an officially recommended external peripheral
 *  layout for buttons, LEDs and a Joystick.
 *
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>BUTTONS_BUTTON1</td><td>HWB Button</td><td>Low</td><td>PORTD.7</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __BUTTONS_BUMBLEB_H__
#define __BUTTONS_BUMBLEB_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BUTTONS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the first button on the board. */
			//#define BUTTONS_BUTTONSEL      (1 << 7)
			//#define BUTTONS_BUTTONSTOP      (1 << 6)
			//#define BUTTONS_BUTTONBAS       (1 << 5)
			//#define BUTTONS_BUTTONDROITE    (1 << 4)
			//#define BUTTONS_BUTTONGAUCHE    (1 << 1)
			#define BUTTONS_BUTTONHAUT      (1 << 0)


		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Buttons_Init(void)
			{
			/*	DDRB  &= ~BUTTONS_BUTTONSEL;
				PORTB |=  BUTTONS_BUTTONSEL;
			
				DDRB  &= ~BUTTONS_BUTTONSTOP;
				PORTB |=  BUTTONS_BUTTONSTOP;

				DDRF  &= ~BUTTONS_BUTTONBAS;
				PORTF |=  BUTTONS_BUTTONBAS;

				DDRF  &= ~BUTTONS_BUTTONDROITE;
				PORTF |=  BUTTONS_BUTTONDROITE;

				DDRF  &= ~BUTTONS_BUTTONGAUCHE;
				PORTF |=  BUTTONS_BUTTONGAUCHE;
			*/
				DDRF  &= ~BUTTONS_BUTTONHAUT;
				PORTF |=  BUTTONS_BUTTONHAUT;
			

			}

			static inline void Buttons_Disable(void)
			{
		/*
				DDRB  &= ~BUTTONS_BUTTONSEL;
				PORTB &= ~BUTTONS_BUTTONSEL;
			
				DDRB  &= ~BUTTONS_BUTTONSTOP;
				PORTB &=  BUTTONS_BUTTONSTOP;

				DDRF  &= ~BUTTONS_BUTTONBAS;
				PORTF &=  BUTTONS_BUTTONBAS;

				DDRF  &= ~BUTTONS_BUTTONDROITE;
				PORTF &=  BUTTONS_BUTTONDROITE;

				DDRF  &= ~BUTTONS_BUTTONGAUCHE;
				PORTF &=  BUTTONS_BUTTONGAUCHE;
		*/
				DDRF  &= ~BUTTONS_BUTTONHAUT;
				PORTF &=  BUTTONS_BUTTONHAUT;
			

			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
				return ((PINF & BUTTONS_BUTTONHAUT) ^ BUTTONS_BUTTONHAUT);
			}
/*
			static inline uint8_t ButtonsS_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t ButtonsS_GetStatus(void)
			{
				return ((PINB & BUTTONS_BUTTONSEL) ^ BUTTONS_BUTTONSEL);
			}
*/
/*
			static inline uint8_t ButtonsH_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t ButtonsH_GetStatus(void)
			{
				return ((PINB & BUTTONS_BUTTONSTOP) ^ BUTTONS_BUTTONSTOP);
			}


			static inline uint8_t ButtonsBAS_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t ButtonsBAS_GetStatus(void)
			{
				return ((PINF & BUTTONS_BUTTONBAS) ^ BUTTONS_BUTTONBAS);
			}


			static inline uint8_t ButtonsDROITE_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t ButtonsDROITE_GetStatus(void)
			{
				return ((PINF & BUTTONS_BUTTONDROITE) ^ BUTTONS_BUTTONDROITE);
			}


			static inline uint8_t ButtonsGAUCHE_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t ButtonsGAUCHE_GetStatus(void)
			{
				return ((PINF & BUTTONS_BUTTONGAUCHE) ^ BUTTONS_BUTTONGAUCHE);
			}

*/


		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

