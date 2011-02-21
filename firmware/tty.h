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

#ifndef TTY_H
#define TTY_H

/*----------------------------------------------------------------------------*/
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "usbdrv.h"
#include "uart.h"

#include "globals.h"

// Maximale Länge die auf dem Terminal als kommando inkl. Parametern angegeben werden kann.
#define TTY_MAX_CMD_LINE_LEN 30

#define TTY_CMD_WITHOUT_PARAMETER     0
#define TTY_CMD_WITH_STRING_PARAMETER 1

#define TTY_READ_MODE_COMMAND        0
#define TTY_READ_MODE_HID_DESCRIPTOR 1
#define TTY_READ_MODE_HID_DATA       2

#define TTY_ECHO_ON  1
#define TTY_ECHO_OFF 0

// Verschiebung der EEPROM-Konstanten
#define TTY_EEP_CFG_USB_OFFSET 16

const char WELCOME_MSG[] PROGMEM = "\r\n------------------\r\n\r\nklaute's HackStick\r\nv0.06 (by klaute)\r\n>";

/*----------------------------------------------------------------------------*/
// Externe USB-Daten
extern uint8_t dataBytes[];
extern uint8_t maxUSBDataBytes;
extern uint8_t maxUSBHidReportDescriptorBytes;
extern char usbHidReportDescriptor[];
extern char usbDescriptorConfiguration[];

extern int usbDescriptorStringVendor[];
extern int usbDescriptorStringDevice[];
extern int usbDescriptorStringSerialNumber[];

/*----------------------------------------------------------------------------*/
// Externe Methoden zum Zugriff auf Daten

extern void usbReset(void);

extern void eep_readUSBHidReportDescriptor(void);
extern void eep_saveUSBHidReportDescriptor(void);

extern void eep_readUSBHidReportData(void);
extern void eep_saveUSBHidReportData(void);

extern void eep_readUSBDescriptorStringVendor(void);
extern void eep_saveUSBDescriptorStringVendor(void);

extern void eep_readUSBDescriptorStringDevice(void);
extern void eep_saveUSBDescriptorStringDevice(void);

extern void eep_readUSBDescriptorStringSerialNumber(void);
extern void eep_saveUSBDescriptorStringSerialNumber(void);

extern void eep_readUSBCfgVendorID(void);
extern void eep_saveUSBCfgVendorID(void);

extern void eep_readUSBCfgDeviceID(void);
extern void eep_saveUSBCfgDeviceID(void);

extern void eep_toggleUSBConfigBit(uint8_t);

extern void eep_deleteUSBConfigBits(void);

/*----------------------------------------------------------------------------*/

// Configutrationsbyte für das TTY
struct tty_config_t {
    // TTY_READ_MODE_COMMAND = Kommando-Modus
    // TTY_READ_MODE_HID_DESCRIPTOR = Zeilenweises einlesen des HIDDescriptors
    // TTY_READ_MODE_HID_DATA = Einlesen der HIDReportData
    uint8_t read_mode:2;
    // TTY_ECHO_ON = TTY echo eingeschaltet;
    // TTY_ECHO_OFF = TTY echo ausgeschalte
    uint8_t echo:1;
    uint8_t empty:5; // Frei für weiter Konfigurationszwecke.
} tty_config;

unsigned char tty_cb_pos; // Position im Kommando Buffer
unsigned char tty_ud_pos; // Position in den zu verändernden Daten

// Puffer der eingegeben Kommandos und deren Parameter.
char tty_buff[TTY_MAX_CMD_LINE_LEN];

// Typendefinition zur verinfachten Zuordnung von Kommandos zu
// den damit verbundenen Funktionen.
typedef struct
{
   void (*func)(int); // Zeiger auf die auszuführende Funktion
   int type;         // das Argument, das mitübergeben wird
   char *command;    // Zeiger auf das Kommando im FLASH
} tty_command_t;

/*----------------------------------------------------------------------------*/

void tty_init(void);

// Diese Funktion wird für jedes Zeichen aufgerufen das per printf auseggeben wird.
static int _uart_putc(char c, FILE *stream);

void tty_pollTerminal(void); // Muss kontinuierlich aufgerufen werden, für das Terminal

int tty_executeCmd(const char*);

/*----------------------------------------------------------------------------*/
// Funktionen zum Zugriff auf die externen Daten

void tty_ledRedOn(void);
void tty_ledRedOff(void);
void tty_ledGreenOn(void);
void tty_ledGreenOff(void);
void tty_ledYellowOn(void);
void tty_ledYellowOff(void);

void tty_setInterrupt(void);
#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
void tty_setInterrupt3(void);
#endif

void tty_setUSBReportData(void);
void tty_setUSBHidDeviceDescriptor(void);

