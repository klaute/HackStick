/* (C) Copyright 2011 Kai Lauterbach klaute at web dot de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is dist ributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "main.h"

/* ------------------------------------------------------------------------- */
int __attribute__((noreturn)) main(void)
{

    init();

    do { // Hauptschleife

        usbPoll();

        tty_pollTerminal();

        _delay_ms(10);

    } while (1); // Endlosschleife

}

/* ------------------------------------------------------------------------- */

/* Initialisieren der Hardware */
void init(void)
{

    DDRB  |= (1 << PB1); // Grüne LED dran als Ausgang
    LED_GREEN_PORT = LED_GREEN_PORT | (1 << LED_GREEN_PIN);

    DDRC  |= (1 << PC4); // Rote LED dran als Ausgang
    LED_RED_PORT = LED_RED_PORT | (1 << LED_RED_PIN);

    DDRC  |= (1 << PC5); // Gelbe LED dran als Ausgang
    LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);

    // PD3, PD2 Eingang ohne PullUp, PD6 mit PullUp
    // PD3 und PD2 werden für die USB-Verbindung verwendet.
    // PD6 ist der Jumper.
    DDRD  |= (0 << PD3) | (0 << PD2) | (0 << PD6);
    PORTD |= (0 << PD3) | (0 << PD2) | (1 << PD6);

    tty_init();

    // USB-Konfiguartion aus dem EEPROM laden
    uint8_t config = eeprom_read_byte(&eep_usbConfig);

    // TODO aus EEPROM laden oder festlegen der USB Geräteinformationen setzen
    usbDescriptorDevice[4]  = USBCfgDeviceClass;
    usbDescriptorDevice[5]  = USBCfgDeviceSubClass;
    usbDescriptorConfiguration[14] = USBCfgInterfaceClass;
    usbDescriptorConfiguration[15] = USBCfgInterfaceSubClass;
    usbDescriptorConfiguration[16] = USBCfgInterfaceProtocol;
    
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_HID_REPORT_DESCRIPTOR)) )
    {
        eep_readUSBHidReportDescriptor();
    } else {
        usbDescriptorConfiguration[25] = maxUSBHidReportDescriptorBytes;
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_DESCRIPTOR_STRING_VENDOR)) )
    {
        eep_readUSBDescriptorStringVendor();
    } else {
        usbDescriptorStringVendor[0] = USB_STRING_DESCRIPTOR_HEADER(8);
        usbDescriptorStringVendor[1] = 'k';
        usbDescriptorStringVendor[2] = 'l';
        usbDescriptorStringVendor[3] = 'a';
        usbDescriptorStringVendor[4] = 'u';
        usbDescriptorStringVendor[5] = 't';
        usbDescriptorStringVendor[6] = 'e';
        usbDescriptorStringVendor[7] = '\'';
        usbDescriptorStringVendor[8] = 's';
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_DESCRIPTOR_STRING_DEVICE)) )
    {
        eep_readUSBDescriptorStringDevice();
    } else {
        usbDescriptorStringDevice[0] = USB_STRING_DESCRIPTOR_HEADER(9);
        usbDescriptorStringDevice[1] = 'H';
        usbDescriptorStringDevice[2] = 'a';
        usbDescriptorStringDevice[3] = 'c';
        usbDescriptorStringDevice[4] = 'k';
        usbDescriptorStringDevice[5] = 'S';
        usbDescriptorStringDevice[6] = 't';
        usbDescriptorStringDevice[7] = 'i';
        usbDescriptorStringDevice[8] = 'c';
        usbDescriptorStringDevice[9] = 'k';
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_DESCRIPTOR_STRING_SERIAL_NUMBER)) )
    {
        eep_readUSBDescriptorStringSerialNumber();
    } else {
        usbDescriptorStringSerialNumber[0] = USB_STRING_DESCRIPTOR_HEADER(4);
        usbDescriptorStringSerialNumber[1] = '0';
        usbDescriptorStringSerialNumber[2] = '.';
        usbDescriptorStringSerialNumber[3] = '0';
        usbDescriptorStringSerialNumber[4] = '6';
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_CONFIG_VENDOR_ID)) )
    {
        eep_readUSBCfgVendorID();
    //} else {
        //usbDescriptorDevice[8]  = 0xc0; // Low-Byte der Vendor ID
        //usbDescriptorDevice[9]  = 0x16;
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_CONFIG_DEVICE_ID)) )
    {
        eep_readUSBCfgDeviceID();
    //} else {
        //usbDescriptorDevice[10] = 0xdf; // Low-Byte der Device ID
        //usbDescriptorDevice[11] = 0x05;
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_HID_REPORT_DATA)) )
    {
        eep_readUSBHidReportData();
    }

    // USB initialisieren
    usbInit();

    usbReset(); // USB Verbindung resetten

    sei(); // Interruptupts global einschalten

    printf_P(WELCOME_MSG);
    
}

