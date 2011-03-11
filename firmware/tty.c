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

#include "tty.h"

/* ------------------------------------------------------------------------- */
void tty_init()
{

    /**/
    // UART initialisieren
    cli();

    uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(9600, F_CPU)); // Baudrate = 9600
    //uart_init(UART_BAUD_SELECT(9600, F_CPU)); // Baudrate = 9600

    sei();

    //UDR0 = 'a';
    //uart_puts("test");

    stdout = &_stdout; /* Allow printf over UART */

    tty_config.echo = TTY_ECHO_ON;

}

/* ------------------------------------------------------------------------- */
/* Allow printf over UART */
static int _uart_putc(char c, FILE *stream)
{
    //uart_putc(c); // Doesn't work atm.

    while ( !(UCSR0A & (1<<UDRE0) ) );

    UDR0 = c;

    return 0;
}

/* ------------------------------------------------------------------------- */
void tty_pollTerminal(void)
{

    char c = uart_getc(); // Lesen eines Byte vom UART Puffer.

    if ( c & UART_NO_DATA )
        return;

    // Buffer solange füllen bis ein Zeilenumbruch erreicht wurde oder die maximale anzahl der gepufferten
    // zeichen erreicht wurde
    if ( c != 0 && c != '\r' ) 
    {
		if ( c == 0x7f && tty_cb_pos > 0 && tty_config.echo ) // Wenn Zeichen vorhanden sind wird das letzte gelöscht.
		{ // Backspace
			printf_P(_str_bb); // Zeichen mit Space auf der Ausgabe überschreiben
			tty_buff[tty_cb_pos] = 0x00; // ein Zeichen löschen im Array durch 0x00 ersetzen
			tty_cb_pos--;
        }
        // Die Anzahl der Zeichen darf TTY_MAX_CMD_LINE_LEN minus '\0' nicht überschreiten.
        // Zudem ist tty_cb_pos immer eins höher als die aktuelle Anzahl der Zeichen im String.
        if ( tty_cb_pos >= TTY_MAX_CMD_LINE_LEN -2 )
            return;

        /*
         * new data available from UART
         * check for Frame or Overrun error
         */
        if ( c & UART_FRAME_ERROR )
        {
            /* Framing Error detected, i.e no stop bit detected */
            uart_puts_P("UART Frame Error: ");
        }
        if ( c & UART_OVERRUN_ERROR )
        {
            /* 
             * Overrun, a character already present in the UART UDR register was 
             * not read by the interrupt handler before the next character arrived,
             * one or more received characters have been dropped
             */
            uart_puts_P("UART Overrun Error: ");
        }
        if ( c & UART_BUFFER_OVERFLOW )
        {
            /* 
             * We are not reading the receive buffer fast enough,
             * one or more received character have been dropped 
             */
            uart_puts_P("Buffer overflow error: ");
        }

		// Steuerzeichen abfangen
        if ( c >= 32 && c <= 126 )
        { // Keine Steuerzeichen
			// Kein lokales Echo auf dem Host nötig, jedes Zeichen wird zurück gesendet.
			// Es ist auch kein standardisiertes Terminal.
			if ( tty_config.echo )
				printf_P(_str_char, c);

			tty_buff[tty_cb_pos] = c;
			tty_cb_pos++;
		} else if ( c == 0x09 ) 
        { // Tab
			tty_buff[tty_cb_pos] = 32; // durch Space ersetzen
			tty_cb_pos++;
		} else if ( c == 0x1b && tty_cb_pos > 0 )
        { // ESC
            printf_P(_str_ret_gt);
            tty_cb_pos = 0; // Kommando abbrechen
        }

        if ( tty_cb_pos > TTY_MAX_CMD_LINE_LEN ) // Bevor der Buffer überläuft, wird "aufgeräumt";
            tty_cb_pos = 0;

    }
    else if ( c == '\r' ) // Zeilenende prüfen
    {

        if ( tty_config.read_mode == TTY_READ_MODE_COMMAND ) // Programmodus == 0
        {
            tty_buff[tty_cb_pos] = '\0'; // Stringende festlegen
            tty_cb_pos = 0;

            if ( tty_config.echo )
                printf_P(_str_ret); // Zeilenumbruch senden.

            if (tty_executeCmd(tty_buff))
            {
                // Das Kommando wurde korrekt ausgeführt.
                if (tty_config.read_mode > TTY_READ_MODE_COMMAND)
                {
                    // Es werden Daten zeilenweise eingegeben
                    return;
                }
            } else {
                if (strlen(tty_buff) > 0)
                    printf_P(_str_error); // Kein gültiges Kommando.
            }
            printf_P(_str_ret);
            if ( tty_config.echo )
                printf_P(_str_gt); // Neuer Promt...

        } else { // read_mode != 0
            // Einlesen der USB_HID_DESCRIPTOR Bytes oder DatenBytes

            tty_buff[tty_cb_pos] = '\0'; // Stringende festlegen
            tty_cb_pos = 0;

            if ( ! strcmp_P((char*)tty_buff, _str_end) )
            { // Es wurde das Ende der Daten angegeben

                printf_P(_str_ret);
                if ( tty_config.echo )
                    printf_P(_str_gt);

                if ( tty_config.read_mode == TTY_READ_MODE_HID_DESCRIPTOR )
                {
                    // Länge der des Descriptors speichern und
                    // die den Konfigurations Descriptor anpassen.
                    maxUSBHidReportDescriptorBytes = tty_ud_pos;
                    usbDescriptorConfiguration[25] = maxUSBHidReportDescriptorBytes & 0xFF;
                    usbDescriptorConfiguration[26] = maxUSBHidReportDescriptorBytes >> 8;
                }
#ifdef WITH_INTERPRETER
                else if ( tty_config.read_mode == TTY_READ_MODE_USB_DATA_SEQ ) //  Länge der Sequenzdaten speichern
                    usbDataSequenceBytes = tty_ud_pos;
#endif
				else if ( tty_config.read_mode == TTY_READ_MODE_HID_DATA )
					maxUSBDataBytes = tty_ud_pos;
				
                tty_ud_pos = 0;
                tty_config.read_mode = TTY_READ_MODE_COMMAND; // In den Kommandomdus zurückspringen

            } else { // Weitere Daten folgen

                unsigned int tmp = 0;
                // formatiertes einlesen der Hexadezimalen Bytes wenn der Stig 4 Zeichen besitzt
                if ( sscanf_P((char*)tty_buff, _str_2hex, &tmp ) &&
                     strlen(tty_buff) == 4 )
                {

                    if ( tty_config.read_mode == TTY_READ_MODE_HID_DESCRIPTOR &&
                         tty_ud_pos < USB_CFG_HID_REPORT_DESCRIPTOR_LEN )
                        usbHidReportDescriptor[tty_ud_pos] = tmp; // In USB HID Descriptor eintragen.
#ifdef WITH_INTERPRETER
                    else if ( tty_config.read_mode == TTY_READ_MODE_USB_DATA_SEQ &&
                              tty_ud_pos+1 < USB_MAX_DATA_SEQ_SIZE )
                    {
                        usbDataSequence[tty_ud_pos] = tmp; // In das Datenarray eintragen.
                    }
#endif
					else if ( tty_config.read_mode == TTY_READ_MODE_HID_DATA &&
                              tty_ud_pos < USB_MAX_DATA_BYTES )
						dataBytes[tty_ud_pos] = tmp;
                    else
                    {
                        // Dateneingabe abbrechen, da die Puffer mit der Maximalen Anzahl der Elemente
                        // gefüllt ist.
                        printf_P(_str_minus);
                        printf_P(_str_ret);
                        printf_P(_str_end);
                        printf_P(_str_ret_gt);
                        tty_ud_pos = 0;
                        tty_config.read_mode = TTY_READ_MODE_COMMAND;
                        return;
                    }

                    tty_ud_pos++;
                    printf_P(_str_plus); // Byte wurde übernommen
                } else
                    printf_P(_str_minus); // Eingabe wurde verworfen, war ungültig

                printf_P(_str_ret);
            }
        } // if zu read_mode == 0
    } // if ( c == '\r' ) zu

}

