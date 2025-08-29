#ifndef __CAN_INPUT_OTA_H__
#define __CAN_INPUT_OTA_H__

char PasswordIn[33];
boolean SSID_PASSWORT_Senden = false;

void CanInputOTA()
{
  if (rx_frame.MsgID != 3000) return;// Nur wenn die richtige CAN-ID gefunden wurde
  // WIFI Sann aufrufen
  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x09)
  {
    WifiScan();
  }
  // ENDE WIFI Sann aufrufen

  // Ausgewälte SSID übernehmen
  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x01)
  {
    WifiSsidAuswahl(rx_frame.data.u8[2] - 1);
  }
  // ENDE Ausgewälte SSID übernehmen

  // WIFI Passwort übernehmen und Speichern ###########################################################################
  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x02)
  {
    PasswordIn[0] = rx_frame.data.u8[2];
    PasswordIn[1] = rx_frame.data.u8[3];
    PasswordIn[2] = rx_frame.data.u8[4];
    PasswordIn[3] = rx_frame.data.u8[5];
    PasswordIn[4] = rx_frame.data.u8[6];
    PasswordIn[5] = rx_frame.data.u8[7];
  }

  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x03)
  {
    PasswordIn[6] = rx_frame.data.u8[2];
    PasswordIn[7] = rx_frame.data.u8[3];
    PasswordIn[8] = rx_frame.data.u8[4];
    PasswordIn[9] = rx_frame.data.u8[5];
    PasswordIn[10] = rx_frame.data.u8[6];
    PasswordIn[11] = rx_frame.data.u8[7];
  }

  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x04)
  {
    PasswordIn[12] = rx_frame.data.u8[2];
    PasswordIn[13] = rx_frame.data.u8[3];
    PasswordIn[14] = rx_frame.data.u8[4];
    PasswordIn[15] = rx_frame.data.u8[5];
    PasswordIn[16] = rx_frame.data.u8[6];
    PasswordIn[17] = rx_frame.data.u8[7];
  }

  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x05)
  {
    PasswordIn[18] = rx_frame.data.u8[2];
    PasswordIn[19] = rx_frame.data.u8[3];
    PasswordIn[20] = rx_frame.data.u8[4];
    PasswordIn[21] = rx_frame.data.u8[5];
    PasswordIn[22] = rx_frame.data.u8[6];
    PasswordIn[23] = rx_frame.data.u8[7];
  }

  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x06)
  {
    PasswordIn[24] = rx_frame.data.u8[2];
    PasswordIn[25] = rx_frame.data.u8[3];
    PasswordIn[26] = rx_frame.data.u8[4];
    PasswordIn[27] = rx_frame.data.u8[5];
    PasswordIn[28] = rx_frame.data.u8[6];
    PasswordIn[29] = rx_frame.data.u8[7];
  }

  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x07)
  {
    PasswordIn[30] = rx_frame.data.u8[2];
    PasswordIn[31] = rx_frame.data.u8[3];

    String test = PasswordIn;
    test.trim();
    PASSWORD_Schreiben(test);
  }
  // ENDE WIFI Passwort übernehmen und Speichern ######################################################################
  
  // WIFI SSID und PASSWORT Anzeigen ##################################################################################
  if (rx_frame.MsgID == 3000 && rx_frame.data.u8[0] == OtaDevieID && rx_frame.data.u8[1] == 0x08)
  {
    SSID_PASSWORT_Senden= true;
    delay(100);
    Aktuelle_SSID_Senden();
    delay(100);
    Aktuelle_PASSWORT_Senden();
  }
  // ENDE WIFI SSID und PASSWORT Anzeigen #############################################################################
}

#endif