/* ------------------------------------------------------------------------- */
/* Simulieren eines USB disconnect */
void usbReset( void )
{

    LED_GREEN_PORT = LED_GREEN_PORT & ~(1 << LED_GREEN_PIN);
    usbDeviceDisconnect();

    uchar i = 13;
    do
    {    // USB disconnect (~250ms)
        _delay_ms(20);
        LED_GREEN_PORT = LED_GREEN_PORT ^ (1 << LED_GREEN_PIN); // Grüne LED blinken lassen
    } while ( --i );

    usbDeviceConnect();
    LED_GREEN_PORT = LED_GREEN_PORT | (1 << LED_GREEN_PIN);

}

/* ------------------------------------------------------------------------- */
/* usbFunctionRead() wird aufgerufen wenn der PC auf den AVR lesend zugreift.
 */
uchar usbFunctionRead(uchar *data, uchar len)
{
    // Wenn mehr Bytes übertragen werden sollen als übernommen werden können
    // sollen die überschüssigen ignoriert werden
    if (len > bytesRemaining)
        len = bytesRemaining;

    LED_YELLOW_PORT = LED_YELLOW_PORT & ~(1 << LED_YELLOW_PIN);

    // Berechnen der Position im Bytearray ab dem 8 Bytes gesendet werden sollen.
    uint16_t pos = ( maxUSBDataBytes - bytesRemaining );
    uint8_t i = 0;
    for ( i = 0; i < len; i++ ) // Schleife über die zu übergebenen Bytes.
    {
        // Das aktuelle Byte an der Position i speichern. Pos wird weiter oben beschrieben.
        if ( pos + i+1 <= maxUSBDataBytes )
            data[i] = dataBytes[ pos + i ]; // Auslesen eines Bytes aus ddem Daten-Array
        else
        { // Ende des Testdatens erreicht, Übertragung wird beendet
            LED_YELLOW_PORT  = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);
            bytesRemaining = 0;
            return i; // Anzahl der geschriebenen Bytes zurückliefern.
        }
    }
    
    // Wenn noch 8 Bytes übrig sind wurden USB_DATA_BYTES Bytes übertragen -> Maximum
    // erreicht.
    if ( bytesRemaining <= 8 )
    {
        LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);
    }
    bytesRemaining -= len;

    return len;
}

/* ------------------------------------------------------------------------- */

/* usbFunctionWrite() wird aufgerufen wenn der PC auf den AVR schreibend zugreift.
 * /
uchar usbFunctionWrite(uchar *data, uchar len)
{
    if ( bytesRemaining == 0 )
        return 1; // Ende der Übertragung

    if ( len > bytesRemaining )
        len = bytesRemaining; // Falls mehr Daten übertragen werden sollen als übrig sind.

    LED_YELLOW_PORT = LED_YELLOW_PORT & ~(1 << LED_YELLOW_PIN);

    uint16_t pos = ( maxUSBDataBytes - bytesRemaining ); // Berechnen der Position im Datenarray.

    uint8_t i = 0;
    for ( i = 0; i < len; i++ )
    {
        // Daten in das EEPROM Byteweise schreiben.
        dataBytes[pos + i] = data[i];
    }

    if ( bytesRemaining <= 8 ) // Wenn hier noch 8 Bytes übrig sind wurden alle USB_DATA_BYTES Bytes übernommen. USB_DATA_BYTES = Maximum.
    {
        LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);
    }

    bytesRemaining -= len;
    return bytesRemaining == 0; // return 1 if this was the last chunk 
}*/