/* ------------------------------------------------------------------------- */

int tty_executeCmd(const char *buffer)
{

    char *command = strtok(buffer, " "); // Kommando aus dem buffer auslesen

    // Schleifenvariable
    unsigned char i;

    // Wandert durch das Array mit Kommando-Strukturen
    const tty_command_t *cmd = tty_commands;

    // sizeof wird von gcc ausgewertet und ist wie eine Konstante,
    // denn beide sizeofs sind zur Compilezeit bekannt
    for (i=0; i < sizeof(tty_commands) / sizeof(tty_command_t); i++)
    {
        const prog_char *text_P;

        // Liest die Startadresse von dem zu vergleichenden String
        text_P = (const prog_char *)pgm_read_word(& cmd->command);

        // Ist das der gesuchte String?
        if ( strcmp_P(command, text_P) )
        {
            // Das eingegebene Kommando stimmt mit keinem der verfügbaren Kommandos überein.
            cmd++;
            continue;
        }

        // Das Kommando wurde gefunden
        int (*func)(int), type;

        tty_ledYellowOn();
        
        // Dann Funktionszeiger und Argument besorgen,
        func = (void(*)(int)) pgm_read_word (& cmd->func);
        type = (int)          pgm_read_word (& cmd->type);

        if (type == TTY_CMD_WITH_STRING_PARAMETER) {
            //Funktion mit String aufrufen.
            char *t = &buffer[0] + strlen_P(text_P)+1;
            func(t);
        } else if (type == TTY_CMD_WITHOUT_PARAMETER) {
            // Funktion ausführen ohne weitere Parameter.
            func(0);
        } else if (type >= (EEP_CFG_USB_STARTS_WITH + TTY_EEP_CFG_USB_OFFSET) &&
                   type < (EEP_CFG_USB_TYPES + TTY_EEP_CFG_USB_OFFSET))
        {
            // Funktion mit EEP-Einstellung aufrufen.
            func(type-TTY_EEP_CFG_USB_OFFSET);
        } else {
            return 0;
        }

        tty_ledYellowOff();
        return 1;
    }

    // text ist nicht in commands
    return 0;
}

