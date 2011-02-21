/* (C) Copyright 2011 Kai Lauterbach klaute at web.de
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

#ifndef EEPROM_H
#define EEPROM_H

/*----------------------------------------------------------------------------*/

#include <avr/eeprom.h> // eeprom...
#include <avr/pgmspace.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "usbdrv.h"

#include "globals.h"

/*----------------------------------------------------------------------------*/

#ifndef EEMEM
// alle Textstellen EEMEM im Quellcode durch __attribute__ ... ersetzen
#define EEMEM  __attribute__ ((section (".eeprom")))
#endif

/*----------------------------------------------------------------------------*/

#define USB_CFG_ID_BYTE_CNT 2

/*----------------------------------------------------------------------------*/

extern uchar dataBytes[];
extern char usbHidReportDescriptor[];
extern uint8_t maxUSBDataBytes;
extern uint8_t maxUSBHidReportDescriptorBytes;

/*----------------------------------------------------------------------------*/

// Variablen im EEPROM
uint8_t eep_usbConfig EEMEM;
uint8_t eep_maxUSBHidReportDescriptorBytes EEMEM;
char eep_usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LEN] EEMEM;

int eep_usbDescriptorStringVendor[USB_DEVICE_STRING_DESCRIPTION_LEN] EEMEM;
int eep_usbDescriptorStringDevice[USB_DEVICE_STRING_DESCRIPTION_LEN] EEMEM;
int eep_usbDescriptorSerialNumber[USB_DEVICE_STRING_DESCRIPTION_LEN] EEMEM;
uint8_t eep_usbCfgVendorID[USB_CFG_ID_BYTE_CNT] EEMEM;
uint8_t eep_usbCfgDeviceID[USB_CFG_ID_BYTE_CNT] EEMEM;
uint8_t eep_maxUSBDataBytes EEMEM;
uchar eep_dataBytes[USB_MAX_DATA_BYTES] EEMEM;

/*----------------------------------------------------------------------------*/

// Methoden zum Zugriff auf die Variablen im EEPROM
void eep_readUSBHidReportDescriptor(void);
void eep_saveUSBHidReportDescriptor(void);

void eep_readUSBHidReportData(void);
void eep_saveUSBHidReportData(void);

void eep_readUSBDescriptorStringVendor(void);
void eep_saveUSBDescriptorStringVendor(void);

void eep_readUSBDescriptorStringDevice(void);
void eep_saveUSBDescriptorStringDevice(void);

void eep_readUSBDescriptorStringSerialNumber(void);
void eep_saveUSBDescriptorStringSerialNumber(void);

void eep_readUSBCfgVendorID(void);
void eep_saveUSBCfgVendorID(void);

void eep_readUSBCfgDeviceID(void);
void eep_saveUSBCfgDeviceID(void);

void eep_toggleUSBConfigBit(uint8_t);

void eep_deleteUSBConfigBits(void);

/*----------------------------------------------------------------------------*/

#endif

