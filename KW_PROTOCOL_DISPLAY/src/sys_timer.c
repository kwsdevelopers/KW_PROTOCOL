


/**
 *
 *	\brief		Функция инициализации системного таймера
 *
 */
 
#include "at32f403a_407_clock.h"
#include "init.h" 
#include "sys_timer.h"
 

#define MS_TICK						(system_core_clock / 1000) // Значение для системного таймера

 
// счетчик тиков 
uint32_t sys_tick_count = 0;  

// 
uint32_t event_tick = 0;  
 
 
void init_sys_timer(void)
{
	// Устанавливаем источник тактирования системного таймера
	systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
	
	// Конфигурируем системный таймер на отсчет времени 1 мс
	SysTick_Config(MS_TICK);
  
  // Вкл. прерывания с установкой приоритета SysTick_IRQn: группа 1, подприоритет 3
  nvic_irq_enable(SysTick_IRQn, 1, 1);
}


/**
 *
 *	\brief		Обработчик прерываний системного таймера SysTick
 *
 *
 */
void SysTick_Handler(void)
{
  event_tick = 1;
	sys_tick_count++;
	
}
