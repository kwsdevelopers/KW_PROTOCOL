/**
 *
 *	\file		kw_proto_enums.h
 *	\brief	Описаны коды, испорльзуемые в протоколе
 *
 *
 */

#ifndef __KW_PROTO_ENUMS_H
#define __KW_PROTO_ENUMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_vars.h"

typedef enum 
{
  PGN_ACK                       = 0xE800, 
  PGN_REQUEST                   = 0xEA00, 
  PGN_TP_DT                     = 0xEB00, 
  PGN_TP_CM                     = 0xEC00, 
  PGN_PROP_SPC_CMD              = 0xEF00,
  PGN_TD                        = 0xFEE6, 
  PGN_PROP_ALARM_STATUS         = 0xFF00,
  PGN_PROP_IN1_VOLTAGE          = 0xFF01,
  PGN_PROP_IN1_CURRENT          = 0xFF02,
  PGN_PROP_IN1_FREQENCY         = 0xFF03,
  PGN_PROP_IN2_VOLTAGE          = 0xFF04,
  PGN_PROP_IN2_CURRENT          = 0xFF05,
  PGN_PROP_IN2_FREQENCY         = 0xFF06,
  PGN_PROP_IN3_VOLTAGE          = 0xFF07,
  PGN_PROP_IN3_CURRENT          = 0xFF08,
  PGN_PROP_IN3_FREQENCY         = 0xFF09,
  PGN_PROP_IN_STATUS            = 0xFF0F,
  PGN_PROP_OUT1_VOLTAGE         = 0xFF11,
  PGN_PROP_OUT1_CURRENT         = 0xFF12,
  PGN_PROP_OUT2_VOLTAGE         = 0xFF13,
  PGN_PROP_OUT2_CURRENT         = 0xFF14,
  PGN_PROP_OUT3_VOLTAGE         = 0xFF15,
  PGN_PROP_OUT3_CURRENT         = 0xFF16,
  PGN_PROP_OUT_FREQENCY         = 0xFF1E,
  PGN_PROP_OUT_PHASE_SHIFT      = 0xFF1F,
  PGN_PROP_BYPASS1_VOLTAGE      = 0xFF21,
  PGN_PROP_BYPASS1_CURRENT      = 0xFF22,
  PGN_PROP_BYPASS2_VOLTAGE      = 0xFF22,
  PGN_PROP_BYPASS2_CURRENT      = 0xFF23,
  PGN_PROP_BYPASS3_VOLTAGE      = 0xFF24,
  PGN_PROP_BYPASS3_CURRENT      = 0xFF25,
  PGN_PROP_BYPASS_FREQENCY      = 0xFF2E,
  PGN_PROP_BYPASS_PHASE_SHIFT   = 0xFF2F,
  PGN_PROP_MIDDLE_VOLTAGE       = 0xFF31,
  PGN_PROP_INVERTER_CURRENT     = 0xFF32,
  PGN_PROP_BATTERY_VOLTAGE      = 0xFF33,
  PGN_PROP_BATTERY_STATUS       = 0xFF34,
  PGN_PROP_MODULES_TEMPERATURE  = 0xFF35,
  PGN_PROP_FUN_SPEED            = 0xFF36,
  PGN_PROP_FUN_SPEED_2          = 0xFF37,
  PGN_PROP_INVERTER_VOLTAGE     = 0xFF38,
  PGN_PROP_SETPOINTS            = 0xFF40,
  PGN_PROP_TEST_RESULT_DETAIL   = 0xFF41,
  PGN_PROP_ID_CARD              = 0xFF60,
  PGN_PROP_IP_ADDR_MASK         = 0xFF70,
  PGN_PROP_IP_GATE_TYPE         = 0xFF71,
  PGN_PROP_MB_SETTINGS          = 0xFF72,
  PGN_PROP_DRY_SETTINGS         = 0xFF73,
  PGN_PROP_LOG_STR              = 0xFFF7 
	
	// Add more here 
}ENUM_PGN_CODES;


/* Control bytes enums */
typedef enum 
{
	CONTROL_BYTE_TP_CM_ABORT = 0xFF,
	CONTROL_BYTE_TP_CM_BAM = 0x20,
	CONTROL_BYTE_TP_CM_EndOfMsgACK = 0x13,
	CONTROL_BYTE_TP_CM_CTS = 0x11,
	CONTROL_BYTE_TP_CM_RTS = 0x10,
	CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED = 0x0,
	CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_NOT_SUPPORTED = 0x1,
	CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_ACCESS_DENIED = 0x2,
	CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_BUSY = 0x3
	/* Add more control bytes here */
}ENUM_CONTROL_BYTES_CODES;




/* Enums for the acknowledgements */
typedef enum 
{
	GROUP_FUNCTION_VALUE_NORMAL = 0x0,
	GROUP_FUNCTION_VALUE_CANNOT_MAINTAIN_ANOTHER_CONNECTION = 0x1,
	GROUP_FUNCTION_VALUE_LACKING_NECESSARY_RESOURCES = 0x2,
	GROUP_FUNCTION_VALUE_ABORT_TIME_OUT = 0x3,
	GROUP_FUNCTION_VALUE_NO_CAUSE = 0xFF
} ENUM_GROUP_FUNCTION_VALUE_CODES;

// 
typedef enum 
{
	SPC_CMD_SWITCH_TO_MODE = 0x01,
	SPC_CMD_WRITE_SETPOINT,
	SPC_CMD_ENTER_PASSWORD,
	SPC_CMD_WRITE_ID_CARD_1,
	SPC_CMD_WRITE_ID_CARD_2,
	SPC_CMD_WRITE_ID_CARD_3,
	SPC_CMD_WRITE_ID_CARD_4,
	SPC_CMD_WRITE_ID_CARD_5,
	SPC_CMD_WRITE_IP_ADR,
	SPC_CMD_WRITE_IP_MASK,
	SPC_CMD_WRITE_IP_GATE,
	SPC_CMD_WRITE_IP_TYPE,
	SPC_CMD_WRITE_MB_SETTINGS,
	SPC_CMD_WRITE_DRY_CONTACTS_SETTINGS,
	SPC_CMD_SET_DATE_TIME,
	SPC_CMD_TEST_START = 0x10,
  
}SPC_CMD_CODES;


typedef enum 
{
	UPS_MODE_OFF = 0x00,
	UPS_MODE_ON,
	UPS_MODE_SLEEP,
	UPS_MODE_STANDBY,
	UPS_MODE_BYPASS,
	UPS_MODE_ONLINE,
	UPS_MODE_ONBATTERY,
	UPS_MODE_SERVICE,
	UPS_MODE_FAULT,
	UPS_MODE_MAX
}UPS_MODE_ENUM;


#ifdef __cplusplus
}
#endif

#endif // __KW_PROTO_ENUMS_H


