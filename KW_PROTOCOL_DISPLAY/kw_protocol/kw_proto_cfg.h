/**
 *
 *	\file		kw_proto_cfg.h
 *	\brief	Модуль для конфигурирования протокола для работы по CAN шине
 *
 *
 */

#ifndef __KW_PROTO_CFG_H
#define __KW_PROTO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_can.h"

//------------------------------ Описание конфигурации  ------------------------------
///< Номер канала CAN для работы протокола
#define   KW_CAN_PROTO_CHANNEL        KW_CAN_CANNEL_1   

///< Скорость CAN для работы протокола
#define   KW_CAN_PROTO_BAUD           KW_CAN_BAUD_1M   

///< Число фаз входного напряжения - 1 или 3    
#define   KW_PROTO_PHASE_NUMBERS      1

///< Число входных линий - 1, 2 или 3    
#define   KW_PROTO_IN_LINE_NUMBERS    1

///< Число выходных линий - 1, 2 или 3    
#define   KW_PROTO_OUT_LINE_NUMBERS   1

///< Число линий байпасс - 1, 2 или 3    
#define   KW_PROTO_BYPASS_LINE_NUMBERS   1


// выбор роли модуля в протоколе
#define   KW_POWER_MODULE     1 
#define   KW_DISPLAY_MODULE   2
#define   KW_KIP6_MODULE      3 

///< Какой роль модуль реализуется  KW_POWER_MODULE, KW_DISPLAY_MODULE, KW_KIP6_MODULE (соответственно силовой модуль, дисплейный модуль, модуль КИП6)
//#define   KW_PROTO_MODULE          KW_POWER_MODULE 
#define   KW_PROTO_MODULE          KW_DISPLAY_MODULE
//#define   KW_PROTO_MODULE          KW_KIP6_MODULE 


#ifdef __cplusplus
}
#endif

#endif
