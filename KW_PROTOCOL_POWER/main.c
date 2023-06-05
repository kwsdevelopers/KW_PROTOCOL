/**
 *
 *	\file		main.c
 * 	\brief		��������� ������������ ������ kw_can
 * 				� ������ DMA.
 *
 *				� ��������� ������������ ����������� ������������� ����� � ��������� CAN.
 *         ����� � ����� ����������� ����� CAN � ������������ �������.
 *         �� �� �������� � ����� ������� �������� ����� ������� USB_CAN_TOOL
 *
 *
 * 	\author		UsharovSV
 *	\version  	1.0
 *	\date     	27-02-2023
 *
 */

#include "at32f403a_407.h"
#include "init.h"
#include "sys_timer.h"
//#include "kw_can.h"

#include "kw_protocol.h"



int main(void)
{ 
//	kw_can_msg_t msg_can;
  volatile int i;
  
	// ���������� ���������� ����������
	__disable_irq();

	// ������������� ������ ������������
	init_CRM_BSP();

	for ( i = 0; i < 5000; i++ ); // �������� ��� ������� ��������� ���������

  // ������������� ���������� �������
  init_sys_timer();
  
	// ���������� ��������� ����������
	__enable_irq();

  kw_proto_init();

	while(1)
	{    
		
		// ��������� � ��������� ��������� can
		if( kw_proto_listen() )
		{
			continue;
		}

    if( event_tick )
    {
      kw_proto_tick_operate();      
      
      // ����� �����
      event_tick = 0;      
    }
   
//    for ( i = 0; i < 50000; i++ ); // �������� ������ �������� ����������           

  }


}
