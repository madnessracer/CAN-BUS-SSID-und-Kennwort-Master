# CAN BUS SSID und Kennwort Master

## Projektbeschreibung
Dieses Projekt ermöglicht die Verwaltung von WLAN-SSID und Passwort über den CAN-Bus mit einem ESP32. Die Konfiguration und Steuerung erfolgt über CAN-Nachrichten, sodass z. B. OTA-Updates und Netzwerkwechsel remote durchgeführt werden können.

## Hauptfunktionen
- Empfang und Verarbeitung von SSID und Passwort über den CAN-Bus
- Speicherung der Zugangsdaten im Dateisystem (LittleFS)
- OTA-Update (Over-the-Air) per CAN-Bus aktivierbar
- Scannen und Übertragung von verfügbaren WLAN-Netzwerken
- Senden von Status und IP-Adresse über den CAN-Bus

## Hardware
- ESP32 mit CAN-Bus-Modul (z. B. T-CAN485)
- Anschluss: TX=GPIO27, RX=GPIO26, CAN-BUS Enable=GPIO23
- I2C für Sensoren: SDA=GPIO25, SCL=GPIO33

## Wichtige CAN-IDs
- SSID/Passwort-Empfang: 3000
- OTA-Steuerung: 0x407
- Status/Antworten: ab 0x259

## Dateistruktur
- `src/main.cpp`: Hauptprogramm
- `include/`: Header-Dateien für Funktionen und Konfiguration
- `lib/`: Bibliotheken (z. B. ESP32-Arduino-CAN)
- `platformio.ini`: Projektkonfiguration

## Nutzung
1. Projekt mit PlatformIO öffnen und auf ESP32 flashen
2. CAN-Bus anschließen und konfigurieren
3. SSID und Passwort per CAN-Nachricht senden (siehe Codebeispiele)
4. OTA-Update per CAN-Bus aktivieren
5. Status und IP-Adresse werden über CAN-Bus zurückgemeldet

## Beispiel: SSID und Passwort setzen
Sende eine CAN-Nachricht mit ID 3000 und den entsprechenden Datenbytes für SSID und Passwort.


## Beispiel: OTA aktivieren
Sende eine CAN-Nachricht mit ID 0x407 und Datenbytes `0x01 0x01`.

## Beispiel: OTA deaktivieren
Sende eine CAN-Nachricht mit ID 0x407 und Datenbytes `0x01 0x00`.

## Hinweise
- Kommentare in der `platformio.ini` immer mit `;` beginnen
- Für Speicheroptimierung werden char-Arrays statt String-Objekten verwendet
- Weitere Details siehe Quellcode und Header-Dateien

---

© 2025 madnessracer
