/**
 *
 *	\file		kw_can.c
 *	\brief	Модуль для работы с интерфейсом CAN - интерфейсы
 *
 *
 */

#ifndef __KW_CAN_H
#define __KW_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//------------------------------ Описание типов ------------------------------
///< Номер канала CAN
typedef enum
{
 KW_CAN_CANNEL_1 = 0, 
 KW_CAN_CANNEL_2,
 KW_CAN_CANNEL_NUMBERS  
}
kw_can_channel_t;

///< Скорости CAN
typedef enum
{
  KW_CAN_BAUD_1M = 0, 
  KW_CAN_BAUD_800K, 
  KW_CAN_BAUD_500K, 
  KW_CAN_BAUD_250K, 
  KW_CAN_BAUD_125K, 
  KW_CAN_BAUD_50K, 
  KW_CAN_BAUD_20K, 
  KW_CAN_BAUD_10K,
  KW_CAN_BAUD_NUMBERS  
}
kw_can_baudrate_t;

///< Тип идентификатора CAN
typedef enum
{
  KW_CAN_ID_STANDARD   = 0x00, // Стандартный - 11 бит ID 
  KW_CAN_ID_EXTENDED   = 0x01  // Расширенный - 29 бит ID
}
kw_can_id_t;

///< Тип сообщения CAN
typedef enum
{
  KW_CAN_TFT_DATA     = 0x00,   // кадр данных 
  KW_CAN_TFT_REMOTE   = 0x01    // кадр удаленного запроса 
} 
kw_can_trans_frame_t;


// структура кадра
typedef struct
{
  uint32_t 				      id;	        // 29-и битный расширенный ID  ( 0 .. 0x1FFFFFFF ) или 11-и битный стандартный ID  (0 .. 0x7FF ) 
  kw_can_id_t 		      id_type;		// определение типа кадра 11/29 бит.
  kw_can_trans_frame_t 	frame_type;	// определение типа кадра данные/удаленный запрос.
  uint8_t 				      dlc;			  // длина данных ( 0 .. 8 )
  uint8_t 				      data[8];		// данные (0 .. 0xFF). 
} 
kw_can_msg_t;

/**
  * @brief  Инициализация пинов для канала CAN.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @retval none.
  */  
void kw_can_gpio_init( kw_can_channel_t chan );

/**
  * @brief  Инициализация канала CAN.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @retval none.
  */  
void kw_can_module_init( kw_can_channel_t chan, kw_can_baudrate_t baud);

/**
  * @brief  Положить сообщение в очередь передачи.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @param  p_msg: указатель на структуру, откуда берется сообщение.
  * @retval 0 - не удалось сохранить сообщение, !0 - сообщение сохранено.
  */
uint32_t kw_can_put_tx_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg );


/**
  * @brief  Получить сообщение из очереди приема.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @param  p_msg: указатель на структуру, куда сохраняется сообщение.
  * @retval 0 - не удалось получить сообщение, !0 - сообщение получено.
  */
uint32_t kw_can_get_rx_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg );


// Пример использования
/*
// ------ main.c -------------------------

int main(void)
{ 
	kw_can_msg_t msg_can;
	//...

	// инициализация
	kw_can_gpio_init(KW_CAN_CANNEL_1 );
	kw_can_gpio_init(KW_CAN_CANNEL_2 );

	kw_can_module_init(KW_CAN_CANNEL_1, KW_CAN_BAUD_1M );
	kw_can_module_init(KW_CAN_CANNEL_1, KW_CAN_BAUD_500K );

	while( 1 )
	{
		// ....
		// получение и обработка сообщения can
		if( kw_can_get_rx_msg(KW_CAN_CANNEL_1, &msg_can ) )
		{
			can_bl_develop_1( &msg_can );
			continue;
		}
		
		if( kw_can_get_rx_msg(KW_CAN_CANNEL_2, &msg_can ) )
		{
			can_bl_develop_2( &msg_can );
			continue;
		}
				
	}
}
//-----------------------------------

// ------ can_bl.c -------------------------

void can_bl_develop_1( kw_can_msg_t *p_msg )
{
	kw_can_msg_t msg_can_asw;
	// обработка сообщения
	// ...
	
	// формирование ответного сообщения
	// ...
	
	// ставим ответное сообщение в очередь отправки
	kw_can_put_tx_msg(KW_CAN_CANNEL_1, kw_can_msg_t &msg_can_asw );	
}

void can_bl_develop_2( kw_can_msg_t *p_msg )
{
	kw_can_msg_t msg_can_asw;
	// обработка сообщения
	// ...
	
	// формирование ответного сообщения
	// ...
	
	// ставим ответное сообщение в очередь отправки	
	kw_can_put_tx_msg(KW_CAN_CANNEL_2, kw_can_msg_t &msg_can_asw );
		
}
//-----------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif
