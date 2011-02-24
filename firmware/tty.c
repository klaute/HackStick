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

    // UART initialisieren
    uart_init(UART_BAUD_SELECT(9600, F_CPU)); // Baudrate = 9600

    stdout = &_stdout; /* Allow printf over UART */

    tty_config.echo = TTY_ECHO_ON;
}

/* ------------------------------------------------------------------------- */
/* Allow printf over UART */
static int _uart_putc(char c, FILE *stream)
{
    uart_putc(c);
    return 0;
}

/* ------------------------------------------------------------------------- */
void tty_pollTerminal(void)
{

    char c = uart_getc(); // Lesen eines Byte vom UART Puffer.

    if ( c != 0 && c != '\r' ) // Buffer solange füllen bis ein Zeilenumbruch erreicht wurde
    {

        switch ( c ) // Steuerzeichen abfangen
        {
            case 32 ... 126:; // Keine Steuerzeichen
                // Kein lokales Echo auf dem Host nötig, jedes Zeichen wird zurück gesendet.
                // Es ist auch kein standardisiertes Terminal.
                if ( tty_config.echo )
                    printf_P(PSTR("%c"), c);

                tty_buff[tty_cb_pos] = c;
                tty_cb_pos++;
            break;
            case 0x09:; // Tab
                tty_buff[tty_cb_pos] = 32; // durch Space ersetzen
                tty_cb_pos++;
            break;
            case 0x7F:; // Backspace
                if ( tty_cb_pos > 0 && tty_config.echo ) // Wenn Zeichen vorhanden sind wird das letzte gelöscht.
                {
                    printf_P(PSTR("\b \b")); // Zeichen mit Space auf der Ausgabe überschreiben
                    tty_buff[tty_cb_pos] = 0x00; // ein Zeichen löschen im Array durch 0x00 ersetzen
                    tty_cb_pos--;
                }
            break;
            case 0x1b:; // ESC
                if ( tty_cb_pos > 0 )
                {
                    printf_P(PSTR("\r\n>"));
                    tty_cb_pos = 0; // Kommando abbrechen
                }
            break;
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
                printf_P(PSTR("\r\n")); // Zeilenumbruch senden.

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
                    printf_P(PSTR("ERR")); // Kein gültiges Kommando.
            }
            printf_P(PSTR("\r\n"));
            if ( tty_config.echo )
                printf_P(PSTR(">")); // Neuer Promt...

        } else { // read_mode != 0
            // Einlesen der USB_HID_DESCRIPTOR Bytes oder DatenBytes

            tty_buff[tty_cb_pos] = '\0'; // Stringende festlegen
            tty_cb_pos = 0;

            if ( ! strcmp_P((char*)tty_buff, PSTR("E")) )
            { // Es wurde das Ende der Daten angegeben

                printf_P(PSTR("\r\n"));
                if ( tty_config.echo )
                    printf_P(PSTR(">"));

                if ( tty_config.read_mode == TTY_READ_MODE_HID_DESCRIPTOR )
                {
                    maxUSBHidReportDescriptorBytes = tty_ud_pos;
                    usbDescriptorConfiguration[25] = maxUSBHidReportDescriptorBytes & 0xFF;
                    usbDescriptorConfiguration[26] = maxUSBHidReportDescriptorBytes >> 8;
                }
                // TODO prüfen ob dies noh benötigt wird.
                //else if ( tty_config.read_mode == TTY_READ_MODE_HID_DATA ) // Falls wir im Mode 2 sind muss die Länge gespeichert werden.
                    //maxUSBDataBytes = tty_ud_pos;

                tty_ud_pos = 0;
                tty_config.read_mode = TTY_READ_MODE_COMMAND; // In den Kommandomdus zurückspringen

            } else { // Weitere Daten folgen

                unsigned int tmp = 0;
                // formatiertes einlesen der Hexadezimalen Bytes wenn der Stig 4 Zeichen besitzt
                if ( sscanf((char*)tty_buff, "0x%02x", &tmp ) && strlen(tty_buff) == 4 )
                {

                    if ( tty_config.read_mode == TTY_READ_MODE_HID_DESCRIPTOR )
                        usbHidReportDescriptor[tty_ud_pos] = tmp; // In USB HID Descriptor eintragen.
                    else if ( tty_config.read_mode == TTY_READ_MODE_USB_DATA_SEQ )
                        dataBytes[tty_ud_pos] = tmp; // In das Datenarray eintragen.

                    tty_ud_pos++;
                    printf_P(PSTR(" +")); // Byte wurde übernommen
                } else
                    printf_P(PSTR(" -")); // Eingabe wurde verworfen, war ungültig

                printf_P(PSTR("\r\n"));
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
    if ( usbInterruptIsReady() )
    {
        usbSetInterrupt(&dataBytes[0], maxUSBDataBytes);
    }
}

#if (USB_CFG_HAVE_INTRIN_ENDPOINT3 != 0)
void tty_setInterrupt3()
{
    if ( usbInterruptIsReady() )
    {
        usbSetInterrupt3(&dataBytes[0], maxUSBDataBytes);
    }
}
#endif

void tty_getUSBDataSequence()
{
    uint8_t i = 0;
    // TODO Hier die maximale Anzahl durch parsen der Daten herausfinden
    // und strukturiert anzeigen.
    for ( i = 0; i < USB_MAX_DATA_SEQ_SIZE; i++ )
    {
        printf_P(PSTR("0x%02X "), usbDataSequence[i]); // Byteweises ausgeben der Daten
        if (((i+1)%20)==0) // Alle 20 Werte einen Zeilenumbruch einfügen
            printf_P(PSTR("\r\n"));
    }
}

void tty_getUSBHidDeviceDescriptor()
{
    uint8_t i = 0;
    for ( i = 0; i < maxUSBHidReportDescriptorBytes; i++ )
    { // ausgeben des kompletten Array's
        printf_P(PSTR("0x%02X "), (unsigned int)usbHidReportDescriptor[i]);
        if (((i+1)%20)==0) // Alle 20 Werteeinen Zeilenumbruch einfügen
            printf_P(PSTR("\r\n"));
    }
}

void tty_getVendorName()
{
    // Ausgeben des Herstellers.
    uint8_t i = 0;
    int j = ( ( usbDescriptorStringVendor[0] & 0x00ff ) -2 ) / 2;
    printf_P(PSTR("H=0x%02X\r\n"),usbDescriptorStringVendor[0]);
    for ( i = 1; i <= j; i++ )
    {
        printf_P(PSTR("%c"), (unsigned int)usbDescriptorStringVendor[i]);
    }
}

void tty_getDeviceName()
{
    // Ausgeben des Gerätenamen und Headers
    uint8_t i = 0;
    uint8_t j = ( ( usbDescriptorStringDevice[0] & 0x00FF ) -2 ) / 2;
    printf_P(PSTR("H=0x%02X\r\n"),usbDescriptorStringDevice[0]);
    for ( i = 1; i <= j; i++ )
    {
        printf_P(PSTR("%c"), usbDescriptorStringDevice[i]);
    }
}

void tty_getSerialNumber()
{
    // Ausgeben der Seriennummer und des Headers
    uint8_t i = 0;
    // Stringlänge ermitteln.
    char j = ( ( usbDescriptorStringSerialNumber[0] & 0x00FF ) -2 ) / 2;
    printf_P(PSTR("H=0x%02X\r\n"),usbDescriptorStringSerialNumber[0]);
    for ( i = 1; i <= j; i++ )
    {
        printf_P(PSTR("%c"), (unsigned int)usbDescriptorStringSerialNumber[i]);
    }
}

void tty_getUSBConfigVendorID()
{
    printf_P(PSTR("VID=0x%02x%02x"), usbDescriptorDevice[9], usbDescriptorDevice[8]);
}

void tty_getUSBConfigDeviceID()
{
    printf_P(PSTR("DID=0x%02x%02x"), usbDescriptorDevice[11], usbDescriptorDevice[10]);
}

void tty_setUSBDataSequence()
{
    tty_config.read_mode = TTY_READ_MODE_USB_DATA_SEQ;
}


void tty_setUSBHidDeviceDescriptor()
{
    tty_config.read_mode = TTY_READ_MODE_HID_DESCRIPTOR;
}

void tty_setVendorName(char* t)
{
    uint8_t i = 0;
    // Größe des Daten ermitteln und festlegen
    uint8_t j = strlen(t);
    // Der String darf nur USB_DEVICE_STRING_DESCRIPTION_LEN -1 Zeichen lang sein,
    // da im ersten Element die Länge der Bytefolge steht.
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN) ?
                        j :
                        USB_DEVICE_STRING_DESCRIPTION_LEN-1;
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
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN) ?
                    j :
                    USB_DEVICE_STRING_DESCRIPTION_LEN-1;
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
    uint8_t k = (j < USB_DEVICE_STRING_DESCRIPTION_LEN) ?
                    j :
                    USB_DEVICE_STRING_DESCRIPTION_LEN-1;
    usbDescriptorStringSerialNumber[0] = USB_STRING_DESCRIPTOR_HEADER(k);
    for ( i = 0; i < k; i++ )
    { // Byteweise kopieren
        usbDescriptorStringSerialNumber[i+1] = t[i];
    }
}

