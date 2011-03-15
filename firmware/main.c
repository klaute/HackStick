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

#ifdef DEBUG
        printf_P(PSTR("\rconnected=%d"), usb_status.connected);
#endif
        if ( usb_status.isd == 1 && usb_status.connected >= 6 )
        {
            //printf("%d\r\n",usb_status.connected);
            printf_P( PSTR("\r\nsending USB Data Sequence...") );
            interpretUSBDataSequence();
            usb_status.isd = 0;
            printf_P( _str_ret );
            printf_P( _str_ret_gt );
        }

    } while (1); // Endlosschleife

}

/* ------------------------------------------------------------------------- */

/* Initialisieren der Hardware */
void init(void)
{

    DDRB  |= (1 << PB1); // Grüne LED als Ausgang
    LED_GREEN_PORT = LED_GREEN_PORT | (1 << LED_GREEN_PIN);

    DDRC  |= (1 << PC4); // Rote LED als Ausgang
    LED_RED_PORT = LED_RED_PORT | (1 << LED_RED_PIN);

    DDRC  |= (1 << PC5); // Gelbe LED als Ausgang
    LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);

    // PD3, PD2 Eingang ohne PullUp, PD6 mit PullUp
    // PD3 und PD2 werden für die USB-Verbindung verwendet.
    // PD6 ist der Jumper.
    DDRD  |= (0 << PD3) | (0 << PD2) | (0 << PD6);
    PORTD |= (0 << PD3) | (0 << PD2) | (1 << PD6);

    // Anzah der Bytes des Descriptors die in der Firmware eingetragen sind.
    //maxUSBHidReportDescriptorBytes = 22;

    usb_descr.USBCfgInterfaceClass = 3; // Hid Device Class

    tty_init();

    _loadEEPROMConfig();

    LED_GREEN_PORT = LED_GREEN_PORT & ~(1 << LED_GREEN_PIN);

    // USB initialisieren
    usbInit();

    usbReset(); // USB Verbindung resetten

    sei(); // Interruptupts global einschalten

    printf_P(WELCOME_MSG);
    
}

/* ------------------------------------------------------------------------- */
/* Laden der Startup Konfiguration aus dem EEPROM */
void _loadEEPROMConfig()
{

    // USB-Konfiguartion aus dem EEPROM laden
    uint16_t config = eeprom_read_word(&eep_usbConfig);

    // TODO aus EEPROM laden oder festlegen der USB Geräteinformationen setzen
    usbDescriptorDevice[4]         = usb_descr.USBCfgDeviceClass;
    usbDescriptorDevice[5]         = usb_descr.USBCfgDeviceSubClass;
    usbDescriptorConfiguration[14] = usb_descr.USBCfgInterfaceClass;
    usbDescriptorConfiguration[15] = usb_descr.USBCfgInterfaceSubClass;
    usbDescriptorConfiguration[16] = usb_descr.USBCfgInterfaceProtocol;
    
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_HID_REPORT_DESCRIPTOR)) )
    {
        eep_readUSBHidReportDescriptor();
    } else {
        // Bei der default einstellung muss die Größe nicht angepasst werden,
        // da der Zeiger bereits auf die korrekte Größe initialisiert wurde.
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
        usbDescriptorStringSerialNumber[0] = USB_STRING_DESCRIPTOR_HEADER(5);
        usbDescriptorStringSerialNumber[1] = '0';
        usbDescriptorStringSerialNumber[2] = '.';
        usbDescriptorStringSerialNumber[3] = '6';
        usbDescriptorStringSerialNumber[4] = '.';
        usbDescriptorStringSerialNumber[5] = '1';
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
#ifdef WITH_INTERPRETER
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_DATA_SEQ)) )
    {
        eep_readUSBDataSequence();
        if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_CONFIG_INTERPRET_ID)) )
        {
            // Wird in der Main ausgeführt
            usb_status.isd = 1;
        }
    }
    if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_RECEIVE_DATA)) )
    {
        eep_readUSBReceiveData();
        if ( (config & (EEP_CFG_VALUE_ON<<EEP_CFG_USB_RECEIVE_DATA_ACTIVE)) )
        {
            usb_status.prd = 1;
            usb_status.isd = 0; // cant't be done simultanous
        }
    }
#endif
}

/* ------------------------------------------------------------------------- */

