/**
 *
 *	\file		main.c
 * 	\brief		��������� ���������� ������ �� ��������� CAN ��� ������ �������.
 *            � ������ ������ � ������� ����� �������������� �������� �� ���� CAN ���������.
 *            ����� ��������� �������� � ����� README.MD
 *
 * 	\author		UsharovSV
 *	\version  	1.0
 *	\date     	24-04-2023
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
  
// ����������� �������� - ������ �������� �������� ������  
//  kw_proto_special_operation( SPC_OP_SEND_REQUEST, REQUEST_POWER_MODULE_SETPOINTS );  

// ����������� �������� - ������ IP ������ � ����� ���� �� ���6  
//  kw_proto_special_operation( SPC_OP_SEND_REQUEST, REQUEST_KIP6_MODULE_IP_MASK );  

  
// ����������� �������� - ������ ������� �������� ������  - ��������� ����������
//  kw_proto_special_operation( SPC_OP_WRITE_SETPOINT, SETPOINT_POWER_MODULE_OUT_VOLTAGE );  
  
// ����������� �������� - ��������� ����/�������
//  kw_proto_special_operation( SPC_OP_SET_DATE_TIME, 0 );  
  
	while(1)
	{    
		
		// ��������� � ��������� ��������� can
		if( kw_proto_listen() )
		{
			continue;
		}

    //��������� ���� ���������� ��������
    if( event_tick )
    {
      kw_proto_tick_operate();      
      
      // ����� �����
      event_tick = 0;      
    }
   
//    for ( i = 0; i < 50000; i++ ); // �������� ������ �������� ����������           

  }


}