/* ------------------------------------------------------------------------- */
/* usbFunctionDescriptor() wird aufgerufen vom USBTreiber.
 * Als Parameter wird der Request vom PC erwartet.
 * Zurückgeliefert wird die Größe des entsprechenden Descriptors.
 * Die Funktion wir dausschließlich vom USB-Treiber aufgerufen.
 */
uchar usbFunctionDescriptor(usbRequest_t *rq)
{

    if ( rq->wValue.bytes[1] == USBDESCR_HID )
    {
        usbMsgPtr = (uchar *)usbDescriptorConfiguration+18;
        return 9 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3;
    } else if ( rq->wValue.bytes[1] == USBDESCR_CONFIG )
    {
        usbMsgPtr = (uchar *)usbDescriptorConfiguration;
        return sizeof(usbDescriptorConfiguration);
    } else if ( rq->wValue.bytes[1] == USBDESCR_DEVICE )
    {
        usbMsgPtr = (uchar *)usbDescriptorDevice;
        return sizeof(usbDescriptorDevice);
    } else if ( rq->wValue.bytes[1] == USBDESCR_HID_REPORT )
    {
        usbMsgPtr = (uchar *)usbHidReportDescriptor;
        return maxUSBHidReportDescriptorBytes; // return size
        //return USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH; // return size
    } else if ( rq->wValue.bytes[1] == USBDESCR_STRING )
    {
        if ( rq->wValue.bytes[0] == 1 ) // Vendor
        {
            usbMsgPtr = (uchar *)usbDescriptorStringVendor;
            return USB_PROP_LENGTH(usbDescriptorStringVendor[0]);
        } else if ( rq->wValue.bytes[0] == 2 ) // Device
        {
            usbMsgPtr = (uchar *)usbDescriptorStringDevice;
            return USB_PROP_LENGTH(usbDescriptorStringDevice[0]);
        } else if ( rq->wValue.bytes[0] == 3 ) // SerialNumber
        {
            usbMsgPtr = (uchar *)usbDescriptorStringSerialNumber;
            return USB_PROP_LENGTH(usbDescriptorStringSerialNumber[0]);
        }
    }

    return 0;
}

/* ------------------------------------------------------------------------- */
/* usbFunctionSetup() wird ausschließlich vom USB-Treiber aufgerufen.
 * Definiert die Verhaltensweise was beim lesen oder schreiben ausgeführt
 * werden soll.
 */
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data;

    if ( ( rq->bmRequestType & USBRQ_TYPE_MASK ) == USBRQ_TYPE_CLASS )
    {   // HID class request
        if ( rq->bRequest == USBRQ_HID_GET_REPORT )
        { // wValue: ReportType (highbyte), ReportID (lowbyte)
            // since we have only one report type, we can ignore the report-ID

            bytesRemaining = maxUSBDataBytes;
            usbMsgPtr = &dataBytes[0];

            return USB_NO_MSG; // call usbFunctionRead()

        /*} else if ( rq->bRequest == USBRQ_HID_SET_REPORT )
        {
            // since we have only one report type, we can ignore the report-ID
            //bytesRemaining = maxUSBDataBytes;
            return maxUSBDataBytes;  // usbFunctionWrite() wird aufgerufen*/
        } else if(rq->bRequest == USBRQ_HID_GET_IDLE)
        {
            usbMsgPtr = &idleRate;
            return 1;
        } else if ( rq->bRequest == USBRQ_HID_SET_IDLE )
        {
            idleRate = rq->wValue.bytes[1];
        }
    }
    return 0;
}


