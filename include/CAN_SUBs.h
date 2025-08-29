#ifndef __CAN_SUBs_H__
#define __CAN_SUBs_H__

CAN_device_t CAN_cfg; // CAN Config
CAN_frame_t rx_frame;

#define CAN_ON 33
#define CAN_TX_PIN 14
#define CAN_RX_PIN 34

void CAN_Send(uint MesageID, byte MesageByte1 = 0, byte MesageByte2 = 0, byte MesageByte3 = 0, byte MesageByte4 = 0, byte MesageByte5 = 0, byte MesageByte6 = 0, byte MesageByte7 = 0, byte MesageByte8 = 0)
{
  rx_frame.FIR.B.FF = CAN_frame_ext;
  rx_frame.MsgID = MesageID;
  rx_frame.FIR.B.DLC = 8;
  rx_frame.data.u8[0] = MesageByte1;
  rx_frame.data.u8[1] = MesageByte2;
  rx_frame.data.u8[2] = MesageByte3;
  rx_frame.data.u8[3] = MesageByte4;
  rx_frame.data.u8[4] = MesageByte5;
  rx_frame.data.u8[5] = MesageByte6;
  rx_frame.data.u8[6] = MesageByte7;
  rx_frame.data.u8[7] = MesageByte8;

  ESP32Can.CANWriteFrame(&rx_frame);
}

#endif
