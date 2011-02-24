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

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/*----------------------------------------------------------------------------*/
#ifndef F_CPU
#define F_CPU 20000000UL
#endif

/*----------------------------------------------------------------------------*/
#define USB_CFG_HID_REPORT_DESCRIPTOR_LEN 100

// Maximale Länge der Strings für die USB Variablen.
#define USB_DEVICE_STRING_DESCRIPTION_LEN 20

// Maximale Anzahl der zu übertragenden DatenBytes festlegen
#define USB_MAX_DATA_BYTES 128

// Anzahl der Bytes für die USB ID's (Vendor und Device)
#define USB_CFG_ID_BYTE_CNT 2

// Maximal Anzahl der Bytes im EEPROM abzüglich der anderen gespeicherten Daten.
//( 512 -(2 + USB_CFG_HID_REPORT_DESCRIPTOR_LEN + (2*USB_CFG_ID_BYTE_CNT) + (3*USB_DEVICE_STRING_DESCRIPTION_LEN) ) )
#define USB_MAX_DATA_SEQ_SIZE 286
//#define USB_MAX_DATA_SEQ_SIZE 512-(2 + USB_CFG_HID_REPORT_DESCRIPTOR_LEN + (2*USB_CFG_ID_BYTE_CNT) + (3*USB_DEVICE_STRING_DESCRIPTION_LEN) )

/*----------------------------------------------------------------------------*/
// Defines um die LED's einfacher ansteuern zu können.
#define LED_RED_PORT    PORTC
#define LED_YELLOW_PORT PORTC
#define LED_GREEN_PORT  PORTB
#define LED_RED_PIN     PC4
#define LED_YELLOW_PIN  PC5
#define LED_GREEN_PIN   PB1

/*----------------------------------------------------------------------------*/
// Konfigurationsbits in der EEPROM-Variable eep_usbConfig
#define EEP_CFG_USB_HID_REPORT_DESCRIPTOR           0
#define EEP_CFG_USB_DESCRIPTOR_STRING_VENDOR        1
#define EEP_CFG_USB_DESCRIPTOR_STRING_DEVICE        2
#define EEP_CFG_USB_DESCRIPTOR_STRING_SERIAL_NUMBER 3
#define EEP_CFG_USB_CONFIG_VENDOR_ID                4
#define EEP_CFG_USB_CONFIG_DEVICE_ID                5
#define EEP_CFG_USB_DATA_SEQ                        6

#define EEP_CFG_USB_TYPES       7 // Die Anzahl der "EEP_CFG_USB_" Defines
#define EEP_CFG_USB_STARTS_WITH 0

#define EEP_CFG_VALUE_ON  1
#define EEP_CFG_VALUE_OFF 0

/*----------------------------------------------------------------------------*/

#endif

