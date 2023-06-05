/**
 *
 *	\file		init.c
 *	\brief		������� ������������� ������ ������������ (CRM)
 *
 * 				������� ������������� ����������� � ������� ���������� BSP.
 *
 */

#include "at32f403a_407_clock.h"
#include "init.h"


/**
 *
 *	\brief		������� ������������� ������ ������������ (CRM) c �������������� ��������� BSP
 *
 */
void init_CRM_BSP(void)
{
	system_clock_config();
}