void tty_setVendorName(char*);
void tty_setDeviceName(char*);
void tty_setSerialNumber(char*);

void tty_setVendorHeader(char *t);
void tty_setDeviceNameHeader(char *t);
void tty_setSerialNumberHeader(char *t);

void tty_setUSBConfigVendorID(char*);
void tty_setUSBConfigDeviceID(char*);

void tty_getUSBHidDeviceDescriptor(void);
void tty_getUSBReportData(void);

void tty_getVendorName(void);
void tty_getDeviceName(void);
void tty_getSerialNumber(void);

void tty_getUSBConfigVendorID(void);
void tty_getUSBConfigDeviceID(void);

void tty_setEcho(char*);

/*----------------------------------------------------------------------------*/

// Zum umbiegen von stdout auf UART
static FILE _stdout = FDEV_SETUP_STREAM(_uart_putc, NULL, _FDEV_SETUP_WRITE);

/*----------------------------------------------------------------------------*/

// Liste der Kommandos, abgelegt im Flash.
const prog_char _rledon[]  = "rledon";
const prog_char _rledoff[] = "rledoff";
const prog_char _yledon[]  = "yledon";
const prog_char _yledoff[] = "yledoff";
const prog_char _gledon[]  = "gledon";
const prog_char _gledoff[] = "gledoff";
const prog_char _urst[] = "urst";
const prog_char _sint[] = "sint";
#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
const prog_char _sint3[] = "sint3";
#endif
const prog_char _gdsc[] = "gdsc";
const prog_char _gdta[] = "gdta";

const prog_char _sdsc[] = "sdsc";
const prog_char _sdta[] = "sdta";

const prog_char _erdta[] = "erdta";
const prog_char _esdta[] = "esdta";
const prog_char _erdsc[] = "erdsc";
const prog_char _esdsc[] = "esdsc";

const prog_char _ervn[]  = "ervn";
const prog_char _esvn[]  = "esvn";
const prog_char _ern[]   = "ern";
const prog_char _esn[]   = "esn";
const prog_char _ersn[]  = "ersn";
const prog_char _essn[]  = "essn";

const prog_char _ercvid[] = "ercvid";
const prog_char _escvid[] = "escvid";
const prog_char _ercdid[] = "ercdid";
const prog_char _escdid[] = "escdid";

const prog_char _tlosdsc[]  = "tlosdsc";
const prog_char _tlosdta[]  = "tlosdta";
const prog_char _tlosvn[]   = "tlosvn";
const prog_char _tlosn[]    = "tlosn";
const prog_char _tlossn[]   = "tlossn";
const prog_char _tloscvid[] = "tloscvid";
const prog_char _tloscdid[] = "tloscdid";

const prog_char _edcfg[]  = "edcfg";

const prog_char _gvn[]   = "gvn";
const prog_char _gn[]    = "gn";
const prog_char _gsn[]   = "gsn";
const prog_char _gcvid[] = "gcvid";
const prog_char _gcdid[] = "gcdid";
const prog_char _svn[]   = "svn";
const prog_char _sn[]    = "sn";
const prog_char _ssn[]   = "ssn";

const prog_char _svnh[]   = "svnh";
const prog_char _snh[]    = "snh";
const prog_char _ssnh[]   = "ssnh";

const prog_char _scvid[] = "scvid";
const prog_char _scdid[] = "scdid";

const prog_char _ttye[] = "ttye";

