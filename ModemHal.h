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
 * @brief  Header file for modem hardware specific routines
 ******************************************************************************/

#ifndef CELLMODEM_MODEMHAL_H_
#define CELLMODEM_MODEMHAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Modem.h"

bool IsPwrMonPinSet(void);
void ModemUsartInit(void);
void RegModem (Modem* newModem);
void sendBytesToModem(char* txBuffer, const char* sendBytes, 
					  uint16_t len, volatile uint16_t* txBufCurrent,
					  volatile uint16_t* txBufSize);
	

#ifdef __cplusplus
}
#endif

#endif /* CELLMODEM_MODEMHAL_H_ */
