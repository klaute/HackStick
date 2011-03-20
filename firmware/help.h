
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
\tisd:\tStartet den Interpreter der Sequenzdaten.\r\n\
\tsrd:\tErwartet 3 Parameter im Format 0x00.\r\n\
\t    \tParameter 1 enthält die Anzahl der Bytes die im zu empfangenen Report enthalten sind.\r\n\
\t    \tIst dieser Parameter gleich 0 werden die Empfangenen Daten nicht geprüft.\r\n\
\t    \tParameter 2 enthält den Index innerhalb der Report-Daten, die geprüft werden sollen.\r\n\
\t    \tParameter 3 enthält den den Wert, der an dem angegebenen Index mit einem logischen UND geprüft wird..\r\n\
\tgrd:\tLiefert die im Speicher vorgehaltenen Request Daten.\r\n\
\tprd:\tToggelt das interne Flag ob die Empfangenen Daten geprüft werden sollen oder nicht.\r\n\
\tgvid:\tLiefert die Vendor ID des USB Device.\r\n\
\tsvid:\tSetzt die Vendor ID des USB Device durch die Übergabe dieser im Format 0x0000.\r\n\
\tgdid:\tLiefert die Device ID des USB Device.\r\n\
\tsdid:\tSetzt die Device ID des USB Device durch die Übergabe dieser im Format 0x0000.\r\n\
\tgn:\tLiefert den Device Namen.\r\n\
\tsn:\tSetzt den Device Namen im RAM.\r\n\
\tsnh:\tSetzt den Header des Device Namen im RAM.\r\n\
\t    \tMuss als Parameter im Format 0x00 angegeben werden.\r\n\
\tgvn:\tLiefert den Vendor Namen.\r\n\
\tsvn:\tSetzt den Vendor Namen im RAM.\r\n\
\tsvnh:\tSetzt den Header des Vendor Namen im RAM.\r\n\
\t    \tMuss als Parameter im Format 0x00 angegeben werden.\r\n\
\tgsn:\tLiefert die Seriennummer.\r\n\
\tssn:\tSetzt die Seriennummer im RAM.\r\n\
\tssnh:\tSetzt die Header des Seriennummer im RAM.\r\n\
\t    \tMuss als Parameter im Format 0x00 angegeben werden.\r\n\
\turst:\tEntfernt das USB Device vom Bus und verbindet es neu.\r\n\
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
\tervid:\tLiest die Vendor ID aus dem EEPROM heraus.\r\n\
\tesvid:\tSpeicheert die Vendor ID is das EEPROM.\r\n\
\terdid:\tLiest die Device ID aus dem EEPROM heraus.\r\n\
\tesdid:\tSpeichert die Device ID is das EEPROM.\r\n\
\terrd:\tLiest die Request Daten aus dem EEPROM.\r\n\
\tesrd:\tSpeichert die Request Daten in das EEPROM.\r\n\
\ttlsdsc:\tToggelt das Konfigurations-Bit für das Laden des USB Hid Descriptors beim Start.\r\n\
\ttlsn:\tToggelt das Konfigurations-Bit für das Laden des Device Namen beim Start.\r\n\
\ttlsvn:\tToggelt das Konfigurations-Bit für das Laden des Vendor Namen beim Start.\r\n\
\ttlssn:\tToggelt das Konfigurations-Bit für das Laden der Seriennummer beim Start.\r\n\
\ttlssd:\tToggelt das Konfigurations-Bit für das Laden der USB Sequenz-Daten beim Start.\r\n\
\ttlsrd:\tToggelt das Konfigurations-Bit für das Laden der USB Request-Daten beim Start.\r\n\
\ttprd:\tToggelt das Konfigurations-Bit für das prüfen der USB Request-Daten.\r\n\
\ttlsvid:\tToggelt das Konfigurations-Bit für das Laden der Vendor ID beim Start.\r\n\
\ttlsdid:\tToggelt das Konfigurations-Bit für das Laden der Device ID beim Start.\r\n\
\ttissd:\tToggelt das Konfigurations-Bit für das ausführen von USB Sequenz-Daten beim Start.\r\n\
\tedcfg:\tLöscht alle Bits des Konfigurationsbytes im EEPROM.\r\n\
\thelp:\tGibt diese Hilfe aus.\r\n\
\tttye:\tToggelt das Echo und die Ausgabe des TTY.\r\n\
\tbtldr:\tReset the device and start den USBasp-Loader.\r\n\
\tegcfg:\tGet the configuration word from EEPROM.\r\n\
";

#endif