// Zuordnung der vorher definierten Kommandos
// zu den Funktionen mit deren Parametern
const tty_command_t tty_commands[] PROGMEM = {

    { tty_ledRedOn,     TTY_CMD_WITHOUT_PARAMETER, _rledon  },
    { tty_ledRedOff,    TTY_CMD_WITHOUT_PARAMETER, _rledoff },
    { tty_ledYellowOn,  TTY_CMD_WITHOUT_PARAMETER, _yledon  },
    { tty_ledYellowOff, TTY_CMD_WITHOUT_PARAMETER, _yledoff },
    { tty_ledGreenOn,   TTY_CMD_WITHOUT_PARAMETER, _gledon  },
    { tty_ledGreenOff,  TTY_CMD_WITHOUT_PARAMETER, _gledoff },

    { usbReset, TTY_CMD_WITHOUT_PARAMETER, _urst },

    { tty_setInterrupt,  TTY_CMD_WITHOUT_PARAMETER, _sint  },

#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
    { tty_setInterrupt3, TTY_CMD_WITHOUT_PARAMETER, _sint3 },
#endif

    { tty_getUSBHidDeviceDescriptor, TTY_CMD_WITHOUT_PARAMETER, _gdsc },
    { tty_getUSBReportData,          TTY_CMD_WITHOUT_PARAMETER, _gdta },

    { tty_setUSBHidDeviceDescriptor, TTY_CMD_WITHOUT_PARAMETER, _sdsc },
    { tty_setUSBReportData,          TTY_CMD_WITHOUT_PARAMETER, _sdta },

    { eep_readUSBHidReportData,                TTY_CMD_WITHOUT_PARAMETER, _erdta  },
    { eep_saveUSBHidReportData,                TTY_CMD_WITHOUT_PARAMETER, _esdta  },
    { eep_readUSBHidReportDescriptor,          TTY_CMD_WITHOUT_PARAMETER, _erdsc  },
    { eep_saveUSBHidReportDescriptor,          TTY_CMD_WITHOUT_PARAMETER, _esdsc  },
    { eep_readUSBDescriptorStringVendor,       TTY_CMD_WITHOUT_PARAMETER, _ervn   },
    { eep_saveUSBDescriptorStringVendor,       TTY_CMD_WITHOUT_PARAMETER, _esvn   },
    { eep_readUSBDescriptorStringDevice,       TTY_CMD_WITHOUT_PARAMETER, _ern    },
    { eep_saveUSBDescriptorStringDevice,       TTY_CMD_WITHOUT_PARAMETER, _esn    },
    { eep_readUSBDescriptorStringSerialNumber, TTY_CMD_WITHOUT_PARAMETER, _ersn   },
    { eep_saveUSBDescriptorStringSerialNumber, TTY_CMD_WITHOUT_PARAMETER, _essn   },
    { eep_readUSBCfgVendorID,                  TTY_CMD_WITHOUT_PARAMETER, _ercvid },
    { eep_saveUSBCfgVendorID,                  TTY_CMD_WITHOUT_PARAMETER, _escvid },
    { eep_readUSBCfgDeviceID,                  TTY_CMD_WITHOUT_PARAMETER, _ercdid },
    { eep_saveUSBCfgDeviceID,                  TTY_CMD_WITHOUT_PARAMETER, _escdid },

    { eep_toggleUSBConfigBit, EEP_CFG_USB_HID_REPORT_DESCRIPTOR + TTY_EEP_CFG_USB_OFFSET,           _tlosdsc  },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_HID_REPORT_DATA + TTY_EEP_CFG_USB_OFFSET,                 _tlosdta  },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_DESCRIPTOR_STRING_VENDOR + TTY_EEP_CFG_USB_OFFSET,        _tlosvn   },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_DESCRIPTOR_STRING_DEVICE + TTY_EEP_CFG_USB_OFFSET,        _tlosn    },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_DESCRIPTOR_STRING_SERIAL_NUMBER + TTY_EEP_CFG_USB_OFFSET, _tlossn   },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_CONFIG_VENDOR_ID + TTY_EEP_CFG_USB_OFFSET,                _tloscvid },
    { eep_toggleUSBConfigBit, EEP_CFG_USB_CONFIG_DEVICE_ID + TTY_EEP_CFG_USB_OFFSET,                _tloscdid },

    { eep_deleteUSBConfigBits, TTY_CMD_WITHOUT_PARAMETER, _edcfg },

    { tty_getVendorName,        TTY_CMD_WITHOUT_PARAMETER, _gvn   },
    { tty_getDeviceName,        TTY_CMD_WITHOUT_PARAMETER, _gn    },
    { tty_getSerialNumber,      TTY_CMD_WITHOUT_PARAMETER, _gsn   },
    { tty_getUSBConfigVendorID, TTY_CMD_WITHOUT_PARAMETER, _gcvid },
    { tty_getUSBConfigDeviceID, TTY_CMD_WITHOUT_PARAMETER, _gcdid },

    { tty_setVendorName,        TTY_CMD_WITH_STRING_PARAMETER, _svn },
    { tty_setDeviceName,        TTY_CMD_WITH_STRING_PARAMETER, _sn  },
    { tty_setSerialNumber,      TTY_CMD_WITH_STRING_PARAMETER, _ssn },

    { tty_setVendorHeader,       TTY_CMD_WITH_STRING_PARAMETER, _svnh },
    { tty_setDeviceNameHeader,   TTY_CMD_WITH_STRING_PARAMETER, _snh  },
    { tty_setSerialNumberHeader, TTY_CMD_WITH_STRING_PARAMETER, _ssnh },

    { tty_setUSBConfigVendorID, TTY_CMD_WITH_STRING_PARAMETER, _scvid },
    { tty_setUSBConfigDeviceID, TTY_CMD_WITH_STRING_PARAMETER, _scdid },

    { tty_setEcho, TTY_CMD_WITH_STRING_PARAMETER, _ttye },

};

#endif

