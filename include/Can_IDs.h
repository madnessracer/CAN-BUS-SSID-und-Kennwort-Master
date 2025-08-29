
#ifndef __CAN_IDS_H__
#define __CAN_IDS_H__

#define MessageBasisID 0x3E8 // Zum Testen ID 1000 muss dann angepasst werden
#define WIFI_Name "Master"
#define OTA_On_Off (MessageBasisID + 31)
#define IP_Send_to_CAN (MessageBasisID + 32)
#define OtaDevieID (MessageBasisID + 33)

#endif
