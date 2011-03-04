/* (C) Copyright 2011 Kai Lauterbach klaute at web dot de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef MAIN_H
#define MAIN_H

/*----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "globals.h"

#include "usbdrv.h"

/*----------------------------------------------------------------------------*/

int __attribute__((noreturn)) main(void);
// Init Methode der Firmware.
void init(void);

void _loadEEPROMConfig(void);

void usbReset(void);

/*----------------------------------------------------------------------------*/
/* Sequenz Daten Funktionen */

#ifdef WITH_INTERPRETER
void interpretUSBDataSequence(void);
#endif

/*----------------------------------------------------------------------------*/

extern uint8_t eep_usbConfig EEMEM;

extern const char WELCOME_MSG[] PROGMEM;

/*----------------------------------------------------------------------------*/
// Methoden zum Zugriff auf die Variablen im EEPROM
extern void tty_init(void);
extern void tty_pollTerminal(void);
extern void tty_setInterrupt(void);
#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
extern void tty_setInterrupt3(void);
#endif

extern void eep_readUSBHidReportDescriptor(void);

#ifdef WITH_INTERPRETER
extern void eep_readUSBDataSequence(void);
#endif

extern void eep_readUSBDescriptorStringVendor(void);

extern void eep_readUSBDescriptorStringDevice(void);

extern void eep_readUSBDescriptorStringSerialNumber(void);

extern void eep_readUSBCfgVendorID(void);

extern void eep_readUSBCfgDeviceID(void);

/*----------------------------------------------------------------------------*/
/* USB */

// Maximale Anzahl der zu übertragenden DatenBytes festlegen
uint8_t maxUSBDataBytes;
#ifdef WITH_INTERPRETER
// Vorhandene Anzahl von Sequenzbytes
uint8_t usbDataSequenceBytes;
#endif

// Statusvariable zum steuern der übertragenen Bytes.
static uchar bytesRemaining;

static uchar idleRate; // in 4 ms units

// Daten die an den Host gesendet werden.
uint8_t dataBytes[USB_MAX_DATA_BYTES];
#ifdef WITH_INTERPRETER
// Sequence der Daten die an den Host gesendet werden sollen.
uint8_t usbDataSequence[USB_MAX_DATA_SEQ_SIZE];
#endif

/*----------------------------------------------------------------------------*/
/* USB report descriptor */

typedef struct USB_Descr
{
    // TODO In EEPROM ablegen und per Kommandozeile konfigurierbar machen.
    // Hid Informationen
    uint8_t USBCfgDeviceClass;
    uint8_t USBCfgDeviceSubClass;
    // Für die Device Configuration
    uint8_t USBCfgInterfaceClass; // 3
    uint8_t USBCfgInterfaceSubClass;
    uint8_t USBCfgInterfaceProtocol;
} USB_Descr_t;

USB_Descr_t usb_descr;

/*----------------------------------------------------------------------------*/

uint8_t maxUSBHidReportDescriptorBytes = 22;

// USB_CFG_HID_REPORT_DESCRIPTOR_LEN in usbconfig.h definiert
char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LEN] = {

// USB Data (22 Byte)
 0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
  0x09, 0x01,                    // USAGE (Vendor Usage 1)
   0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x80,                    //   REPORT_COUNT (128)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
 0xc0,                          // END_COLLECTION

};

int usbDescriptorStringVendor[USB_DEVICE_STRING_DESCRIPTION_LEN+1];

int usbDescriptorStringDevice[USB_DEVICE_STRING_DESCRIPTION_LEN+1];

int usbDescriptorStringSerialNumber[USB_DEVICE_STRING_DESCRIPTION_LEN+1];