#ifdef WITH_INTERPRETER
void interpretUSBDataSequence()
{
/**/
    if ( usbDataSequenceBytes < 4 )
        return; // Keine gültige Sequenz vorhanden und der Code soll ausgeführt werden.

    // Header auslesen.
    maxUSBDataBytes    = usbDataSequence[0];
    uint8_t delayStart = usbDataSequence[1];
    uint8_t delay      = usbDataSequence[2];
    uint8_t blockCnt   = usbDataSequence[3];

    // Die maximale/minimale Anzahl der auszugebenden Daten ist ungültig oder keine Blöcke in den Daten vorhanden.
    if ( maxUSBDataBytes > USB_MAX_DATA_BYTES || !maxUSBDataBytes || !blockCnt )
        return; 

    uint16_t arrayPos = 3; // Index ab dem die Blöcke gelesen werden
    
    LED_RED_PORT = LED_RED_PORT ^ (1 << LED_RED_PIN); // Rote LED an

    LED_YELLOW_PORT = LED_YELLOW_PORT ^ (1 << LED_YELLOW_PIN); // Gelbe LED an

    _delay_ms(delayStart); // Pause vor dem Start ausführen

    usbPoll();
    
    // Bytes beginnen zu interpretieren
    uint8_t i;
    for ( i = 0; i < blockCnt; i++ )
    {
        LED_YELLOW_PORT = LED_YELLOW_PORT ^ (1 << LED_YELLOW_PIN); // Gelbe LED blinkt
        arrayPos++;
        uint8_t tupelCnt = usbDataSequence[arrayPos];
        // TODO Hier prüfen ob die Anzahl der Tupel kleiner gleich ist
        // mit der maximalen Anzahl der Bytes in einem Datenpaket.
        if ( tupelCnt > USB_MAX_DATA_BYTES || tupelCnt == 0 )
        {
            printf_P(_str_error);
            printf_P(_str_ret);
            return;
        }
        
        uint8_t j;
        for ( j = 0; j < tupelCnt; j++ )
        {
            arrayPos++;
            uint8_t index = usbDataSequence[arrayPos];
            
            arrayPos++;
            if ( index < maxUSBDataBytes ) // ungültige indizes werden übersprungen
                dataBytes[ index ] = usbDataSequence[arrayPos];
        }

#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
        // Falls ein weiterer Endpoint definiert wurde werden die Daten mit diesem versendet.
        tty_setInterrupt3();
#else
        tty_setInterrupt();
#endif
        _delay_ms(delay + USB_CFG_INTR_POLL_INTERVAL);

        usbPoll();

    }
    LED_YELLOW_PORT = LED_YELLOW_PORT & ~(1 << LED_YELLOW_PIN); // Gelbe LED aus
    LED_RED_PORT = LED_RED_PORT ^ (1 << LED_RED_PIN); // Rote LED aus
/**/
}

#endif

/* ------------------------------------------------------------------------- */
/* Simulieren eines USB disconnect */
void usbReset( void )
{

    LED_GREEN_PORT = LED_GREEN_PORT & ~(1 << LED_GREEN_PIN);
    usbDeviceDisconnect();

    usb_status.connected = 0;

    uchar i = 13;
    do
    {    // USB disconnect (~250ms)
        _delay_ms(20);
        LED_GREEN_PORT = LED_GREEN_PORT ^ (1 << LED_GREEN_PIN); // Grüne LED blinken lassen
        i--;
    } while ( i > 0 );

    usbDeviceConnect();
    //LED_GREEN_PORT = LED_GREEN_PORT | (1 << LED_GREEN_PIN);
    LED_GREEN_PORT = LED_GREEN_PORT ^ (1 << LED_GREEN_PIN); // Grüne LED blinken lassen

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
 */
uchar usbFunctionWrite(uchar *data, uchar len)
{

#ifdef WITH_INTERPRETER
    if ( usb_status.prd == 1 && bytesRemaining == usbReceiveData[0] && len == usbReceiveData[0] ) // Keyboard LED status
    {
        LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);

        if ( (data[ usbReceiveData[1] ] & usbReceiveData[2]) > 0 )
        {
            usb_status.isd = 1; // start interpretation of the data
        }

        return 1;
    }
#endif

    if ( bytesRemaining == 0 )
        return 1; // Ende der Übertragung

    if ( len > bytesRemaining )
        len = bytesRemaining; // Falls mehr Daten übertragen werden sollen als übrig sind.

    LED_YELLOW_PORT = LED_YELLOW_PORT & ~(1 << LED_YELLOW_PIN);

    uint16_t pos = ( maxUSBDataBytes - bytesRemaining ); // Berechnen der Position im Datenarray.

    uint8_t i = 0;
    if (len > 0)
        printf_P( _str_rcv_dta_msg );
    for ( i = 0; i < len; i++ )
    {
        // Daten Byteweise ausgeben
        dataBytes[pos + i] = data[i];
        printf_P( _str_rcv_dta, i, data[i] );
    }
    if (len > 0)
        printf_P( _str_ret_gt );

    if ( bytesRemaining <= 8 ) // Wenn hier noch 8 Bytes übrig sind wurden alle USB_DATA_BYTES Bytes übernommen. USB_DATA_BYTES = Maximum.
    {
        LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN);
    }

    bytesRemaining -= len;
    return bytesRemaining == 0; // return 1 if this was the last chunk 

}/**/

