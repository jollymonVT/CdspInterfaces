/***************************************************************************//**
 * COPYRIGHT 2020 CONNECTED DEVELOPMENT, INC
 *
 * ALL RIGHTS RESERVED BY AND FOR THE EXCLUSIVE BENEFIT OF
 * CONNECTED DEVELOPMENT, INC.
 *
 * CONNECTED DEVELOPMENT, INC - CONFIDENTIAL AND PROPRIETARY
 * INFORMATION AND/OR TRADE SECRET.
 *
 * NOTICE: ALL CODE, PROGRAM, INFORMATION, SCRIPT, INSTRUCTION,
 * DATA, AND COMMENT HEREIN IS AND SHALL REMAIN THE CONFIDENTIAL
 * INFORMATION AND PROPERTY OF CONNECTED DEVELOPMENT, INC.
 * USE AND DISCLOSURE THEREOF, EXCEPT AS STRICTLY AUTHORIZED IN A
 * WRITTEN AGREEMENT SIGNED BY CONNECTED DEVELOPMENT, INC IS PROHIBITED.
 *
 *******************************************************************************
 * @file
 * @brief  Header file for Multitech MTQN driver code
 ******************************************************************************/

#ifndef APPLICATION_CELLMODEM_MODEMMTQN_H_
#define APPLICATION_CELLMODEM_MODEMMTQN_H_

#include "Modem.h"

class ModemMTQN: public Modem
{
private:
   int16_t WriteBinary(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   uint16_t ReadBinary(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   int16_t WriteHex(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   uint16_t ReadHex(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);

public:
   ModemErr_e SoftReset(void);
   ModemErr_e Init(void);
   ModemErr_e GetRsrp(int& rsrp, int& rsrq);
   ModemErr_e GetModemApn(char *currentApn);
   ModemErr_e GetModemGreeting(char *currentGreeting, int& mode);
   ModemErr_e GetModemMno(ModemMNO_e& mno);
   ModemErr_e SetModemApn(const char *apn);
   ModemErr_e SetModemGreeting(const char *greting, int mode);
   ModemErr_e SetModemMno(ModemMNO_e mno);
   ModemErr_e SetPDPContext(void);
   ModemRegStatus_e GetRegistrationStatus(void);
   ModemRegStatus_e WaitForRegistration(uint32_t timeout);
   int16_t Write(unsigned char *buffer, uint16_t len, uint32_t timeout_ms);
   uint16_t Read(unsigned char *buffer, uint16_t len, uint32_t timeout_ms);
   ModemErr_e NetworkConnect(const char *addr, int port);
   ModemErr_e NetworkDisconnect(void);
};

#endif /* APPLICATION_CELLMODEM_MODEMMTQN_H_ */
