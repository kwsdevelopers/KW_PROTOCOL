/**
 *
 *	\file		kw_proto_vars_kip6.h
 *	\brief	Описание интерфейса модуля протокола  
 *
 *
 */

#ifndef __KW_PROTO_VARS_KIP6_H
#define __KW_PROTO_VARS_KIP6_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include "kw_proto_vars.h"


extern kw_proto_vars_interface_t vars_kip6_interface;


void kw_vars_kip6_init( void );


#ifdef __cplusplus
}
#endif

#endif //__KW_PROTO_VARS_KIP6_H


