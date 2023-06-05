/**
 *
 *	\file		kw_proto_module.h
 *	\brief	Описание интерфейса модуля протокола  силовой платы
 *
 *
 */

#ifndef __KW_PROTO_MODULE_POWER_H
#define __KW_PROTO_MODULE_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kw_proto_cfg.h"

#if( KW_PROTO_MODULE == KW_POWER_MODULE )

#include "kw_proto_module.h"

// ---------------- константы ------------------------------
#define    OWN_ADDR     POWER_MODULE_ADDR


// ---------------- интерфейс модуля  ----------------------

extern kw_proto_module_interface_t mod_power_inerface;



#endif // ( KW_PROTO_MODULE == KW_POWER_MODULE )

#ifdef __cplusplus
}
#endif

#endif //__KW_PROTO_MODULE_POWER_H


