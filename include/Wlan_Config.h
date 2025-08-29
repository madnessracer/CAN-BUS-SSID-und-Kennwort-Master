#ifndef __Wlan_Config_H__
#define __Wlan_Config_H__

const char *ssid;
const char *password;

byte WIFIuptade = 0;
byte OTA_On = 0;
int WiFi_Error = 0;
byte SSID_Speicher[50][33];
byte SSID_Byte_arrey[33];
String NeueSSID;

void OTA_Stop()
{
  if (OTA_On == 1) // OTA aus
  {
    OTA_On = 0;
    ArduinoOTA.end();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    CAN_Send(IP_Send_to_CAN, 0x03);
  }
}

void OTA_Start()
{
  CAN_Send(IP_Send_to_CAN, 0x01);

  if (OTA_On == 1) // Wenn schon an war und auf eine andere IP Adresse umgeschalten wird
  {
    OTA_On = 0;
    ArduinoOTA.end();
    WiFi.disconnect();
  }

  // SSID vom FS lesen und übergeben
  String SSID_str = SSID_Lesen();
  int SSID_str_len = SSID_str.length() + 1;
  char SSID_char[SSID_str_len];
  SSID_str.toCharArray(SSID_char, SSID_str_len);
  Serial.println(SSID_char);
  ssid = SSID_char;
  // ENDE SSID vom FS lesen und übergeben

  // PASSWORD vom FS lesen und übergeben
  String PASSWORD_str = PASSWORD_Lesen();
  int PASSWORD_str_len = PASSWORD_str.length() + 1;
  char PASSWORD_char[PASSWORD_str_len];
  PASSWORD_str.toCharArray(PASSWORD_char, PASSWORD_str_len);
  Serial.println(PASSWORD_char);
  password = PASSWORD_char;
  // ENDE PASSWORD vom FS lesen und übergeben

  WiFi.hostname(WIFI_Name);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) // Wait for connection
  {
    delay(100);
    WiFi_Error++;

    if (WiFi_Error == 200)
    {
      CAN_Send(IP_Send_to_CAN, 0x04);
      ESP.restart();
    }
  }

  ArduinoOTA.begin();

  // IPtoCAN();

  ArduinoOTA.onStart([]()
                     { WIFIuptade = 1;
                      CAN_Send(IP_Send_to_CAN, 0x05); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});

  ArduinoOTA.onEnd([]()
                   { WIFIuptade = 0; 
                    CAN_Send(IP_Send_to_CAN, 0x06); });

  OTA_On = 1;
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  IPAddress ip = WiFi.localIP();
  CAN_Send(IP_Send_to_CAN, 0x02, ip[0], ip[1], ip[2], ip[3]);
}

void WifiScan() // WLAN Netzwerke Scannen und an CanBus Senden
{
  Serial.println("Scan start");

  CAN_Send(3000, 0x01);

  // WiFi.scanNetworks will return the number of networks found.
  byte n = WiFi.scanNetworks();
  Serial.println("Scan done");

  if (n == 0)
  {
    Serial.println("no networks found");
    CAN_Send(3001, 0x02); // Kein Netzwerk gefunden
  }
  else
  {
    if (n > 10)
    {
      n = 10;
    }

    Serial.print(n);

    CAN_Send(3001, 0x03, n); // SSID Anzahl gefunden

    String SSID_gefunden;

    Serial.println(" networks found");
    Serial.println("SSID");
    for (int i = 0; i < n; ++i)
    {
      // Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      SSID_gefunden = WiFi.SSID(i); // printf("%-32.32s", WiFi.SSID(i).c_str());

      for (int a = SSID_gefunden.length(); a < 32; ++a)
      {
        SSID_gefunden += " ";
      }

      String message = SSID_gefunden;
      byte plain[message.length()];
      message.getBytes(plain, message.length() + 1);

      for (int b = 0; b < 32; ++b)
      {
        SSID_Speicher[i][b] = plain[b];
      }

      delay(100);
      CAN_Send(3002, i + 1, plain[0], plain[1], plain[2], plain[3], plain[4], plain[5], plain[6]);
      delay(100);
      CAN_Send(3003, i + 1, plain[7], plain[8], plain[9], plain[10], plain[11], plain[12], plain[13]);
      delay(100);
      CAN_Send(3004, i + 1, plain[14], plain[15], plain[16], plain[17], plain[18], plain[19], plain[20]);
      delay(100);
      CAN_Send(3005, i + 1, plain[21], plain[22], plain[23], plain[24], plain[25], plain[26], plain[27]);
      delay(100);
      CAN_Send(3006, i + 1, plain[28], plain[29], plain[30], plain[31]);

      Serial.println(SSID_gefunden);

      delay(10);
    }
  }

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

void WifiSsidAuswahl(byte wert) // SSID auswahl und speichern
{
  for (int b = 0; b < 32; ++b)
  {
    SSID_Byte_arrey[b] = SSID_Speicher[wert][b];
  }

  NeueSSID = String((char *)SSID_Byte_arrey);

  NeueSSID.trim();
  SSID_Schreiben(NeueSSID);
}

void Aktuelle_SSID_Senden() // SSID an CanBus Senden
{
  String SSID_gespeichert = SSID_Lesen();

  for (int a = SSID_gespeichert.length(); a < 32; ++a)
  {
    SSID_gespeichert += " ";
  }

  String message = SSID_gespeichert;
  byte plain[message.length()];
  message.getBytes(plain, message.length() + 1);

  delay(500);
  CAN_Send(3010, plain[0], plain[1], plain[2], plain[3], plain[4], plain[5], plain[6], plain[7]);
  delay(100);
  CAN_Send(3011, plain[8], plain[9], plain[10], plain[11], plain[12], plain[13], plain[14], plain[15]);
  delay(100);
  CAN_Send(3012, plain[16], plain[17], plain[18], plain[19], plain[20], plain[21], plain[22], plain[23]);
  delay(100);
  CAN_Send(3013, plain[24], plain[25], plain[26], plain[27], plain[28], plain[29], plain[30], plain[31]);
}

void Aktuelle_PASSWORT_Senden() // Passwort an CanBus Senden
{
  String SSID_gespeichert = PASSWORD_Lesen();

  for (int a = SSID_gespeichert.length(); a < 32; ++a)
  {
    SSID_gespeichert += " ";
  }

  String message = SSID_gespeichert;
  byte plain[message.length()];
  message.getBytes(plain, message.length() + 1);

  delay(500);
  CAN_Send(3014, plain[0], plain[1], plain[2], plain[3], plain[4], plain[5], plain[6], plain[7]);
  delay(100);
  CAN_Send(3015, plain[8], plain[9], plain[10], plain[11], plain[12], plain[13], plain[14], plain[15]);
  delay(100);
  CAN_Send(3016, plain[16], plain[17], plain[18], plain[19], plain[20], plain[21], plain[22], plain[23]);
  delay(100);
  CAN_Send(3017, plain[24], plain[25], plain[26], plain[27], plain[28], plain[29], plain[30], plain[31]);
}

#endif