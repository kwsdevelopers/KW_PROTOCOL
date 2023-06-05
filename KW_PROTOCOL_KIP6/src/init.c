/**
 *
 *	\file		init.c
 *	\brief		Функции инициализации модуля тактирования (CRM)
 *
 * 				Функции инициализации реализованы с помощью библиотеки BSP.
 *
 */

#include "at32f403a_407_clock.h"
#include "init.h"


/**
 *
 *	\brief		Функция инициализации модуля тактирования (CRM) c использованием библиотек BSP
 *
 */
void init_CRM_BSP(void)
{
	system_clock_config();
}

