#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <FS.h>
#include <LittleFS.h>
#include <Wire.h>
#include <AHT10.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include <Can_IDs.h>

byte Statusbyte_0;
boolean DatenZumSenden = false;

unsigned long lastmillis = 0;
const unsigned long alleSekunde = 1000;

#include "I2C_SUBs.h"
#include "SecToTime.h"
#include <FileSystem.h>
#include <CAN_SUBs.h>
#include <Wlan_Config.h>
#include <CAN_INPUT_OTA.h>

void setup()
{
  // CAN-BUS einschalten
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);

  Serial.begin(115200);

  delay(1000);

  // CAN-BUS initialisieren
  CAN_cfg.speed = CAN_SPEED_250KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_27;
  CAN_cfg.rx_pin_id = GPIO_NUM_26;
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  ESP32Can.CANInit();

  Serial.print("CAN SPEED :");
  Serial.println(CAN_cfg.speed);
  CAN_Send(IP_Send_to_CAN, 0x03);

  Wire.begin(25, 33); // sda= GPIO 05 /scl= GPIO 25

  // OTA_Start();
}

void loop()
{
  if (OTA_On == 1)
  {
    ArduinoOTA.handle();
  }

  if (WIFIuptade == 0)
  {
    if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
    {
      // CAN BUS Input auswerten ##################################################################################################
      if (rx_frame.FIR.B.FF == CAN_frame_ext)
      {
        CanInputOTA();

        if (rx_frame.MsgID == 201) // FH-ZSG geht in den Standby
        {
          if (rx_frame.data.u8[0] == 0x00 && rx_frame.data.u8[1] == 0x00 && rx_frame.data.u8[2] == 0x00 && rx_frame.data.u8[3] == 0x00 &&
              rx_frame.data.u8[4] == 0x00 && rx_frame.data.u8[5] == 0x00 && rx_frame.data.u8[6] == 0x00 && rx_frame.data.u8[7] == 0x00)
          {
            delay(5000);
          }
        }

        if (rx_frame.MsgID == OTA_On_Off) // OTA AN/Aus
        {
          if (rx_frame.data.u8[0] == 0x01 && rx_frame.data.u8[1] == 0x00) // OTA 1 Aus
          {
            OTA_Stop();
          }
          if (rx_frame.data.u8[0] == 0x01 && rx_frame.data.u8[1] == 0x01) // OTA 1 Ein
          {
            OTA_Start();
          }
        }
      }
    }
  }

  if (millis() - lastmillis >= alleSekunde)
  {
    lastmillis = millis();
  }
}
