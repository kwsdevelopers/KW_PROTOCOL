/**
 *
 *	\file		kw_proto_sys.h
 *	\brief	Модуль для работы c переменными протокола на CAN шине
 *
 *
 */

#ifndef __KW_PROTO_SYS_H
#define __KW_PROTO_SYS_H

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_vars.h"
#include "kw_proto_enums.h"


void kw_proto_sys_init( void );


void kw_proto_sys_ack_unpack( kw_can_msg_t *p_msg );

void kw_proto_sys_ack_pack_and_send( uint8_t DA, uint8_t control_byte, uint8_t group_function_value, uint32_t PGN_of_requested_info );


void kw_proto_sys_request_pack_and_send( uint8_t DA, uint32_t pgn );

void kw_proto_sys_request_unpack( kw_can_msg_t *p_msg );

void kw_proto_sys_tp_cm_pack_and_send( uint8_t DA, uint16_t PGN, uint8_t *p_data, uint16_t sz_data);

void kw_proto_sys_tp_cm_unpack( kw_can_msg_t *p_msg );


void kw_proto_sys_tp_dt_unpack( kw_can_msg_t *p_msg );

void kw_proto_sys_tp_dt_send( uint8_t DA );





#ifdef __cplusplus
}
#endif

#endif // __KW_PROTO_SYS_H


