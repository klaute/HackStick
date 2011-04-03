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

//#define DEBUG

/*----------------------------------------------------------------------------*/
#ifndef F_CPU
#define F_CPU 20000000UL
#endif

/*----------------------------------------------------------------------------*/
// Flags um die Bestandteile der Firmware zu aktivieren/deaktivieren

#define WITH_INTERPRETER

/*----------------------------------------------------------------------------*/

#define USB_CFG_HID_REPORT_DESCRIPTOR_LEN 100

// Maximale Laenge der Strings fuer die USB Variablen.
#define USB_DEVICE_STRING_DESCRIPTION_LEN 20

// Maximale Anzahl der zu uebertragenden DatenBytes festlegen
#define USB_MAX_DATA_BYTES 128

// Anzahl der Bytes fuer die USB ID's (Vendor und Device)
#define USB_CFG_ID_BYTE_CNT 2

// Anzahl der Bytes die notwendig sind für das Erkennen von zu empfangenen Daten
// Byte 0: ist beinhaltet die Anzahl der Bytes die empfangen werden sollen,
//         diese wurde im USB Hid Report Descriptor festgelegt
// Byte 1: Index der Byte im Daten-Array, das geprüft werden soll.
// Byte 2: Inhalt der per & mit dem Byte im Daten-Array verknüpft wird.
#define USB_RECEIVE_DATA_SIZE 3

// Maximal Anzahl der Bytes im EEPROM abzueglich der anderen gespeicherten Daten.
#define USB_MAX_DATA_SEQ_SIZE 794

/*----------------------------------------------------------------------------*/
// Defines um die LED's einfacher ansteuern zu koennen.
#define LED_RED_PORT    PORTC
#define LED_YELLOW_PORT PORTC
#define LED_GREEN_PORT  PORTB
#define LED_RED_PIN     PC4
#define LED_YELLOW_PIN  PC5
#define LED_GREEN_PIN   PB1

/*----------------------------------------------------------------------------*/
// Konfigurationsbits in der EEPROM-Variable eep_usbConfig (16 Bit)
// Ist das entsprechende Bit ind er EEPROM Konfigurations-Variable gesetzt (1),
// dann ist die Funktion aktiv.
#define EEP_CFG_USB_HID_REPORT_DESCRIPTOR           0
#define EEP_CFG_USB_DESCRIPTOR_STRING_VENDOR        1
#define EEP_CFG_USB_DESCRIPTOR_STRING_DEVICE        2
#define EEP_CFG_USB_DESCRIPTOR_STRING_SERIAL_NUMBER 3
#define EEP_CFG_USB_CONFIG_VENDOR_ID                4
#define EEP_CFG_USB_CONFIG_DEVICE_ID                5
#define EEP_CFG_USB_DATA_SEQ                        6
#define EEP_CFG_USB_CONFIG_INTERPRET_SD             7
#define EEP_CFG_USB_RECEIVE_DATA                    8
#define EEP_CFG_USB_RECEIVE_DATA_ACTIVE             9 // Ist diese Funktion aktiv, wird EEP_CFG_USB_CONFIG_INTERPRET_SD ignoriert.
#define EEP_CFG_USB_ACTIVE                         10

#define EEP_CFG_USB_TYPES       11 // Die Anzahl der "EEP_CFG_USB_" Defines, nicht der höchste Wert.
#define EEP_CFG_USB_STARTS_WITH  0

#define EEP_CFG_VALUE_ON  1
#define EEP_CFG_VALUE_OFF 0

/*----------------------------------------------------------------------------*/
// USART Puffergröße in Byte

#define UART_RX_BUFFER_SIZE 128
#define UART_TX_BUFFER_SIZE 0

/*----------------------------------------------------------------------------*/

// Bit in USB_Status.os_type
#define USB_HID_DESCRIPTOR_DONE                  (1 << 0) // =   1
#define USB_CONFIG_DESCRIPTOR_DONE               (1 << 1) // =   2
#define USB_DEVICE_DESCRIPTOR_DONE               (1 << 2) // =   4
#define USB_HID_REPORT_DESCRIPTOR_DONE           (1 << 3) // =   8
#define USB_STRING_DEVICE_DESCRIPTOR_DONE        (1 << 4) // =  16
#define USB_STRING_VENDOR_DESCRIPTOR_DONE        (1 << 5) // =  32
#define USB_STRING_SERIAL_NUMBER_DESCRIPTOR_DONE (1 << 6) // =  64

// Vergleichswerte, die in usb_status.descr_sent und optional in
// usb_status.sub_status enthalten sein müssen, um den Verbindungs-Status
// in usb_status.connected auf Verbunden (1) zu setzen.
#define USB_LINUX_CONNECTED ( USB_CONFIG_DESCRIPTOR_DONE | \
							  USB_STRING_SERIAL_NUMBER_DESCRIPTOR_DONE | \
							  USB_STRING_DEVICE_DESCRIPTOR_DONE | \
							  USB_STRING_VENDOR_DESCRIPTOR_DONE | \
							  USB_HID_REPORT_DESCRIPTOR_DONE ) && \
		                    usb_status.sub_status == 0x02
#define USB_WIN7_CONNECTED ( USB_CONFIG_DESCRIPTOR_DONE | \
							 USB_STRING_SERIAL_NUMBER_DESCRIPTOR_DONE | \
							 USB_STRING_DEVICE_DESCRIPTOR_DONE | \
							 USB_HID_REPORT_DESCRIPTOR_DONE ) && \
		                    usb_status.sub_status == 0x02

typedef struct USB_Status
{
    // isd ist das Status-Bit welches in der main Hauptschleife geprüft wird um
    // die Interpretation der aktuell vorgehaltenen Sequenz-Daten zu starten.
    uint16_t isd        : 1;
    // "prd" wird in der Funktion zum Empfang von USB Daten dazu verwendet um
    // die Prüfung dieser zu veranlassen. 1 = aktiviert.
    uint16_t prd        : 1;
    // Hier wird der Verbindungsstatus eingetragen. TODO Betriebssystemabhängig
    // müssen hier Werte festgelegt werden.
    uint16_t connected  : 1;
	// Ein Byte zum erkennen des OS
	uint16_t descr_sent : 7;
	uint16_t sub_status : 6;
} USB_Status_t;

/*----------------------------------------------------------------------------*/

#endif

