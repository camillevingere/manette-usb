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
 *
 *  Main source file for the Joystick demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Manette.h"


/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Joystick_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_Joystick,
				.ReportINEndpoint             =
					{
						.Address              = JOYSTICK_EPADDR,
						.Size                 = JOYSTICK_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs_D(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_B(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_C(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_E(LEDMASK_USB_NOTREADY);

	GlobalInterruptEnable();

	for (;;)
	{
		HID_Device_USBTask(&Joystick_HID_Interface);
		USB_USBTask();
		EndpointOut_LED();
		EndpointOut_Vibreur();
		HID_Task();

	}
}


/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

	/* Hardware Initialization */
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	USB_Init();
}


/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup HID Report Endpoints */
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(ENDPOINT_OUT_EPADDR_1, EP_TYPE_INTERRUPT, EPSIZE_2_octets, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(ENDPOINT_OUT_EPADDR_2, EP_TYPE_INTERRUPT, EPSIZE_1_octet, 1);

	/* Turn on Start-of-Frame events for tracking HID report period expiry */
	USB_Device_EnableSOFEvents();

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs_D(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
	LEDs_SetAllLEDs_B(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
	LEDs_SetAllLEDs_C(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
	LEDs_SetAllLEDs_E(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

void ProcessLEDReport(const uint16_t LEDReport)
{
	uint16_t LEDMask = LEDS_LED2;

	/*if (LEDReport & HID_KEYBOARD_LED_NUMLOCK)
	  LEDMask |= LEDS_LED1;

	if (LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
	  LEDMask |= LEDS_LED3;

	if (LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
	  LEDMask |= LEDS_LED4;*/

	if(LEDReport == 0x0001){
        LEDMask |= LEDS_LED1;
    }
    if(LEDReport == 0x0002){
        LEDMask |= LEDS_LED2;
    }
    if(LEDReport == 0x0004){
        LEDMask |= LEDS_LED3;
    }
    if(LEDReport == 0x0008){
        LEDMask |= LEDS_LED4;
    }
    if(LEDReport == 0x0010){
        LEDMask |= LEDS_LED5;
    }
    if(LEDReport == 0x0020){
        LEDMask |= LEDS_LED6;
    }
    if(LEDReport == 0x0040){
        LEDMask |= LEDS_LED7;
    }
    if(LEDReport == 0x0080){
        LEDMask |= LEDS_LED8;
    }
    if(LEDReport == 0x0100){
        LEDMask |= LEDS_LED9;
    }
    if(LEDReport == 0x0200){
        LEDMask |= LEDS_LED10;
    }
    if(LEDReport == 0x0400){
        LEDMask |= LEDS_LED11;
    }

	/* Set the status LEDs to the current Keyboard LED status */
	
	LEDs_SetAllLEDs_D(LEDMask);
	LEDs_SetAllLEDs_B(LEDMask);
	LEDs_SetAllLEDs_C(LEDMask);
	LEDs_SetAllLEDs_E(LEDMask);
	}


/*-------------------------------------------------------------------------------------------------------------------------------------*/


/** Event handler for the library USB Configuration Changed event. */


void EndpointOut_LED(void)
{
	/* Select the Keyboard LED Report Endpoint */
	Endpoint_SelectEndpoint(ENDPOINT_OUT_EPADDR_1);

	/* Check if Keyboard LED Endpoint contains a packet */
	if (Endpoint_IsOUTReceived())
	{
		/* Check to see if the packet contains data */
		if (Endpoint_IsReadWriteAllowed())
		{
			/* Read in the LED report from the host */
			uint16_t LEDReport = Endpoint_Read_16_LE();

			/* Process the read LED report from the host */
			ProcessLEDReport(LEDReport);
		}

		/* Handshake the OUT Endpoint - clear endpoint and ready for next report */
		Endpoint_ClearOUT();
	}
}


void EndpointOut_Vibreur(void)
{
	/* Select the Keyboard LED Report Endpoint */
	Endpoint_SelectEndpoint(ENDPOINT_OUT_EPADDR_2);

	/* Check if Keyboard LED Endpoint contains a packet */
	if (Endpoint_IsOUTReceived())
	{
		/* Check to see if the packet contains data */
		if (Endpoint_IsReadWriteAllowed())
		{
			//???
		}

		/* Handshake the OUT Endpoint - clear endpoint and ready for next report */
		Endpoint_ClearOUT();
	}
}


void HID_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Process the LED report sent from the host */
	EndpointOut_LED();
	EndpointOut_Vibreur();
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/



/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs_D(LEDMASK_USB_ENUMERATING);
	LEDs_SetAllLEDs_B(LEDMASK_USB_ENUMERATING);
	LEDs_SetAllLEDs_C(LEDMASK_USB_ENUMERATING);
	LEDs_SetAllLEDs_E(LEDMASK_USB_ENUMERATING);

}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	
	LEDs_SetAllLEDs_D(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_B(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_C(LEDMASK_USB_NOTREADY);
	LEDs_SetAllLEDs_E(LEDMASK_USB_NOTREADY);
}


/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Joystick_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_JoystickReport_Data_t* JoystickReport = (USB_JoystickReport_Data_t*)ReportData;

	uint8_t JoyStatus_LCL    = Joystick_GetStatus();
	//uint8_t ButtonStatus_LCL = Buttons_GetStatus();

	JoystickReport -> X = JoyStatus_LCL + 0x80;
	JoystickReport -> Y = JoyStatus_LCL & 0x0F;

	/*if (ButtonStatus_LCL & BUTTONS_BUTTONHAUT){			//test bouton haut, ne fonctionne pas
		JoystickReport->Button |= BUTTONS_BUTTONHAUT;
	}*/

	JoystickReport->Button = PINF & 0x33;		//bouton haut gauche bas droit -- haut fonctionnel

	JoystickReport->Button = PINB & 0x50;		//bouton STOP et SEL


	*ReportSize = sizeof(USB_JoystickReport_Data_t);
	return false;
	
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}


