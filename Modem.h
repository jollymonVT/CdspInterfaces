 /**************************************************************************//**
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
 * @brief  Header file for generic modem driver
 ******************************************************************************/

#ifndef APPLICATION_CELLMODEM_MODEM_H_
#define APPLICATION_CELLMODEM_MODEM_H_

#include <stdint.h>
#include <string.h>

#define MAX_APN_LEN 50
#define MAX_STRING_LEN 50
#define MODEM_BUFFER_SIZE 500
#define MAX_GREETING_LEN 20
#define ATT_APN "m2m.com.attz"
#define ZIPIT_APN "zipitwireless.com.attz"

/***************************************************************************//**
 * @brief
 *   Modem errors used to signify modem operation status
 ******************************************************************************/

typedef enum
{
   MODEM_OK,
   MODEM_TIMEOUT,
   MODEM_STRING_LEN_ERR,
   MODEM_ERR
} ModemErr_e;

/***************************************************************************//**
 * @brief
 *   Modem registration status
 ******************************************************************************/
typedef enum
{
   REG_NONE,
   REG_HOME,
   REG_SEARCHING,
   REG_REJECTED,
   REG_UNKNOWN,
   REG_ROAM,
   REG_ERR
} ModemRegStatus_e;

/***************************************************************************//**
 * @brief
 *   Socket transfer format
 *   Used for modem sockets - signifies if data transferred over the socket
 *   will be in binary or hex format
 ******************************************************************************/
typedef enum
{
   FORMAT_BINARY,
   FORMAT_HEX
} ModemConnectionFormat_e;

/***************************************************************************//**
 * @brief
 *   Modem Network Operator
 ******************************************************************************/

typedef enum
{
   MNO_ATT = 2, MNO_VERIZON = 3, MNO_SPRINT = 8, MNO_NONE = 255
} ModemMNO_e;

class Modem
{
private:
   char apn[MAX_APN_LEN];
   char greetingString[MAX_GREETING_LEN];
   char rxBuffer[MODEM_BUFFER_SIZE];
   char txBuffer[MODEM_BUFFER_SIZE];
   ModemMNO_e mno;  // Mobile Network Operator
   ModemConnectionFormat_e dataFormat;  // Binary or Hex mode for sockets
   ModemErr_e GetAtRspNthParameter(char **foundString, const uint8_t index,
         char *atString);
   uint16_t rxBufStart = 0;               // Start of unconsumed UART characters
                                       // from the modem
   volatile uint16_t rxBufCurrent = 0;    // Tail of unconsumed UART characters
                                       // from the modem
   volatile uint16_t txBufCurrent = 0;    // Index to next unsent byte waiting to
                                       // be sent to the modem
   volatile uint16_t txBufSize = 0;       // Size of buffer wating to be sent to
                                       // the modem
         
   int GetModemReceiveBufferStartPos(void);
   int GetModemReceiveBufferTailPos(void);
   char GetModemReceivedChar(int pos);
   void SetModemReceiveBufferStartPos(int pos);

public:
   Modem();
   virtual ~Modem();
   virtual ModemErr_e SoftReset(void);
   virtual ModemErr_e HardReset(void);
   virtual ModemErr_e Init(void);
   virtual ModemErr_e GetRsrp(int& rsrp, int& rsrq);
   virtual ModemErr_e GetModemApn(char *currentApn);
   virtual ModemErr_e GetModemMno(ModemMNO_e& mno);
   virtual ModemErr_e GetModemGreeting(char *currentGreeting, int& mode);
   virtual ModemErr_e SetModemApn(const char *apn);
   virtual ModemErr_e SetModemMno(ModemMNO_e mno);
   virtual ModemErr_e SetModemGreeting(const char *greeting,
         int mode);
   virtual ModemErr_e SetPDPContext(void);
   virtual ModemRegStatus_e GetRegistrationStatus(void);
   virtual ModemRegStatus_e WaitForRegistration(uint32_t timeout);
   virtual int16_t Write(const char *buffer, uint16_t len,
         uint32_t timeout_ms);
   virtual uint16_t Read(unsigned char *buffer, uint16_t len,
         uint32_t timeout_ms);
   virtual ModemErr_e NetworkConnect(const char *addr, int port);
   virtual ModemErr_e NetworkDisconnect(void);
   virtual ModemErr_e Configure(const char *newApn, ModemMNO_e newMno,
         const char* newGreeting);

   void UartInit(void);
   ModemErr_e WaitForString(const char *match, int timeout, char *commandBuffer,
         bool printLog);
   ModemErr_e SendWaitForString(const char *sendString, const char *match,
         int timeout, char *commandBuffer, bool printLog);
   ModemErr_e GetBytes(uint16_t len, uint16_t timeout,
         unsigned char *commandBuffer);
   ModemErr_e ModemSendString(const char *sendString, bool printLog);

   ModemErr_e ParseAtRspForInt(int& foundInt, const uint8_t index,
         char *atString);
   ModemErr_e ParseAtRspForString(char *foundString, const uint8_t index,
         char *atString);
   ModemErr_e ModemSendBytes(const char *sendBytes, uint16_t len, bool printLog);
   ModemErr_e ModemSendEscape(void);
   void ClearModemRxBuffer(void);
   bool IsApnCorrect(void);
   bool IsGreetingCorrect(void);
   bool IsMnoCorrect(void);
   void BufferReceivedByte (uint8_t rxChar);
   bool GetNextBufferedTransmitByte (uint8_t* txChar);

   char* GetApn()
   {
      return this->apn;
   }

   bool SetApn(const char *newApn)
   {
      if (strlen(newApn) > MAX_APN_LEN)
      {
         return false;
      }
      strcpy(this->apn, newApn);

      return true;
   }

   ModemConnectionFormat_e GetDataFormat() const
   {
      return dataFormat;
   }

   void SetDataFormat(ModemConnectionFormat_e dataFormat)
   {
      this->dataFormat = dataFormat;
   }

   char* GetGreetingString()
   {
      return greetingString;
   }

   bool SetGreetingString(const char *newGreeting)
   {
      if (strlen(newGreeting) > MAX_GREETING_LEN)
      {
         return false;
      }
      strcpy(this->greetingString, newGreeting);

      return true;
   }

   ModemMNO_e GetMno() const
   {
      return mno;
   }

   void SetMno(ModemMNO_e mno)
   {
      this->mno = mno;
   }
};

#endif /* APPLICATION_CELLMODEM_MODEM_H_ */
