/**
 *
 *	\file		kw_protocol.h
 *	\brief	Модуль для конфигурирования протокола для работы по CAN шине
 *
 *
 */

#ifndef __KW_PROTOCOL_H
#define __KW_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_cfg.h"

///< тип данных, описывающий специфическую операцию
typedef enum
{
  SPC_OP_SEND_REQUEST,
  SPC_OP_WRITE_SETPOINT,
  SPC_OP_SET_DATE_TIME,  
  SPC_OP_SWITCH_TO_MODE,  
}PROTO_SPC_OPERATION_ENUM;


///< тип данных, описывающий возможные запросы
typedef enum
{
  REQUEST_POWER_MODULE_SETPOINTS,
  REQUEST_POWER_MODULE_INPUT_LINES_STATUS,  
  REQUEST_KIP6_MODULE_IP_MASK,
  REQUEST_KIP6_MODULE_GATE_TYPE,
  REQUEST_KIP6_MODULE_MB_SETTINGS,
  REQUEST_KIP6_MODULE_DRY_SETTINGS,
}PROTO_REQUEST_ENUM;

///< тип данных, описывающий возможные записи уставок
typedef enum
{
  SETPOINT_POWER_MODULE_OUT_VOLTAGE,                              // Уставка номинального значения выходного напряжения
  SETPOINT_POWER_MODULE_OUT_SHORT_CIRCUT_CURRENT,                 // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
  SETPOINT_POWER_MODULE_IN_VOLTAGE_HI_THRESHHOLD,                 // Уставка верхней границы допустимого входного напряжения ИБП
  SETPOINT_POWER_MODULE_IN_VOLTAGE_LOW_THRESHHOLD,                // Уставка нижней границы допустимого входного напряжения ИБП
  SETPOINT_POWER_MODULE_IN_FREQUENCY_HI_THRESHHOLD,               // Уставка верхней границы допустимой частоты входного напряжения: % от номинального значения
  SETPOINT_POWER_MODULE_IN_FREQUENCY_LOW_THRESHHOLD,              // Уставка нижней границы допустимой частоты входного напряжения: % от номинального значения
  SETPOINT_POWER_MODULE_SWITCHING_MODES_WHEN_ALARM_EVENT,         // Переход между режимами работы модуля ИБП при возникновении аварийного события 	
  SETPOINT_KIP6_MODULE_IP_ADR,                                    // Уставка IP адрес устройства
  SETPOINT_KIP6_MODULE_NET_MASK,                                  // Уставка IP маска сети
  SETPOINT_KIP6_MODULE_GATE,                                      // Уставка IP арес шлюза сети
  SETPOINT_KIP6_MODULE_TYPE,                                      // Уставка тип IP адресации 
  SETPOINT_KIP6_MODULE_MB_SETTINGS,                               // Уставка настройки ModBus
  SETPOINT_KIP6_MODULE_DRY_SETTINGS,                              // Уставка настройки сухих контактов
}PROTO_SETPOINT_ENUM;




#if( KW_PROTO_MODULE == KW_POWER_MODULE )
  #include "kw_proto_module_power.h"
#elif( KW_PROTO_MODULE == KW_DISPLAY_MODULE )
  #include "kw_proto_module_display.h"
#elif( KW_PROTO_MODULE == KW_KIP6_MODULE )
  #include "kw_proto_module_kip6.h"
#endif

// прототипы функций

void kw_proto_init( void );
uint32_t kw_proto_listen(  void );
uint32_t kw_proto_tick_operate( void );
uint32_t kw_proto_special_operation( PROTO_SPC_OPERATION_ENUM operation, uint32_t param );





#ifdef __cplusplus
}
#endif

#endif // __KW_PROTOCOL_H
