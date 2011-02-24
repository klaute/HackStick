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

/* ------------------------------------------------------------------------- */

#include "eeprom.h"

/* ------------------------------------------------------------------------- */

void eep_readUSBHidReportDescriptor()
{
    while (!eeprom_is_ready()) {}
    maxUSBHidReportDescriptorBytes = eeprom_read_byte(&eep_maxUSBHidReportDescriptorBytes);
    while (!eeprom_is_ready()) {}
    eeprom_read_block(usbHidReportDescriptor,
                eep_usbHidReportDescriptor,
                sizeof(eep_usbHidReportDescriptor));
    usbDescriptorConfiguration[25] = maxUSBHidReportDescriptorBytes;
}
void eep_saveUSBHidReportDescriptor()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_byte(&eep_maxUSBHidReportDescriptorBytes, maxUSBHidReportDescriptorBytes);
    while (!eeprom_is_ready()) {}
    eeprom_write_block(usbHidReportDescriptor,
                eep_usbHidReportDescriptor,
                sizeof(eep_usbHidReportDescriptor));
}

void eep_readUSBDataSequence()
{
    while (!eeprom_is_ready()) {}
    eeprom_read_block(usbDataSequence,
                eep_usbDataSequence,
                sizeof(eep_usbDataSequence));
}
void eep_saveUSBDataSequence()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_block(usbDataSequence,
                eep_usbDataSequence,
                sizeof(eep_usbDataSequence));
}

void eep_readUSBDescriptorStringVendor()
{
    while (!eeprom_is_ready()) {}
    eeprom_read_block(usbDescriptorStringVendor,
                eep_usbDescriptorStringVendor,
                sizeof(eep_usbDescriptorStringVendor));
}
void eep_saveUSBDescriptorStringVendor()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_block(usbDescriptorStringVendor,
                eep_usbDescriptorStringVendor,
                sizeof(eep_usbDescriptorStringVendor));
}

void eep_readUSBDescriptorStringDevice()
{
    while (!eeprom_is_ready()) {}
    eeprom_read_block(usbDescriptorStringDevice,
                eep_usbDescriptorStringDevice,
                sizeof(eep_usbDescriptorStringDevice));
}
void eep_saveUSBDescriptorStringDevice()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_block(usbDescriptorStringDevice,
                eep_usbDescriptorStringDevice,
                sizeof(eep_usbDescriptorStringDevice));
}

void eep_readUSBDescriptorStringSerialNumber()
{
    while (!eeprom_is_ready()) {}
    eeprom_read_block(usbDescriptorStringSerialNumber,
                eep_usbDescriptorSerialNumber,
                sizeof(eep_usbDescriptorSerialNumber));
}
void eep_saveUSBDescriptorStringSerialNumber()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_block(usbDescriptorStringSerialNumber,
                eep_usbDescriptorSerialNumber,
                sizeof(eep_usbDescriptorSerialNumber));
}

void eep_readUSBCfgVendorID()
{
    uint8_t tmp[USB_CFG_ID_BYTE_CNT];
    while (!eeprom_is_ready()) {}
    eeprom_read_block(tmp, eep_usbCfgVendorID, sizeof(eep_usbCfgVendorID));
    usbDescriptorDevice[8] = (char)tmp[0];
    usbDescriptorDevice[9] = (char)tmp[1];
}

void eep_saveUSBCfgVendorID()
{
    uint8_t tmp[] = {usbDescriptorDevice[8],usbDescriptorDevice[9]};
    while (!eeprom_is_ready()) {}
    eeprom_write_block(tmp, eep_usbCfgVendorID, sizeof(eep_usbCfgVendorID));
}

void eep_readUSBCfgDeviceID()
{
    uint8_t tmp[USB_CFG_ID_BYTE_CNT];
    while (!eeprom_is_ready()) {}
    eeprom_read_block(tmp, eep_usbCfgDeviceID, sizeof(eep_usbCfgDeviceID));
    usbDescriptorDevice[10] = (char)tmp[0];
    usbDescriptorDevice[11] = (char)tmp[1];
}

void eep_saveUSBCfgDeviceID()
{
    uint8_t tmp[] = {usbDescriptorDevice[10],usbDescriptorDevice[11]};
    while (!eeprom_is_ready()) {}
    eeprom_write_block(tmp, eep_usbCfgDeviceID, sizeof(eep_usbCfgDeviceID));
}

void eep_toggleUSBConfigBit(uint8_t bit)
{
	while (!eeprom_is_ready()) {}
    uint8_t config = eeprom_read_byte(&eep_usbConfig);

    config ^= (EEP_CFG_VALUE_ON << bit);

    while (!eeprom_is_ready()) {}
    eeprom_write_byte(&eep_usbConfig, config);
    printf_P(PSTR("\r\nCfg: 0x%02x"),config);
}

void eep_deleteUSBConfigBits()
{
    while (!eeprom_is_ready()) {}
    eeprom_write_byte(&eep_usbConfig, 0x00);
    uint8_t config = eeprom_read_byte(&eep_usbConfig);
    printf_P(PSTR("\r\nCfg: 0x%02x"),config);
}

