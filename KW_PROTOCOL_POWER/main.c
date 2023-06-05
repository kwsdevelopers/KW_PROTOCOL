/**
 *
 *	\file		main.c
 * 	\brief		Программа тестирования модуля kw_can
 * 				и модуля DMA.
 *
 *				В программе производится аппаравтная инициализация пинов и переферии CAN.
 *         далее в цикле принимаются кадры CAN и отправляются обратно.
 *         На ПК отправка и прием пакетов делается через утилиту USB_CAN_TOOL
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

	while(1)
	{    
		
		// получение и обработка сообщения can
		if( kw_proto_listen() )
		{
			continue;
		}

    if( event_tick )
    {
      kw_proto_tick_operate();      
      
      // сброс флага
      event_tick = 0;      
    }
   
//    for ( i = 0; i < 50000; i++ ); // Имитация работы целевого приложения           

  }


}
