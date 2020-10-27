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

#define LOG_ERROR printf
#define LOG_INFO printf
#define LOG_DEBUG printf

ModemErr_e ModemRegisterRxStringCallback(void (*newModemRxStringCallback)(void));
void ModemOsDelay (unsigned int ms);
bool IsPwrMonPinSet(void);
void ModemUsartInit(void);
void DisableModemUartInterrupt(void);
void EnableModemUartInterrupt(void);
void TriggerModemUartTxInterrupt(void);
void RegModem (Modem* newModem);

typedef enum {
	MODEM_STATE_OFF,
	MODEM_STATE_INIT
} ModemState_e;

typedef struct {
	ModemState_e modemState;
	char modemCommand [MODEM_BUFFER_SIZE];
	char modemResponse [MODEM_BUFFER_SIZE];
	ModemState_e nextModemState;
} ModemStateTableEntry;

typedef struct {
	ModemStateTableEntry table[50];
} modemStateTable;
	

#ifdef __cplusplus
}
#endif

#endif /* CELLMODEM_MODEMHAL_H_ */
