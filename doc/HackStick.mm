<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1298296152229" ID="ID_760555389" MODIFIED="1298296218025" TEXT="HackStick">
<node CREATED="1298296219172" ID="ID_933368424" MODIFIED="1298296444339" POSITION="right" TEXT="Hardware">
<node CREATED="1298296459163" ID="ID_581761272" MODIFIED="1298304160492" TEXT="v0.2">
<node CREATED="1298296461692" ID="ID_824192263" MODIFIED="1298296752132" TEXT="ATMega168-20PU">
<node CREATED="1298296468916" ID="ID_489900738" MODIFIED="1298296473261" TEXT="20MHz Quarz"/>
<node CREATED="1298296752899" ID="ID_1991412995" MODIFIED="1298296760356" TEXT="1kB SRAM"/>
<node CREATED="1298296761050" ID="ID_1298196574" MODIFIED="1298296766893" TEXT="16kB Flash"/>
<node CREATED="1298296767642" ID="ID_1146243416" MODIFIED="1298296772871" TEXT="512B EEPROM"/>
</node>
<node CREATED="1298296488955" ID="ID_29972542" MODIFIED="1298296492037" TEXT="Jumper">
<node CREATED="1298296612795" ID="ID_1546574791" MODIFIED="1298296642524" TEXT="JP1 - Zur Aktivierung des Bootloaders"/>
</node>
<node CREATED="1298296647083" ID="ID_1641211723" MODIFIED="1298296685596" TEXT="USB Anschluss"/>
<node CREATED="1298296669018" ID="ID_1556674247" MODIFIED="1298296690227" TEXT="ISP-Anschluss, wie bei Minimexle"/>
<node CREATED="1298296692107" ID="ID_336393522" MODIFIED="1298296699419" TEXT="LED&apos;s">
<node CREATED="1298296700058" ID="ID_1439803416" MODIFIED="1298296701892" TEXT="Rot"/>
<node CREATED="1298296702658" ID="ID_1569295214" MODIFIED="1298296705001" TEXT="Gelb"/>
<node CREATED="1298296705786" ID="ID_1383624960" MODIFIED="1298296707955" TEXT="Gr&#xfc;n"/>
</node>
<node CREATED="1298296804474" ID="ID_1073432306" MODIFIED="1298296890608">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      USB-Schaltung Basiert auf V-USB
    </p>
    <p>
      Circuit &quot;with-zener.sch&quot; (20100715)
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1298298310499" ID="ID_345804981" MODIFIED="1298298321760" TEXT="Kompatibel mit Firmware 0.6"/>
<node CREATED="1298298323107" ID="ID_759932449" MODIFIED="1298298331640" TEXT="USART Interface">
<node CREATED="1298298332281" ID="ID_827269256" MODIFIED="1298298335022" TEXT="9600Baud"/>
<node CREATED="1298298335770" ID="ID_1803125326" MODIFIED="1298298442411" TEXT="Muss ggf. auf RS232 Pegel angepasst werden"/>
<node CREATED="1298298347858" ID="ID_1761231350" MODIFIED="1298298413015">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Anbindung von USB-Chip, zur umsetzung<br />von USB&lt;--&gt;RS232, m&#246;glich.
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1298300341016" ID="ID_588032577" MODIFIED="1298300348753" TEXT="momentan als Lochrsterplatine aufgebaut"/>
</node>
<node CREATED="1298298300969" ID="ID_314378030" MODIFIED="1298304158275" TEXT="v0.3">
<node CREATED="1298300741175" ID="ID_462756617" MODIFIED="1298300782579" TEXT="hier sind nur &#xc4;nderungen aufgez&#xe4;hlt"/>
<node CREATED="1298296461692" ID="ID_39240116" MODIFIED="1298299929083" TEXT="ATMega644-20AU">
<node CREATED="1298296468916" ID="ID_166741154" MODIFIED="1298296473261" TEXT="20MHz Quarz"/>
<node CREATED="1298296752899" ID="ID_1158124122" MODIFIED="1298299844517" TEXT="4kB SRAM"/>
<node CREATED="1298296761050" ID="ID_1801865358" MODIFIED="1298299851219" TEXT="64kB Flash"/>
<node CREATED="1298296767642" ID="ID_355459583" MODIFIED="1298299847851" TEXT="4kB EEPROM"/>
<node CREATED="1298299868995" ID="ID_726363589" MODIFIED="1298299921917" TEXT="TQFP44"/>
</node>
<node CREATED="1298299857346" ID="ID_864058758" MODIFIED="1298299867663" TEXT="ISP-Anschluss wie bei AVR-Dragon">
<node CREATED="1298300182409" ID="ID_1550320537" MODIFIED="1298300204302">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Leider nicht SMD, daher wird dieser<br />nur zur Programmierung aufgesteckt.
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1298300057826" ID="ID_1670243666" MODIFIED="1298300079847" TEXT="FTDI FT242RL mit USART verbunden">
<node CREATED="1298300080434" ID="ID_1641967815" MODIFIED="1298300094593" TEXT="Erm&#xf6;glicht den Zugriff auf das TTY ohne weitere Hardware"/>
<node CREATED="1298300100570" ID="ID_1170621050" MODIFIED="1298300107135" TEXT="Wird von jedem OS direkt erkannt"/>
</node>
<node CREATED="1298300121762" ID="ID_1277963325" MODIFIED="1298300143307" TEXT="Platine wird direkt in den USB Anschluss eingesteckt">
<node CREATED="1298300143905" ID="ID_1694955054" MODIFIED="1298300151279" TEXT="geringe Kosten, da Stecker entfallen"/>
<node CREATED="1298300152217" ID="ID_1888637190" MODIFIED="1298300163015" TEXT="Alle Bauteile in SMD-Bauweise"/>
</node>
<node CREATED="1298300785189" ID="ID_931566616" MODIFIED="1298304193089" TEXT="mit Firmware v0.6 kompatibel">
<node CREATED="1298304200364" ID="ID_1946348749" MODIFIED="1298304218632" TEXT="mit Anpassung auf den AVR"/>
</node>
<node CREATED="1298302675429" ID="ID_588155385" MODIFIED="1298304223615" TEXT="Verbinden von externer Hardware mit USART nicht m&#xf6;glich"/>
<node CREATED="1298302711485" ID="ID_1793151156" MODIFIED="1298302723981" TEXT="Platine muss hergestellt werden"/>
<node CREATED="1298302901155" ID="ID_579614839" MODIFIED="1298302946850" TEXT="Externer SRAM/Flash oder externes EEPROM m&#xf6;glich"/>
</node>
</node>
<node CREATED="1298296445939" ID="ID_1806045077" MODIFIED="1298296448471" POSITION="left" TEXT="Software">
<node CREATED="1298296495868" ID="ID_822527607" MODIFIED="1298296500213" TEXT="Bootloader">
<node CREATED="1298296516940" ID="ID_96451916" MODIFIED="1298296522637" TEXT="USBASP">
<node CREATED="1298296523932" ID="ID_1277545768" MODIFIED="1298296537390" TEXT="Mit meinem Patch f&#xfc;r den Mega168"/>
<node CREATED="1298296541219" ID="ID_1192929681" MODIFIED="1298296610170">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Wird aktiv wenn der Jumper 1
    </p>
    <p>
      (ab HW 0.2) gesettz wird.
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1298296939010" ID="ID_209101390" MODIFIED="1298298285975">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Nach &#220;bertragung von Daten wird die<br />Firmware des HC gestartet.
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1298301807737" ID="ID_630767864" MODIFIED="1298301827040" TEXT="Kann zum Flashen des AVR verwendet werden"/>
<node CREATED="1298301827721" ID="ID_1199338263" MODIFIED="1298301842214" TEXT="Ben&#xf6;tigt 2 kB des internen Flash des AVR"/>
<node CREATED="1298301863848" ID="ID_1346017589" MODIFIED="1298301920681">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Wenn der Jumper JP1 nicht gesettz wird,<br />wird direkt ind ie FW des HC gesprungen.
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
<node CREATED="1298296502020" ID="ID_715302329" MODIFIED="1298296504685" TEXT="Firmware">
<node CREATED="1298296449708" ID="ID_390351284" MODIFIED="1298306904982" TEXT="v0.6">
<node CREATED="1298296901385" ID="ID_1909981689" MODIFIED="1298302289262" TEXT="V-USB 20100715 (USB Treiber)">
<node CREATED="1298297010496" ID="ID_106058487" MODIFIED="1298297033536" TEXT="dynamische Daten">
<node CREATED="1298296993857" ID="ID_1157537372" MODIFIED="1298297140682" TEXT="DescriptorHIDConfiguration">
<node CREATED="1298297364287" ID="ID_335603895" MODIFIED="1298297375849" TEXT="Ger&#xe4;tespezifische Eignschaften"/>
<node CREATED="1298298139681" HGAP="21" ID="ID_1620675219" MODIFIED="1298298150391" TEXT="Interface Class" VSHIFT="-7"/>
<node CREATED="1298298125978" ID="ID_985396041" MODIFIED="1298298131048" TEXT="Interface Subclass"/>
<node CREATED="1298298012764" ID="ID_539802169" MODIFIED="1298298151229" TEXT="Interface Protocol"/>
<node CREATED="1298297338032" ID="ID_1041425424" MODIFIED="1298298215114" TEXT="HID Descriptor">
<node CREATED="1298297914453" ID="ID_1918700603" MODIFIED="1298297929856" TEXT="L&#xe4;nge des DescriptorHIDReport"/>
</node>
<node CREATED="1298297355063" ID="ID_1060013925" MODIFIED="1298298219214" TEXT="Endpoint Konfiguration"/>
</node>
<node CREATED="1298297142680" ID="ID_741256195" MODIFIED="1298302357193" TEXT="DescriptorHIDDevice">
<node CREATED="1298297259936" ID="ID_568671278" MODIFIED="1298297262539" TEXT="Vendor ID"/>
<node CREATED="1298297263263" ID="ID_395954561" MODIFIED="1298297265354" TEXT="Device ID"/>
<node CREATED="1298297811044" ID="ID_1018799729" MODIFIED="1298297827110" TEXT="Device Class"/>
<node CREATED="1298297815284" ID="ID_977836985" MODIFIED="1298297824057" TEXT="Device Subclass"/>
</node>
<node CREATED="1298297043945" ID="ID_578714108" MODIFIED="1298297115009" TEXT="DescriptorHIDReport">
<node CREATED="1298297268943" ID="ID_386807840" MODIFIED="1298297332907" TEXT="HID Descriptor in dem die Art der Kommunikation&#xa;sowie die F&#xe4;higkeiten des Ger&#xe4;tes beschrieben sind."/>
</node>
<node CREATED="1298302332853" ID="ID_75810082" MODIFIED="1298302351267" TEXT="String Informationen">
<node CREATED="1298297153496" ID="ID_689264860" MODIFIED="1298302346770" TEXT="DescriptorStringVendor">
<node CREATED="1298297244856" ID="ID_648672424" MODIFIED="1298297247209" TEXT="Hersteller"/>
</node>
<node CREATED="1298297163872" ID="ID_357807028" MODIFIED="1298302346779" TEXT="DescriptorStringProduct">
<node CREATED="1298297212400" ID="ID_653528173" MODIFIED="1298297236499" TEXT="Ger&#xe4;tebezeichnung"/>
</node>
<node CREATED="1298297172920" ID="ID_244380489" MODIFIED="1298302346789" TEXT="DescriptorStringSerialNumber">
<node CREATED="1298297212400" ID="ID_345084132" MODIFIED="1298297243344" TEXT="Repr&#xe4;sentation der Seriennummer der Ger&#xe4;tes"/>
</node>
<node CREATED="1298302368813" ID="ID_334837145" MODIFIED="1298302396550" TEXT="Erstes Byte im Array ist der Header"/>
<node CREATED="1298302397821" ID="ID_133297231" MODIFIED="1298302443343" TEXT="Abschlie&#xdf;endes \0-Byte entf&#xe4;llt"/>
</node>
<node CREATED="1298299187566" ID="ID_553780029" MODIFIED="1298299190268" TEXT="USB Daten">
<node CREATED="1298299191518" ID="ID_521899004" MODIFIED="1298299198882" TEXT="dynamische L&#xe4;nge"/>
<node CREATED="1298299199534" ID="ID_752592868" MODIFIED="1298299204117" TEXT="dynamischer Inhalt"/>
</node>
</node>
<node CREATED="1298301671666" ID="ID_1538543109" MODIFIED="1298301674260" TEXT="TODO">
<node CREATED="1298303383185" ID="ID_1219740300" MODIFIED="1298303435356" TEXT="Alle Daten dynamisch verwalten um RAM zu sparen"/>
</node>
</node>
<node CREATED="1298298470922" ID="ID_501071082" MODIFIED="1298302191566" TEXT="TTY (Teletype Terminal)">
<node CREATED="1298298478386" ID="ID_1534536221" MODIFIED="1298299021386" TEXT="Kommandos siehe README.console"/>
<node CREATED="1298299083055" ID="ID_660115113" MODIFIED="1298307282847" TEXT="Setzen und auslesen der dynamischen Daten im V-USB Treiber">
<node CREATED="1298307116105" ID="ID_410634060" MODIFIED="1298307118202" TEXT="TODO">
<node CREATED="1298298139681" HGAP="21" ID="ID_1792048888" MODIFIED="1298298150391" TEXT="Interface Class" VSHIFT="-7"/>
<node CREATED="1298298125978" ID="ID_1949515104" MODIFIED="1298298131048" TEXT="Interface Subclass"/>
<node CREATED="1298298012764" ID="ID_14845151" MODIFIED="1298298151229" TEXT="Interface Protocol"/>
<node CREATED="1298297811044" ID="ID_1107672572" MODIFIED="1298297827110" TEXT="Device Class"/>
<node CREATED="1298297815284" ID="ID_647272611" MODIFIED="1298297824057" TEXT="Device Subclass"/>
<node CREATED="1298307134017" ID="ID_1265651360" MODIFIED="1298307186416" TEXT="Anzahl der Interfaces und deren Konfiguration etc."/>
</node>
</node>
<node CREATED="1298299125478" ID="ID_672405486" MODIFIED="1298299153169" TEXT="Speichern und laden der dynamischen Daten in und aus dem EEPROM"/>
<node CREATED="1298299156590" ID="ID_1220315294" MODIFIED="1298299167523" TEXT="Resetten der USB Verbindung"/>
<node CREATED="1298299168606" ID="ID_468835473" MODIFIED="1298299225829" TEXT="Senden von Interrupts an jedem Endpoint (USB Daten werden gesendet)"/>
<node CREATED="1298299381989" ID="ID_920337564" MODIFIED="1298299464820" TEXT="Firmware Start-Verhalten konfigurieren"/>
<node CREATED="1298299180038" ID="ID_1684146136" MODIFIED="1298301086920" TEXT="Ver&#xe4;ndern von USB Daten"/>
<node CREATED="1298301092029" ID="ID_95271393" MODIFIED="1298301654007" TEXT="Setzen und &#xc4;ndern von Header Informationen"/>
<node CREATED="1298303505848" ID="ID_1517404031" MODIFIED="1298303519521" TEXT="TTY Echo abschaltbar"/>
<node CREATED="1298299735571" ID="ID_348854912" MODIFIED="1298301433210" TEXT="TODO">
<node CREATED="1298299226766" ID="ID_1631867487" MODIFIED="1298299236995" TEXT="Empfangen von Daten"/>
<node CREATED="1298299271590" ID="ID_175178987" MODIFIED="1298299371394" TEXT="Starten von Sequenzen"/>
<node CREATED="1298299374509" ID="ID_1453996464" MODIFIED="1298299379865" TEXT="Einlesen von Sequenzen"/>
</node>
</node>
<node CREATED="1298301726233" ID="ID_1589087946" MODIFIED="1298301742441" TEXT="EEPROM Verwaltung">
<node CREATED="1298301742985" ID="ID_560610702" MODIFIED="1298301776050" TEXT="dynamischen Daten aus V-USB"/>
<node CREATED="1298301776642" ID="ID_582272275" MODIFIED="1298302145373" TEXT="Sequenzen von USB Daten"/>
<node CREATED="1298307313968" ID="ID_454765890" MODIFIED="1298307338274" TEXT="Startverhalten der Firmware wird hier abgelegt"/>
</node>
</node>
<node CREATED="1298307208145" ID="ID_1496767637" MODIFIED="1298307211577" TEXT="v0.7">
<node CREATED="1298307230591" ID="ID_391451052" MODIFIED="1298307232688" TEXT="Ideen">
<node CREATED="1298301674810" ID="ID_339579297" MODIFIED="1298382862977" TEXT="Mit sniffen von Daten erm&#xf6;glichen"/>
<node CREATED="1298302457599" ID="ID_123431349" MODIFIED="1298302566425" TEXT="CDC (Communicatins Device Class) m&#xf6;glich,&#xa;durch Implementierung weiterer Logik in den&#xa;USB Function-/Device-Setup Funktionen."/>
</node>
</node>
</node>
</node>
<node CREATED="1298302972564" ID="ID_1840845403" MODIFIED="1298303368696" POSITION="right" TEXT="Ideen">
<node CREATED="1298302975539" ID="ID_1615847548" MODIFIED="1298382809403" TEXT="Daten am USB-Bus mit sniffen">
<node CREATED="1298303134395" ID="ID_1730945440" MODIFIED="1298303155665" TEXT="Als vorhandenes Ger&#xe4;t ausgeben und Daten senden"/>
<node CREATED="1298303163819" ID="ID_1021258689" MODIFIED="1298303180332" TEXT="Loggen von Daten spezieller Device Klassen wie Keyboard"/>
<node CREATED="1298303200211" ID="ID_1017297009" MODIFIED="1298303228218" TEXT="Filter f&#xfc;r zu schnelle Ger&#xe4;te implementieren"/>
</node>
<node CREATED="1298302990971" ID="ID_297884309" MODIFIED="1298303006806" TEXT="Tasteneingaben einer Tastatur simulieren">
<node CREATED="1298303007347" ID="ID_1296819037" MODIFIED="1298303035797" TEXT="simulation einer speziellen (VID/DID) Tastatur"/>
<node CREATED="1298303036643" ID="ID_1102902434" MODIFIED="1298303042647" TEXT="normale HID Tastatur"/>
</node>
<node CREATED="1298303045643" ID="ID_761554441" MODIFIED="1298303061138" TEXT="Simulation von Mausbewegungen und Klicks"/>
<node CREATED="1298303062370" ID="ID_199257536" MODIFIED="1298303074485" TEXT="Simulation eines Massenspeichers">
<node CREATED="1298303078531" ID="ID_1540069886" MODIFIED="1298303088498" TEXT="autorun.inf simulieren"/>
</node>
<node CREATED="1298303231715" ID="ID_1315952802" MODIFIED="1298303248822" TEXT="Aktionen(Sequenzen) auf Signale startet">
<node CREATED="1298303269691" ID="ID_969702734" MODIFIED="1298303328845" TEXT="Anzahl der Bet&#xe4;tigung der CapsLock-Taste"/>
<node CREATED="1298303331402" ID="ID_201219351" MODIFIED="1298303343529" TEXT="Anzahl der Klicks einer anderen Maus"/>
</node>
<node CREATED="1298303446202" ID="ID_1505704259" MODIFIED="1298303455273" TEXT="fuzzer schreiben">
<node CREATED="1298306925844" ID="ID_258709964" MODIFIED="1298306978455">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      tty muss angepasst werden bzw.
    </p>
    <p>
      passendes Protokoll implementiert werden.
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
</map>
