/**
 *
 *	\file		kw_proto_module.h
 *	\brief	Описание интерфейса модуля протокола КИП6  
 *
 *
 */

#ifndef __KW_PROTO_MODULE_KIP6_H
#define __KW_PROTO_MODULE_KIP6_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kw_proto_cfg.h"

#if( KW_PROTO_MODULE == KW_KIP6_MODULE )

#include "kw_proto_module.h"

// ---------------- константы ------------------------------
#define    OWN_ADDR     KIP6_MODULE_ADDR


// ---------------- интерфейс модуля  ----------------------


extern kw_proto_module_interface_t mod_kip6_inerface;

#endif // ( KW_PROTO_MODULE == KW_KIP6_MODULE )


#ifdef __cplusplus
}
#endif

#endif //__KW_PROTO_MODULE_KIP6_H


