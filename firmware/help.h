
#ifndef _HELP_H_
#define _HELP_H_

#define _MSG_HELP_ "usage:\r\n\
\tgdsc:\tLiefert den USB Hid Device Descriptor.\r\n\
\tsdsc:\tErwartet keine Parameter sondern erwartet die Daten Zeilenweise\r\n\
\t     \tim Format 0x00. Da Ende der Daten wird mit einem \"E\" festgelegt,\r\n\
\t     \twelches sich in einer eigenen Zeile befinden muss.\r\n\
\tgdta:\tLiefert die aktuell im Speicher vorgehaltenen USB-Daten.\r\n\
\tsdta:\tFunktionalität wie bei \"sdsc\".\r\n\
\tsint:\tLöst eine Übertragung der im Speicher vorgehaltenen USB-Daten aus.\r\n\
\tsint3:\tLöst eine Übertragung der im Speicher vorgehaltenen USB-Daten\r\n\
\t      \tüber den Interrupt3 Endpoint, aus.\r\n\
\tgsd:\tLiefert die Sequenzdaten zurück.\r\n\
\tssd:\tFunktionalität wie bei \"sdsc\".\r\n\
\tisd:\tStartet den Interpreter der SequenzDaten.\r\n\
\tgcvid:\tLiefert die Vendor ID des USB Device.\r\n\
\tscvid:\tSetzt die Vendor ID des USB Device durch die Übergabe dieser im Format 0x0000.\r\n\
\tgcdid:\tLiefert die Device ID des USB Device.\r\n\
\tscdid:\tSetzt die Device ID des USB Device durch die Übergabe dieser im Format 0x0000.\r\n\
\tgn:\tLiefert den Device Namen.\r\n\
\tsn:\tSetzt den Device Namen im RAM.\r\n\
\tsnh:\tSetzt den Header des Device Namen im RAM.\r\b\
\t    \t\tMuss als Parameter im Format 0x00 angeegben werden.\r\n\
\tgvn:\tLiefert den Vendor Namen.\r\n\
\tsvn:\tSetzt den Vendor Namen im RAM.\r\n\
\tsvnh:\tSetzt den Header des Vendor Namen im RAM.\r\b\
\t    \t\tMuss als Parameter im Format 0x00 angeegben werden.\r\n\
\tgvn:\tLiefert die Seriennummer.\r\n\
\tsvn:\tSetzt die Seriennummer im RAM.\r\n\
\tsvnh:\tSetzt die Header des Seriennummer im RAM.\r\b\
\t    \t\tMuss als Parameter im Format 0x00 angeegben werden.\r\n\
\terdsc:\tLiest den im EEPROM gespeicherten USB Hid Descriptor aus.\r\n\
\tesdsc:\tSpeichert den im RAM vorgehaltenen USB Hid Descriptor in das EEPROM.\r\n\
\tersd:\tLiest die im EEPROM gespeicherten USB Sequenz-Daten aus.\r\n\
\tessd:\tSpeichert die im RAM USB Sequenz-Daten in das EEPROM.\r\n\
\tervn:\tLiest den im EEPROM gespeicherten Vendor Namen aus.\r\n\
\tesvn:\tSpeichert den im RAM vorgehaltenen Vendor Namen in das EEPROM.\r\n\
\tern:\tLiest den im EEPROM gespeicherten Device Namen aus.\r\n\
\tesn:\tSpeichert den im RAM vorgehaltenen Device Namen in das EEPROM.\r\n\
\tersn:\tLiest die im EEPROM gespeicherte Seriennummer aus.\r\n\
\tessn:\tSpeichert die im RAM vorgehaltene Seriennummer in das EEPROM.\r\n\
\ttlsdsc:\tToggelt das Konfigurations-Bit für das Laden des USB Hid Descriptors beim Start.\r\n\
\ttlsn:\tToggelt das Konfigurations-Bit für das Laden des Device Namen beim Start.\r\n\
\ttlsvn:\tToggelt das Konfigurations-Bit für das Laden des Vendor Namen beim Start.\r\n\
\ttlssn:\tToggelt das Konfigurations-Bit für das Laden der Seriennummer beim Start.\r\n\
\ttlssd:\tToggelt das Konfigurations-Bit für das Laden der USB Sequenz-Daten beim Start.\r\n\
\ttlscvid:\tToggelt das Konfigurations-Bit für das Laden der Vendor ID beim Start.\r\n\
\ttlscdid:\tToggelt das Konfigurations-Bit für das Laden der Device ID beim Start.\r\n\
\ttlsiossd:\tToggelt das Konfigurations-Bit für das ausführen von USB Sequenz-Daten beim Start.\r\n\
\tedcfg:\tLöscht alle Bits des Konfigurationsbytes im EEPROM.\r\n\
\thelp:\tGibt diese Hilfe aus.\r\n\
\tttye:\tToggelt das Echo und die Ausgabe des TTY.\r\n\
";

#endif

