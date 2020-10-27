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
 * @brief  Header file for Telit ME310 driver code
 ******************************************************************************/

#ifndef APPLICATION_CELLMODEM_MODEMME310_H_
#define APPLICATION_CELLMODEM_MODEMME310_H_

#include "Modem.h"

#define S12_ESCAPE_TIME 1500 // See AT command manual - guard in ms before +++
#define PWRMON_WAIT_RETRIES 40 // # of 100 ms retries: waiting for PWRMON
#define AT_INIT_RETRIES 10 // # of times on init to retry listen for AT response

class ModemME310: public Modem
{
private:
   int16_t WriteBinary(const char *buffer, uint16_t len,
         uint32_t timeout_ms);
   uint16_t ReadBinary(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   int16_t WriteHex(const char *buffer, uint16_t len,
         uint32_t timeout_ms);
   uint16_t ReadHex(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   ModemErr_e WaitForModemReady(void);
   ModemErr_e CheckModemBandMask(char *commandBuf);
   ModemErr_e ActivateContext(char *commandBuf);

public:
   ModemErr_e SoftReset(void) override;
   ModemErr_e Init(void) override;
   ModemErr_e GetRsrp(int& rsrp, int& rsrq) override;
   ModemErr_e GetModemApn(char *currentApn) override;
   ModemErr_e GetModemGreeting(char *currentGreeting, int& mode) override;
   ModemErr_e GetModemMno(ModemMNO_e& mno) override;
   ModemErr_e SetModemApn(const char *apn) override;
   ModemErr_e SetModemGreeting(const char *greting, int mode) override;
   ModemErr_e SetModemMno(ModemMNO_e mno) override;
   ModemErr_e SetPDPContext(void) override;
   ModemRegStatus_e GetRegistrationStatus(void) override;
   ModemRegStatus_e WaitForRegistration(uint32_t timeout) override;
   int16_t Write(const char *buffer, uint16_t len, uint32_t timeout_ms) override;
   uint16_t Read(unsigned char *buffer, uint16_t len, uint32_t timeout_ms) override;
   ModemErr_e NetworkConnect(const char *addr, int port) override;
   ModemErr_e NetworkDisconnect(void) override;
   void TestCallback (int);
};

#endif /* APPLICATION_CELLMODEM_MODEME310_H_ */
