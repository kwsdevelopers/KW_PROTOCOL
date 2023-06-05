/**
 *
 *	\file		kw_proto_module_display.h
 *	\brief	Описание интерфейса модуля протокола дисплея  
 *
 *
 */

#ifndef __KW_PROTO_MODULE_DISPLAY_H
#define __KW_PROTO_MODULE_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kw_proto_cfg.h"

#if( KW_PROTO_MODULE == KW_DISPLAY_MODULE )

  #include "kw_proto_module.h"


// ---------------- константы ------------------------------
#define    OWN_ADDR     DISPLAY_MODULE_ADDR


// ---------------- интерфейс модуля  ----------------------


extern kw_proto_module_interface_t mod_display_inerface;


void kw_mod_display_reqest_setpoints( void );





#endif // ( KW_PROTO_MODULE == KW_DISPLAY_MODULE )


#ifdef __cplusplus
}
#endif

#endif //__KW_PROTO_MODULE_DISPLAY_H


