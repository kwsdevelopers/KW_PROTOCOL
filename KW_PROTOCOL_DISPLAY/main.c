/**
 *
 *	\file		main.c
 * 	\brief		Программа реализации обмена по протоколу CAN для модуля дисплея.
 *            В данном модуле в главном цикле обрабатываются принятые из шины CAN сообщения.
 *            Более подробное описание в файле README.MD
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
  
	// Глобальное отключение прерываний
	__disable_irq();

	// Инициализация модуля тактирования
	init_CRM_BSP();

	for ( i = 0; i < 5000; i++ ); // Задержка для полного включения периферии

  // инициализация системного таймера
  init_sys_timer();
  
	// Глобальное включение прерываний
	__enable_irq();

  kw_proto_init();
  
// специальная операция - запрос настроек силового модуля  
//  kw_proto_special_operation( SPC_OP_SEND_REQUEST, REQUEST_POWER_MODULE_SETPOINTS );  

// специальная операция - запрос IP адреса и маски сети от КИП6  
//  kw_proto_special_operation( SPC_OP_SEND_REQUEST, REQUEST_KIP6_MODULE_IP_MASK );  

  
// специальная операция - запись уставки силового модуля  - выходного напряжения
//  kw_proto_special_operation( SPC_OP_WRITE_SETPOINT, SETPOINT_POWER_MODULE_OUT_VOLTAGE );  
  
// специальная операция - установка даты/времени
//  kw_proto_special_operation( SPC_OP_SET_DATE_TIME, 0 );  
  
	while(1)
	{    
		
		// получение и обработка сообщения can
		if( kw_proto_listen() )
		{
			continue;
		}

    //обрабочик тика системного таймероа
    if( event_tick )
    {
      kw_proto_tick_operate();      
      
      // сброс флага
      event_tick = 0;      
    }
   
//    for ( i = 0; i < 50000; i++ ); // Имитация работы целевого приложения           

  }


}
