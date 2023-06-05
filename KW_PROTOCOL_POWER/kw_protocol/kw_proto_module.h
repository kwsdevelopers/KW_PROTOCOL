/**
 *
 *	\file		kw_proto_module.h
 *	\brief	Описание интерфейса модуля протокола  
 *
 *
 */

#ifndef __KW_PROTO_MODULE_H
#define __KW_PROTO_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_can.h"
#include "kw_protocol.h"


//-------------- константы  ------------------------------------


typedef enum
{
  POWER_MODULE_ADDR     = 0xC8,
  DISPLAY_MODULE_ADDR   = 0xDC,
  KIP6_MODULE_ADDR      = 0xF0
}MODULE_ADDRESS_ENUM;



//-------------- типы данных ------------------------------------

///< Указатель на функцию инициализации модуля
typedef void      ( *func_mod_init_t )        ( void );

///< Указатель на функцию обработки кадра CAN
typedef uint32_t  ( *func_mod_msg_develope_t )( kw_can_msg_t *p_msg );


///< Указатель на функцию обработки тика системного таймера
typedef uint32_t  ( *func_mod_tick_operate_t )( void );    

///< Указатель на функцию специфических операций
typedef uint32_t  ( *func_mod_special_operation_t )( PROTO_SPC_OPERATION_ENUM operation, uint32_t param );    



///< Тип данных, который описывает интерфейс модуля протокола
typedef struct
{
  func_mod_init_t               mod_init;
  func_mod_msg_develope_t       mod_msg_develope;
  func_mod_tick_operate_t       mod_tick_operate;
  func_mod_special_operation_t  mod_special_operation;
}
kw_proto_module_interface_t;


#ifdef __cplusplus
}
#endif

#endif //__KW_PROTO_MODULE_H
