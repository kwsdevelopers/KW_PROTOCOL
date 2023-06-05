/**
 *
 *	\file		sys_timer.h.h
 *	\brief	Модуль системного таймера  
 *
 *
 */

#ifndef __SYS_TIMER_H
#define __SYS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


// счетчик тиков 
extern uint32_t sys_tick_count;  

// событие - прпоизошел тик системного таймера 
extern uint32_t event_tick;  


void init_sys_timer( void );


#ifdef __cplusplus
}
#endif

#endif //__SYS_TIMER_H