/* ------------------------------------------------------------------------- */
/* usbFunctionDescriptor() wird aufgerufen vom USBTreiber.
 * Als Parameter wird der Request vom PC erwartet.
 * Zurückgeliefert wird die Größe des entsprechenden Descriptors.
 * Die Funktion wir dausschließlich vom USB-Treiber aufgerufen.
 */
uchar usbFunctionDescriptor(usbRequest_t *rq)
{

    if ( usb_status.connected == 15 )
        usb_status.connected = 7; // stay connected


    if ( rq->wValue.bytes[1] == USBDESCR_HID )
    {
        usb_status.connected += 1;

#ifdef DEBUG
        printf("hid\r\n");
#endif

        usbMsgPtr = (uchar *)usbDescriptorConfiguration+18;
        return 9 + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT + 7 * USB_CFG_HAVE_INTRIN_ENDPOINT3;
    } else if ( rq->wValue.bytes[1] == USBDESCR_CONFIG )
    {
        usb_status.connected += 1;

#ifdef DEBUG
        printf("config\r\n");
#endif

        usbMsgPtr = (uchar *)usbDescriptorConfiguration;
        return sizeof(usbDescriptorConfiguration);
    } else if ( rq->wValue.bytes[1] == USBDESCR_DEVICE )
    {
        usb_status.connected += 1;

#ifdef DEBUG
        printf("device\r\n");
#endif

        usbMsgPtr = (uchar *)usbDescriptorDevice;
        return sizeof(usbDescriptorDevice);
    } else if ( rq->wValue.bytes[1] == USBDESCR_HID_REPORT )
    {
        usb_status.connected += 1;

#ifdef DEBUG
        printf("hid_report\r\n");
#endif

        usbMsgPtr = (uchar *)usbHidReportDescriptor;
        return maxUSBHidReportDescriptorBytes; // return size
        //return USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH; // return size
    } else if ( rq->wValue.bytes[1] == USBDESCR_STRING )
    {
        if ( rq->wValue.bytes[0] == 1 ) // Vendor
        {
            usb_status.connected += 1;

#ifdef DEBUG
            printf("str_vendor\r\n");
#endif

            usbMsgPtr = (uchar *)usbDescriptorStringVendor;
            return USB_PROP_LENGTH(usbDescriptorStringVendor[0]);
        } else if ( rq->wValue.bytes[0] == 2 ) // Device
        {
            usb_status.connected += 1;

#ifdef DEBUG
            printf("str_device\r\n");
#endif

            usbMsgPtr = (uchar *)usbDescriptorStringDevice;
            return USB_PROP_LENGTH(usbDescriptorStringDevice[0]);
        } else if ( rq->wValue.bytes[0] == 3 ) // SerialNumber
        {
            usb_status.connected += 1;

#ifdef DEBUG
            printf("str_sn\r\n");
#endif

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
            //usbMsgPtr = &dataBytes[0];

            return USB_NO_MSG; // call usbFunctionRead()

        } else if ( rq->bRequest == USBRQ_HID_SET_REPORT )
        {
            // since we have only one report type, we can ignore the report-ID

            // TODO Die Daten nur empfangen wenn dieser gewünscht ist.
            if ( rq->wLength.word == 2 && usbHidReportDescriptor[3] == 0x06 )
            {
                bytesRemaining = 2;
                return USB_NO_MSG; // durch USB_NO_MSG wird usbFunctionWrite() aufgerufen
            }

        } else if(rq->bRequest == USBRQ_HID_GET_IDLE)
        {
            usbMsgPtr = idleRate;
            return 1;
        } else if ( rq->bRequest == USBRQ_HID_SET_IDLE )
        {
            idleRate = rq->wValue.bytes[1];
        }else if(rq->bRequest == USBRQ_HID_GET_PROTOCOL)
        {
            if (rq->wValue.bytes[1] < 1)
            {
                protocolVer = rq->wValue.bytes[1];
            }
        }
        else if (rq->bRequest == USBRQ_HID_SET_PROTOCOL)
        {
            usbMsgPtr = &protocolVer;
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------------- */