/* ------------------------------------------------------------------------- */

void tty_ledRedOn()
{
    LED_RED_PORT = LED_RED_PORT & ~(1 << LED_RED_PIN );
}

void tty_ledRedOff()
{
    LED_RED_PORT = LED_RED_PORT | (1 << LED_RED_PIN );
}

void tty_ledGreenOn()
{
    LED_GREEN_PORT = LED_GREEN_PORT & ~(1 << LED_GREEN_PIN );
}

void tty_ledGreenOff()
{
    LED_GREEN_PORT = LED_GREEN_PORT | (1 << LED_GREEN_PIN );
}

void tty_ledYellowOn()
{
    LED_YELLOW_PORT = LED_YELLOW_PORT & ~(1 << LED_YELLOW_PIN );
}

void tty_ledYellowOff()
{
    LED_YELLOW_PORT = LED_YELLOW_PORT | (1 << LED_YELLOW_PIN );
}

/* ------------------------------------------------------------------------- */
void tty_setInterrupt()
{
    if ( maxUSBDataBytes )
    {
        while( !usbInterruptIsReady() ) {}
        usbSetInterrupt(&dataBytes[0], maxUSBDataBytes);
    }
}

#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
void tty_setInterrupt3()
{
    if ( maxUSBDataBytes )
    {
        while( !usbInterruptIsReady() ) {}
        usbSetInterrupt3(&dataBytes[0], maxUSBDataBytes);
    }
}
#endif

void tty_getUSBReportData()
{
    uint8_t i = 0;
    for ( i = 0; i < maxUSBDataBytes; i++ )
    {
        printf_P(_str_2hex, dataBytes[i]); // Byteweises ausgeben der Daten
        if (((i+1)%20)==0) // Alle 20 Werteeinen Zeilenumbruch einfügen
            printf_P(PSTR("\r\n"));
    }
}

