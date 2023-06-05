/**
 *
 *	\file		kw_proto_vars.h
 *	\brief	Модуль для работы c переменными протокола на CAN шине
 *
 *
 */

#ifndef __KW_PROTO_VARS_POWER_H
#define __KW_PROTO_VARS_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_vars.h"




extern kw_proto_vars_interface_t vars_power_interface;


void kw_vars_power_init( void );



#ifdef __cplusplus
}
#endif

#endif // __KW_PROTO_VARS_POWER_H






