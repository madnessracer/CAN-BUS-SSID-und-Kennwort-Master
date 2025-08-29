#ifndef __SECTOTIME_H__
#define __SECTOTIME_H__

byte B_Sekunde;
String S_Sekunde;
byte B_Minute;
String S_Minute;
u_int16_t UI_Stunde;
String S_Stunde;
u_int16_t UI_Tage;
String S_Tage;

void SecToTime(u_int32_t Sekunden, boolean Zeilenschaltung = false)
{
    B_Sekunde = (Sekunden) % 60;
    B_Minute = (Sekunden / 60) % 60;
    UI_Stunde = (Sekunden / 3600) % 24;
    UI_Tage = ((Sekunden / 86400));

    S_Sekunde = String(B_Sekunde);

    if (S_Sekunde.length() == 1)
    {
        S_Sekunde = "0" + S_Sekunde;
    }

    S_Minute = String(B_Minute);

    if (S_Minute.length() == 1)
    {
        S_Minute = "0" + S_Minute;
    }

    S_Stunde = String(UI_Stunde);

    if (S_Stunde.length() == 1)
    {
        S_Stunde = "0" + S_Stunde;
    }

    S_Tage = String(UI_Tage);

    if (S_Tage.length() == 1)
    {
        S_Tage = "000" + S_Tage;
    }

    if (S_Tage.length() == 2)
    {
        S_Tage = "00" + S_Tage;
    }

    if (S_Tage.length() == 3)
    {
        S_Tage = "0" + S_Tage;
    }

    Serial.print(S_Tage);
    Serial.print(" ");
    Serial.print(S_Stunde);
    Serial.print(":");
    Serial.print(S_Minute);
    Serial.print(":");
    Serial.print(S_Sekunde);

    if (Zeilenschaltung)
    {
        Serial.println();
    }
    else
    {
        Serial.print("  ");
    }
}

#endif