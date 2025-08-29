#ifndef __I2C_SUBs_H__
#define __I2C_SUBs_H__

AHT10 myAHT10(AHT10_ADDRESS_0X38, AHT20_SENSOR);
byte Temp;
byte Humidity;
uint8_t readStatus = 0;
boolean AHT_Error = false;

void AHT_Start()
{
  if (myAHT10.begin() != true)
  {
    AHT_Error = true;
    Serial.println("AHT ERROR");
    bitSet(Statusbyte_0, 2); 
  }
  else
  {
    Serial.println("AHT OK");
    AHT_Error = false;
    bitClear(Statusbyte_0, 2);
  }
}

void I2C_Scanner()
{
  Serial.println();
  Serial.println("I2C scanner. Scanning ..");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);       // Begin I2C transmission Address (i)
    if (Wire.endTransmission() == 0) // Receive 0 = success (ACK response)
    {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX); // PCF8574 7 bit address
      Serial.println(")");
      count++;
    }
  }
  Serial.print("Found ");
  Serial.print(count, DEC); // numbers of devices
  Serial.println(" device(s).");
}

void Temperatur_messen()
{
  readStatus = myAHT10.readRawData(); // read 6 bytes from AHT10 over I2C

  if (readStatus != AHT10_ERROR || AHT_Error == false)
  {
    Temp = round(myAHT10.readTemperature(AHT10_USE_READ_DATA)) + 50;
    Humidity = round(myAHT10.readHumidity(AHT10_USE_READ_DATA));

    bitClear(Statusbyte_0, 2);

    //Serial.print(Temp - 50);
    //Serial.print("  ");
    //Serial.println(Humidity);
  }
  else
  {
    bitSet(Statusbyte_0, 2);
    Serial.println("ATH ERROR");
  }
}

#endif