void tty_setVendorHeader(char *t)
{
	uint16_t tmp = 0;
	if ( sscanf((char*)t, "0x%04x", &tmp) )
	{
	    usbDescriptorStringVendor[0] = ( tmp & 0x00FF )
		             | ((( tmp & 0xFF00 ) >> 8) << 8);
	}
}

void tty_setSerialNumberHeader(char *t)
{
	uint16_t tmp = 0;
	if ( sscanf((char*)t, "0x%04x", &tmp) )
	{
	    usbDescriptorStringSerialNumber[0] = ( tmp & 0x00FF )
		               | ((( tmp & 0xFF00 ) >> 8) << 8);
	}
}

void tty_setDeviceNameHeader(char *t)
{
	uint16_t tmp = 0;
	if ( sscanf((char*)t, "0x%04x", &tmp) )
	{
	    usbDescriptorStringDevice[0] = ( tmp & 0x00FF ) | ((( tmp & 0xFF00 ) >> 8) << 8);
	}
}

void tty_setUSBConfigVendorID(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, PSTR("0x%04x"), &tmp) )
    {
        usbDescriptorDevice[8] = (char)(tmp & 0x00FF);
        usbDescriptorDevice[9] = (char)((tmp & 0xFF00) >> 8);
    }
}

void tty_setUSBConfigDeviceID(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf_P((char*)t, PSTR("0x%04x"), &tmp) )
    {
        usbDescriptorDevice[10] = (char)(tmp & 0x00FF);
        usbDescriptorDevice[11] = (char)((tmp & 0xFF00) >> 8);
    }
}

/* ------------------------------------------------------------------------- */

void tty_setEcho(char* t)
{
    uint16_t tmp = 0;
    if ( sscanf((char*)t, "%d", &tmp) )
    {
        if ( tmp )
            tty_config.echo = TTY_ECHO_ON;
        else
            tty_config.echo = TTY_ECHO_OFF;
    }
}