char usbDescriptorDevice[] = {    /* USB device descriptor */
    18,         /* sizeof(usbDescriptorDevice): length of descriptor in bytes */
    USBDESCR_DEVICE,        /* descriptor type */
    0x10, 0x01,             /* USB version supported */
    0,   // DeviceClass wird in der init gesetzt
    0,   // DeviceSubClass wird in der init gesetzt
    0,                      /* protocol */
    8,                      /* max packet size */
    /* the following two casts affect the first byte of the constant only, but
     * that's sufficient to avoid a warning with the default values.
     */
    0xc0, 0x16, /* 2 bytes, werden in der init gesetzt */
    0xdf, 0x05, /* 2 bytes, werden in der init gesetzt */
    USB_CFG_DEVICE_VERSION, /* 2 bytes */
    USB_CFG_DESCR_PROPS_STRING_VENDOR != 0 ? 1 : 0,         /* manufacturer string index */
    USB_CFG_DESCR_PROPS_STRING_PRODUCT != 0 ? 2 : 0,        /* product string index */
    USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER != 0 ? 3 : 0,  /* serial number string index */
    1,          /* number of configurations */
};

// Für die Device Configuration
char usbDescriptorConfiguration[] = {    // USB configuration descriptor
    9,          // sizeof(usbDescriptorConfiguration): length of descriptor in bytes
    USBDESCR_CONFIG,    // descriptor type
    18 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3 +
                9, 0,
                //(USB_CFG_DESCR_PROPS_HID & 0xff), 0,
                // total length of data returned (including inlined descriptors)
    1,          // number of interfaces in this configuration
    1,          // index of this configuration
    0,          // configuration name string index
#if USB_CFG_IS_SELF_POWERED
    (1 << 7) | USBATTR_SELFPOWER,       // attributes
#else
    (1 << 7),                           // attributes
#endif
    USB_CFG_MAX_BUS_POWER/2,            // max USB current in 2mA units
// interface descriptor follows inline:
    9,          // sizeof(usbDescrInterface): length of descriptor in bytes
    USBDESCR_INTERFACE, // descriptor type
    0,          // index of this interface
    0,          // alternate setting for this interface
    // endpoints excl 0: number of endpoint descriptors to follow
    USB_CFG_HAVE_INTRIN_ENDPOINT + USB_CFG_HAVE_INTRIN_ENDPOINT3,
    0, // wird per USBCfgInterfaceClass in der init gesetzt
    0, // wird per USBCfgInterfaceSubClass in der init gesetzt
    0, // wird per USBCfgInterfaceProtocol in der init gesetzt
    0,          // string index for interface
// da USB_CFG_DESCR_PROPS_HID == 0 ist wird dieser Block niermal eingefügt.
//#if (USB_CFG_DESCR_PROPS_HID & 0xff)
    // HID descriptor
    9,          // sizeof(usbDescrHID): length of descriptor in bytes
    USBDESCR_HID,   // descriptor type: HID
    0x01, 0x01, // BCD representation of HID version
    0x00,       // target country code
    0x01,       // number of HID Report (or other HID class) Descriptor infos to follow
    0x22,       // descriptor type: report
    // Länge des Hid Report Descriptors: Der standard wird in der init gesetzt,
    // hier nur ein statischer dummy
    USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH, 0, // lowByte, highByte
//#endif
#if USB_CFG_HAVE_INTRIN_ENDPOINT    // endpoint descriptor for endpoint 1
    7,          // sizeof(usbDescrEndpoint)
    USBDESCR_ENDPOINT,  // descriptor type = endpoint
    (char)0x81, // IN endpoint number 1
    0x03,       // attrib: Interrupt endpoint
    8, 0,       // maximum packet size
    USB_CFG_INTR_POLL_INTERVAL, // in ms
#endif
#if USB_CFG_HAVE_INTRIN_ENDPOINT3   // endpoint descriptor for endpoint 3
    7,          // sizeof(usbDescrEndpoint)
    USBDESCR_ENDPOINT,  // descriptor type = endpoint
    (char)(0x80 | USB_CFG_EP3_NUMBER), // IN endpoint number 3
    0x03,       // attrib: Interrupt endpoint
    8, 0,       // maximum packet size
    USB_CFG_INTR_POLL_INTERVAL, // in ms
#endif
};

#endif