#ifdef WITH_INTERPRETER
void tty_getUSBDataSequence()
{
    uint8_t i = 0;
    // TODO Hier die maximale Anzahl durch parsen der Daten herausfinden
    // und strukturiert anzeigen.
    for ( i = 0; i < usbDataSequenceBytes; i++ )
    {
        printf_P(_str_2hex, usbDataSequence[i]); // Byteweises ausgeben der Daten
        if (((i+1)%20)==0) // Alle 20 Werte einen Zeilenumbruch einfügen
            printf_P(_str_ret);
    }
}

void tty_getUSBReceiveData()
{
    printf_P( _str_udr, usbReceiveData[0], usbReceiveData[1], usbReceiveData[2] );
}
#endif

void tty_getUSBHidDeviceDescriptor()
{
    uint8_t i = 0;
    for ( i = 0; i < maxUSBHidReportDescriptorBytes; i++ )
    { // ausgeben des kompletten Array's
        printf_P(_str_2hex, (unsigned int)usbHidReportDescriptor[i]);
        if (((i+1)%20)==0) // Alle 20 Werteeinen Zeilenumbruch einfügen
            printf_P(_str_ret);
    }
}

void tty_getVendorName()
{
    // Ausgeben des Herstellers.
    uint8_t i = 0;
    int j = ( ( usbDescriptorStringVendor[0] & 0x00ff ) -2 ) / 2;
    printf_P(_str_header, usbDescriptorStringVendor[0]);
    if (!usbDescriptorStringVendor[0])
        return;
    for ( i = 1; i <= j; i++ )
    {
        printf_P(_str_char, (unsigned int)usbDescriptorStringVendor[i]);
    }
}

void tty_getDeviceName()
{
    // Ausgeben des Gerätenamen und Headers
    uint8_t i = 0;
    uint8_t j = ( ( usbDescriptorStringDevice[0] & 0x00FF ) -2 ) / 2;
    printf_P(_str_header, usbDescriptorStringDevice[0]);
    if (!usbDescriptorStringDevice[0])
        return;
    for ( i = 1; i <= j; i++ )
    {
        printf_P(_str_char, usbDescriptorStringDevice[i]);
    }
}

void tty_getSerialNumber()
{
    // Ausgeben der Seriennummer und des Headers
    uint8_t i = 0;
    // Stringlänge ermitteln.
    char j = ( ( usbDescriptorStringSerialNumber[0] & 0x00FF ) -2 ) / 2;
    printf_P(_str_header, usbDescriptorStringSerialNumber[0]);
    if (!usbDescriptorStringSerialNumber[0])
        return;
    for ( i = 1; i <= j; i++ )
    {
        printf_P(_str_char, (unsigned int)usbDescriptorStringSerialNumber[i]);
    }
}

void tty_getUSBConfigVendorID()
{
    uint16_t tmp = usbDescriptorDevice[9] << 8;
    tmp += usbDescriptorDevice[8];
    printf_P(_str_vid, tmp);
    //printf_P(_str_vid, usbDescriptorDevice[9], usbDescriptorDevice[8]);
}

void tty_getUSBConfigDeviceID()
{
    uint16_t tmp = usbDescriptorDevice[11] << 8;
    tmp += usbDescriptorDevice[10];
    printf_P(_str_did, tmp);
    //printf_P(_str_did, usbDescriptorDevice[11], usbDescriptorDevice[10]);
}

void tty_setUSBReportData()
{
    tty_config.read_mode = TTY_READ_MODE_HID_DATA;
}

#ifdef WITH_INTERPRETER
void tty_setUSBDataSequence()
{
    tty_config.read_mode = TTY_READ_MODE_USB_DATA_SEQ;
}

void tty_setUSBReceiveData(char* t)
{
    uint8_t tmp0 = 0;
    uint8_t tmp1 = 0;
    uint8_t tmp2 = 0;
    if ( sscanf_P((char*)t, _str_3_2hex, &tmp0, &tmp1, &tmp2) )
    {
        usbReceiveData[0] = tmp0;
        usbReceiveData[1] = tmp1;
        usbReceiveData[2] = tmp2;
        if ( tmp0 != 0 )
        {
            usb_status.prd = 1;
        } else {
            usb_status.prd = 0;
        }
    }
}
#endif

void tty_setUSBHidDeviceDescriptor()
{
    tty_config.read_mode = TTY_READ_MODE_HID_DESCRIPTOR;
}

void tty_setVendorName(char* t)
{
    uint8_t i = 0;
    // Größe des Daten ermitteln und festlegen
    uint8_t j = strlen(t);
    // Der String darf nur USB_DEVICE_STRING_DESCRIPTION_LEN Zeichen lang sein,
    // da im ersten Element die Länge der Bytefolge steht.
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN+1) ?
                        j :
                        USB_DEVICE_STRING_DESCRIPTION_LEN;
    usbDescriptorStringVendor[0] = USB_STRING_DESCRIPTOR_HEADER(k);
    for ( i = 0; i < k; i++ )
    { // Byteweise kopieren
        usbDescriptorStringVendor[i+1] = t[i];
    }
}

void tty_setDeviceName(char* t)
{
    uint8_t i = 0;
    // Größe des Daten ermitteln und festlegen
    uint8_t j = strlen(t);
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN+1) ?
                    j :
                    USB_DEVICE_STRING_DESCRIPTION_LEN;
    usbDescriptorStringDevice[0] = USB_STRING_DESCRIPTOR_HEADER(k);
    for ( i = 0; i < k; i++ )
    { // Byteweises kopieren
        usbDescriptorStringDevice[i+1] = t[i];
    }
}

void tty_setSerialNumber(char* t)
{
    uint8_t i = 0;
    // Größe des Daten ermitteln und festlegen
    uint8_t j = strlen(t);
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN+1) ? 
                    j :
                    USB_DEVICE_STRING_DESCRIPTION_LEN;
    usbDescriptorStringSerialNumber[0] = USB_STRING_DESCRIPTOR_HEADER(k);
    for ( i = 0; i < k; i++ )
    { // Byteweise kopieren
        usbDescriptorStringSerialNumber[i+1] = t[i];
    }
}

void tty_setVendorHeader(char *t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_4hex, &tmp) )
    {
        usbDescriptorStringVendor[0] = ( tmp & 0x00FF )
                     | ((( tmp & 0xFF00 ) >> 8) << 8);
    }
}

void tty_setSerialNumberHeader(char *t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_4hex, &tmp) )
    {
        usbDescriptorStringSerialNumber[0] = ( tmp & 0x00FF )
                       | ((( tmp & 0xFF00 ) >> 8) << 8);
    }
}

void tty_setDeviceNameHeader(char *t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_4hex, &tmp) )
    {
        usbDescriptorStringDevice[0] = ( tmp & 0x00FF ) | ((( tmp & 0xFF00 ) >> 8) << 8);
    }
}

void tty_setUSBConfigVendorID(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_4hex, &tmp) )
    {
        usbDescriptorDevice[8] = (char)(tmp & 0x00FF);
        usbDescriptorDevice[9] = (char)((tmp & 0xFF00) >> 8);
    }
}

void tty_setUSBConfigDeviceID(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_4hex, &tmp) )
    {
        usbDescriptorDevice[10] = (char)(tmp & 0x00FF);
        usbDescriptorDevice[11] = (char)((tmp & 0xFF00) >> 8);
    }
}

/* ------------------------------------------------------------------------- */

void tty_Help()
{
    printf_P(HELP_MSG);
}

void tty_startBootloader()
{
    printf_P(_str_bl);
    wdt_enable(0);
    while(1) {};
}

void tty_setEcho(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, _str_decimal, &tmp) )
    {
        if ( tmp )
            tty_config.echo = TTY_ECHO_ON;
        else
            tty_config.echo = TTY_ECHO_OFF;
    }
}

void tty_toggleProveReceiveData(void)
{
    usb_status.prd = !usb_status.prd;
}

/* ------------------------------------------------------------------------- */


