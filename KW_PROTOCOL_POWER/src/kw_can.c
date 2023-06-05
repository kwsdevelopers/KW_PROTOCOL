/**
 *
 *	\file		kw_can.c
 *	\brief	Модуль для работы с интерфейсом CAN - реализация
 *
 * 			 Модуль частично реализован с помощью библиотеки BSP.
 *
 */

#include <string.h>
#include "kw_can.h"
#include "at32f403a_407.h"



#define		CAN_FRAME_COUNT	 32 	// глубина буфера сообщений степень 2 

// ----------- Типы данных -------------------------------
///< Тип данных очередь
typedef struct
{
	kw_can_msg_t	frame_buffer[ CAN_FRAME_COUNT ];	// кольцевой буфер кадров
	uint32_t			rd_idx;								// индекс на чтение
	uint32_t			wr_idx;								// индекс на запись
}
kw_can_queue_t;


///< Тип данных модуль 
typedef struct
{
	kw_can_queue_t rx_queue;  ///< очередь приема
	kw_can_queue_t tx_queue;  ///< очередь приема
} 
kw_can_module_t;

// ------------------- Локальные переменные ------------------

///< массив модулей - размер = числу модулей CAN на кристалле
//static kw_can_module_t kw_can_module[ KW_CAN_CANNEL_NUMBERS ];
kw_can_module_t kw_can_module[ KW_CAN_CANNEL_NUMBERS ];

//------------- Локальные функции -----------------

/**
  * @brief  Положить сообщение в очередь приема.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @param  p_msg: указатель на структуру, откуда берется сообщение.
  * @retval 0 - не удалось сохранить сообщение, !0 - сообщение сохранено.
  */
static uint32_t kw_can_put_rx_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg )
{
	kw_can_queue_t *p_queue;
	
	if( ( uint8_t )chan >=KW_CAN_CANNEL_NUMBERS )
		return FALSE;

  // берем указатель на очероедь передачи нужного модуля CAN
	p_queue = &kw_can_module[ ( uint8_t )chan ].rx_queue;
	
	// копируем кадр в очередь отправки
	memcpy( &( p_queue->frame_buffer[ p_queue->wr_idx ] ), 
			p_msg, 
			sizeof( kw_can_msg_t ) );
	
	// смещаем индекс		
	p_queue->wr_idx++;
	p_queue->wr_idx &= ( CAN_FRAME_COUNT - 1);
	
	return TRUE;
}

/**
  * @brief  Прием сообщения из переферии CAN.
  * @param  can_x: Номер канала CAN.
  *         Может иметь следующие значения:
  *         CAN1,CAN2.
  * @param  fifo_number: Номер ФИФО в канале.
  *         Может иметь следующие значения:
  *         - CAN_RX_FIFO0
  *         - CAN_RX_FIFO1
  * @param  p_msg: указатель на структуру, куда сохраняется сообщение.
  * @retval TRUE - принято сообщение с 29-битным ID, FALSE - НЕ принято сообщение с 29-битным ID.
  */
static uint32_t kw_can_msg_rcv( can_type* can_x, can_rx_fifo_num_type fifo_number, kw_can_msg_t *p_msg )
{
	
  // получаем тип идентификатора
	p_msg->id_type = (kw_can_id_t)can_x->fifo_mailbox[fifo_number].rfi_bit.rfidi;
	
  switch( p_msg->id_type )
  {
    case KW_CAN_ID_STANDARD:
      p_msg->id = can_x->fifo_mailbox[fifo_number].rfi_bit.rfsid;
      break;
    case KW_CAN_ID_EXTENDED:
      p_msg->id = 0x1FFFFFFF & (can_x->fifo_mailbox[fifo_number].rfi >> 3);
      break;
    default:
			// иначе выходим
			can_receive_fifo_release(can_x, fifo_number);				
      return FALSE;
  }
  // тип кадра
  p_msg->frame_type = (kw_can_trans_frame_t)can_x->fifo_mailbox[fifo_number].rfi_bit.rffri;
  
  // длина данных 
  p_msg->dlc = can_x->fifo_mailbox[fifo_number].rfc_bit.rfdtl;

  // поле данных 
  p_msg->data[0] = can_x->fifo_mailbox[fifo_number].rfdtl_bit.rfdt0;
  p_msg->data[1] = can_x->fifo_mailbox[fifo_number].rfdtl_bit.rfdt1;
  p_msg->data[2] = can_x->fifo_mailbox[fifo_number].rfdtl_bit.rfdt2;
  p_msg->data[3] = can_x->fifo_mailbox[fifo_number].rfdtl_bit.rfdt3;
  p_msg->data[4] = can_x->fifo_mailbox[fifo_number].rfdth_bit.rfdt4;
  p_msg->data[5] = can_x->fifo_mailbox[fifo_number].rfdth_bit.rfdt5;
  p_msg->data[6] = can_x->fifo_mailbox[fifo_number].rfdth_bit.rfdt6;
  p_msg->data[7] = can_x->fifo_mailbox[fifo_number].rfdth_bit.rfdt7;

  // release the fifo
  can_receive_fifo_release(can_x, fifo_number);
	
	return TRUE;
}


/**
  * @brief  Передать сообщение из очереди передачиё.
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @param  p_msg: указатель на структуру, куда сохраняется сообщение.
  * @retval CAN_TX_STATUS_NO_EMPTY - не получилось передать ообщение, остальные - сообщение передано.
  */
static uint8_t kw_can_msg_tx( kw_can_channel_t chan, kw_can_msg_t* p_msg)
{
  // указатенль на регистры перефирии
  can_type *p_can = ( chan == KW_CAN_CANNEL_1 )? CAN1 : CAN2;
  uint8_t transmit_mailbox = CAN_TX_STATUS_NO_EMPTY;

  // выбираем пустой почтовый ящик,  
  if(p_can->tsts_bit.tm0ef)
  {
    transmit_mailbox = CAN_TX_MAILBOX0;
  }
  else if(p_can->tsts_bit.tm1ef)
  {
    transmit_mailbox = CAN_TX_MAILBOX1;
  }
  else if(p_can->tsts_bit.tm2ef)
  {
    transmit_mailbox = CAN_TX_MAILBOX2;
  }
  else
  {
    transmit_mailbox = CAN_TX_STATUS_NO_EMPTY;
  }

  if(transmit_mailbox != CAN_TX_STATUS_NO_EMPTY)
  {// нашли пустой почтовый ящик 
    // устанавливаем id в зависмости от его ширины
    p_can->tx_mailbox[transmit_mailbox].tmi &= 0x00000001;
    p_can->tx_mailbox[transmit_mailbox].tmi_bit.tmidsel = p_msg->id_type;
    switch(p_msg->id_type)
    {
      case KW_CAN_ID_STANDARD:
        p_can->tx_mailbox[transmit_mailbox].tmi_bit.tmsid = p_msg->id;
        break;
      case KW_CAN_ID_EXTENDED:
        p_can->tx_mailbox[transmit_mailbox].tmi |= (p_msg->id << 3);
        break;
      default:
        break;
    }
	// тип кадра
    p_can->tx_mailbox[transmit_mailbox].tmi_bit.tmfrsel = p_msg->frame_type;
    // длина кадра
    p_can->tx_mailbox[transmit_mailbox].tmc_bit.tmdtbl = (p_msg->dlc & ((uint8_t)0x0F));

    // данные кадра
    p_can->tx_mailbox[transmit_mailbox].tmdtl = (((uint32_t)p_msg->data[3] << 24) |
                                                ((uint32_t)p_msg->data[2] << 16) |
                                                ((uint32_t)p_msg->data[1] << 8) |
                                                ((uint32_t)p_msg->data[0]));
    p_can->tx_mailbox[transmit_mailbox].tmdth = (((uint32_t)p_msg->data[7] << 24) |
                                                ((uint32_t)p_msg->data[6] << 16) |
                                                ((uint32_t)p_msg->data[5] << 8) |
                                                ((uint32_t)p_msg->data[4]));

    // запрос на передачу
    p_can->tx_mailbox[transmit_mailbox].tmi_bit.tmsr = TRUE;
  }
  return transmit_mailbox;
}



static uint32_t kw_can_send_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg )
{
	// пытаемся положить сообщение в ящик
	if( CAN_TX_STATUS_NO_EMPTY == kw_can_msg_tx( chan, p_msg ) )
	{	// нет пустых ящиков
		return FALSE;	
	}	
	// положили сообщение в ящик	
	return TRUE;
}

/**
  * @brief  Обслуживание канала CAN (отправка сообщения в шину из очереди передачи).
  * @param  chan: Номер канала CAN.
  *         Может иметь следующие значения:
  *         KW_CAN_CANNEL_1,KW_CAN_CANNEL_2.
  * @retval none
*/
static void kw_can_tx_process( kw_can_channel_t chan )
{
	kw_can_queue_t *p_queue;
	kw_can_msg_t *p_msg;
	
	if( ( uint8_t )chan >=KW_CAN_CANNEL_NUMBERS )
		return;

  // указатель на очередь передачи соответствыющего модуля
	p_queue = &kw_can_module[ ( uint8_t )chan ].tx_queue;
	
	//  в очереди есть данные для передачи 
	while( p_queue->rd_idx != p_queue->wr_idx )
	{	
		p_msg = &( p_queue->frame_buffer[ p_queue->rd_idx ] );
		
		if( kw_can_send_msg( chan, p_msg ) )
		{	// получилось отправить
			// смещаем индекс		
			p_queue->rd_idx++;
			p_queue->rd_idx &= ( CAN_FRAME_COUNT - 1);
		}
    else
    {
      // НЕ получилось отправить- заняты все почтовые ящики
      break;
    }
	}
}


//------------- Глобальные функции -----------------

// Обработчик прерывания по окончанию передачи сообщения CAN1
void USBFS_H_CAN1_TX_IRQHandler( void )
{

  can_transmit_status_type tx_status;
  
  // сбрасываем флаги, чтобы сбросить прерывание передачи
  if(can_flag_get(CAN1,CAN_TM0TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN1, CAN_TX_MAILBOX0);  
    
    can_flag_clear(CAN1, CAN_TM0TCF_FLAG);
    
    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN1->tx_mailbox[ CAN_TX_MAILBOX0 ].tmi_bit.tmsr = TRUE;
      return;
    }
  } 
  else if(can_flag_get(CAN1,CAN_TM1TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN1, CAN_TX_MAILBOX1);  
  
    can_flag_clear(CAN1, CAN_TM1TCF_FLAG);

    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN1->tx_mailbox[ CAN_TX_MAILBOX1 ].tmi_bit.tmsr = TRUE;          
      return;
    }
  } 
  else if(can_flag_get(CAN1,CAN_TM2TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN1, CAN_TX_MAILBOX2);  

    can_flag_clear(CAN1, CAN_TM2TCF_FLAG);
    
    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN1->tx_mailbox[ CAN_TX_MAILBOX2 ].tmi_bit.tmsr = TRUE;          
      return;
    }
  }
  
  // отправляем следующий пакет
	kw_can_tx_process( KW_CAN_CANNEL_1 );

}

// Обработчик прерывания по оприему сообщения CAN1 ФИФО 0
void USBFS_L_CAN1_RX0_IRQHandler (void)
{
	kw_can_msg_t kw_can_msg;
	
	// Есть сообщение в ящике
	if(can_flag_get(CAN1,CAN_RF0MN_FLAG) != RESET)
	{	// вытащил сообщение из ящика
		if( kw_can_msg_rcv( CAN1, CAN_RX_FIFO0, &kw_can_msg ) )
		{
			// положили в приемный буфер
			kw_can_put_rx_msg( KW_CAN_CANNEL_1, &kw_can_msg );
		}
	}
}

// Обработчик прерывания по оприему сообщения CAN1 ФИФО 1
void CAN1_RX1_IRQHandler( void )
{
	
}

// Обработчик прерывания ошибок CAN1 
void CAN1_SE_IRQHandler( void )
{
  __IO uint32_t err_index = 0;
  
  if(can_flag_get(CAN1,CAN_EOIF_FLAG) != RESET)
  {
    can_flag_clear(CAN1, CAN_EOIF_FLAG);
  }  
  
  if(can_flag_get(CAN1,CAN_ETR_FLAG) != RESET)
  {
    err_index = CAN1->ests & 0x70;
    can_flag_clear(CAN1, CAN_ETR_FLAG);
  }	
}

// Обработчик прерывания по окончанию передачи сообщения CAN2
void CAN2_TX_IRQHandler( void )
{
  can_transmit_status_type tx_status;
  
  if(can_flag_get(CAN2,CAN_TM0TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN2, CAN_TX_MAILBOX0);  
    
    can_flag_clear(CAN2, CAN_TM0TCF_FLAG);
    
    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN2->tx_mailbox[ CAN_TX_MAILBOX0 ].tmi_bit.tmsr = TRUE;
      return;
    }
  } 
  else if(can_flag_get(CAN2,CAN_TM1TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN2, CAN_TX_MAILBOX1);  
  
    can_flag_clear(CAN2, CAN_TM1TCF_FLAG);

    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN2->tx_mailbox[ CAN_TX_MAILBOX1 ].tmi_bit.tmsr = TRUE;          
      return;
    }
  } 
  else if(can_flag_get(CAN2,CAN_TM2TCF_FLAG) != RESET)
  {
    tx_status = can_transmit_status_get(CAN2, CAN_TX_MAILBOX2);  

    can_flag_clear(CAN2, CAN_TM2TCF_FLAG);
    
    if( tx_status == CAN_TX_STATUS_FAILED ) // передача провалена из-за проигрыш арбитража
    {
      // повторная передача - данные кадра уже лежат в регистре
      CAN2->tx_mailbox[ CAN_TX_MAILBOX2 ].tmi_bit.tmsr = TRUE;          
      return;
    }
  }   
  // отправляем следующий пакет
	kw_can_tx_process( KW_CAN_CANNEL_2 );
}

// Обработчик прерывания по оприему сообщения CAN2 ФИФО 0
void CAN2_RX0_IRQHandler( void )
{
	kw_can_msg_t kw_can_msg;
	
	// Есть сообщение в ящике
	if(can_flag_get(CAN2,CAN_RF0MN_FLAG) != RESET)
	{	// вытащил сообщение из ящика
		if( kw_can_msg_rcv( CAN2, CAN_RX_FIFO0, &kw_can_msg ) )
		{
			// положили в приемный буфер
			kw_can_put_rx_msg( KW_CAN_CANNEL_2, &kw_can_msg );
		}
	}	
}

// Обработчик прерывания по оприему сообщения CAN2 ФИФО 1
void CAN2_RX1_IRQHandler( void )
{

}

// Обработчик прерывания по окончанию передачи сообщения CAN2
void CAN2_SE_IRQHandler( void )
{
  __IO uint32_t err_index = 0;
  
  if(can_flag_get(CAN1,CAN_EOIF_FLAG) != RESET)
  {
    can_flag_clear(CAN1, CAN_EOIF_FLAG);
  }  
  
  if(can_flag_get(CAN2,CAN_ETR_FLAG) != RESET)
  {
    err_index = CAN2->ests & 0x70;
    can_flag_clear(CAN2, CAN_ETR_FLAG);
  }		
}

//------------- Глобальные функции -----------------

void kw_can_gpio_init( kw_can_channel_t chan )
{
	gpio_init_type gpio_init_struct;

	if( chan == KW_CAN_CANNEL_1)
	{ // PD0 PD1
		crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		gpio_pin_remap_config(CAN1_GMUX_0011,TRUE);

		gpio_default_para_init(&gpio_init_struct);
		// can tx pin 
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
		gpio_init_struct.gpio_pins = GPIO_PINS_1;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init(GPIOD, &gpio_init_struct);
		
		// can rx pin 
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_pins = GPIO_PINS_0;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init(GPIOD, &gpio_init_struct);
	}
	else if( chan ==KW_CAN_CANNEL_2)
	{ 
#if 0
    // разведено на целевой плате
		// PB5 PB6
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		gpio_pin_remap_config(CAN2_GMUX_0001,TRUE);

		/* can tx pin */
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
		gpio_init_struct.gpio_pins = GPIO_PINS_6;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init(GPIOB, &gpio_init_struct);
  
		/* can rx pin */
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_pins = GPIO_PINS_5;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init(GPIOB, &gpio_init_struct);
		
		// PB5 PB6
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		gpio_pin_remap_config(CAN2_GMUX_0001,TRUE);
#endif		

#if 1
		// не определено в библиотеке Artery коммутация CAN2 на  PB12 PB13 - мезонинная плата разведена на эти ноги
		#define CAN2_GMUX_0000                   IOMUX_MAKE_VALUE(0x2C, 4, 4, 0x00)  /*!< can2_rx(pb12),  can2_tx(pb13) */

		// PB12 PB13
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
		gpio_pin_remap_config(CAN2_GMUX_0000,TRUE);

		// can tx pin 
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
		gpio_init_struct.gpio_pins = GPIO_PINS_13;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init(GPIOB, &gpio_init_struct);
  
		// can rx pin 
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_pins = GPIO_PINS_12;
		gpio_init_struct.gpio_pull = GPIO_PULL_UP;
		gpio_init(GPIOB, &gpio_init_struct);
#endif		
	}
}

void kw_can_module_init( kw_can_channel_t chan, kw_can_baudrate_t baud)
{
	// таблица настроек стандартных скоростей
	const can_baudrate_type standard_baud[ KW_CAN_BAUD_NUMBERS ] =
	{
		{ 15,	CAN_RSAW_2TQ,	CAN_BTS1_5TQ,	CAN_BTS2_2TQ }, // KW_CAN_BAUD_1M  
		{ 15,	CAN_RSAW_2TQ,	CAN_BTS1_7TQ,	CAN_BTS2_2TQ }, // KW_CAN_BAUD_800K 
		{ 30,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ }, // KW_CAN_BAUD_500K 
		{ 60,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ }, // KW_CAN_BAUD_250K 
		{ 120,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ }, // KW_CAN_BAUD_125K 
		{ 300,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ }, // KW_CAN_BAUD_50K 
		{ 750,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ }, // KW_CAN_BAUD_20K 
		{ 1500,	CAN_RSAW_1TQ,	CAN_BTS1_6TQ,	CAN_BTS2_1TQ } // KW_CAN_BAUD_10K	
	};
	
	can_base_type can_base_struct;
	can_baudrate_type can_baudrate_struct;
	can_filter_init_type can_filter_init_struct;
	can_type *p_can;

	// проверка на номер канала и скорость
	if( ( uint8_t )chan >=KW_CAN_CANNEL_NUMBERS ||
		( uint8_t )baud >= KW_CAN_BAUD_NUMBERS )
		return;
	
	// сброс переменных канала
	memset( &kw_can_module[ ( uint8_t )chan ], 0, sizeof( kw_can_module_t ) );
	
	// включение тактирование канала
	if( chan ==KW_CAN_CANNEL_1 )
	{
		crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
		p_can = CAN1;
	}
	else
	{
		crm_periph_clock_enable(CRM_CAN2_PERIPH_CLOCK, TRUE);
		p_can = CAN2;
	}

	// базовая конфигурация
	can_default_para_init(&can_base_struct);
	can_base_struct.mode_selection = CAN_MODE_COMMUNICATE;		// режим связи (RX и TX) - остальные режимы тестовые
	can_base_struct.ttc_enable = FALSE;							// запуск по времени
	can_base_struct.aebo_enable = TRUE;							// Разрешение автоматического отключения выходной шины 
	can_base_struct.aed_enable = TRUE; 							// Автоматический выход из спящего режима
	can_base_struct.prsf_enable = TRUE;						// Запрет повторной передачи при неудачной отправке сообщения
  can_base_struct.mdrsel_selection = CAN_DISCARDING_FIRST_RECEIVED;	// правило отбрасывания сообщений при переполнении
	can_base_struct.mmssr_selection = CAN_SENDING_BY_REQUEST; // правило последовательности отправки нескольких сообщений
	can_base_init( p_can, &can_base_struct );
		
	// Скорость	
	can_baudrate_struct = *( can_baudrate_type * )&standard_baud[ ( uint8_t )baud ];
	can_baudrate_set( p_can, &can_baudrate_struct );

  // фильтр входных пакетов - без фильтра 
	can_filter_init_struct.filter_activate_enable = TRUE;			        // разрешение фильтра
	can_filter_init_struct.filter_mode = CAN_FILTER_MODE_ID_MASK;     // режим фильтра
	can_filter_init_struct.filter_fifo = CAN_FILTER_FIFO0;            // выбираем ФИФО
	can_filter_init_struct.filter_number = 0;                         // номер фильтра
	can_filter_init_struct.filter_bit = CAN_FILTER_32BIT;             // ширина фильтра
	can_filter_init_struct.filter_id_high = 0;                        //
	can_filter_init_struct.filter_id_low = 0;                         // настройки ID - чтобы принимались все пакеты
	can_filter_init_struct.filter_mask_high = 0;                      //
	can_filter_init_struct.filter_mask_low = 0;                       // 
	can_filter_init(p_can, &can_filter_init_struct);

	// прерывания - пока с одним почтовым ящиком
	if( chan ==KW_CAN_CANNEL_1 )
	{
		/* can interrupt config */
		nvic_irq_enable(CAN1_SE_IRQn, 0x00, 0x00);          // прерывание ошибки
		nvic_irq_enable(USBFS_L_CAN1_RX0_IRQn, 0x00, 0x00); // прерывание RX
		nvic_irq_enable(USBFS_H_CAN1_TX_IRQn, 0x00, 0x00);  // прерывание TX
  
		/* error interrupt enable */
		can_interrupt_enable(CAN1, CAN_ETRIEN_INT, TRUE); // разрешение прерывания записи типа ошибки
		can_interrupt_enable(CAN1, CAN_EOIEN_INT, TRUE);  // прерывание возникновения ошибки
		can_interrupt_enable(CAN1, CAN_RF0MIEN_INT, TRUE);// прерывание приема сообщения ФИФО 0
		can_interrupt_enable(CAN1, CAN_TCIEN_INT, TRUE);  // прерывание завершения передачи сообщения
	}
	else
	{
		/* can interrupt config */
		nvic_irq_enable(CAN2_SE_IRQn, 0x00, 0x00);        // прерывание ошибки
		nvic_irq_enable(CAN2_RX0_IRQn, 0x00, 0x00);       // прерывание RX
		nvic_irq_enable(CAN2_TX_IRQn, 0x00, 0x00);        // прерывание TX

		/* error interrupt enable */
		can_interrupt_enable(CAN2, CAN_ETRIEN_INT, TRUE); // разрешение прерывания записи типа ошибки
		can_interrupt_enable(CAN2, CAN_EOIEN_INT, TRUE);  // прерывание возникновения ошибки
		can_interrupt_enable(CAN2, CAN_RF0MIEN_INT, TRUE);// прерывание приема сообщения ФИФО 0
		can_interrupt_enable(CAN2, CAN_TCIEN_INT, TRUE);  // прерывание завершения передачи сообщения 
	}
}

uint32_t kw_can_put_tx_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg )
{
	kw_can_queue_t *p_queue;
	
	if( ( uint8_t )chan >=KW_CAN_CANNEL_NUMBERS )
		return 0;
	
  // пытаемся передать
  if( kw_can_send_msg( chan, p_msg ) )
  { // получилось передать 
 
    return 1;
  }
  // иначе кладем в буфер
	p_queue = &kw_can_module[ ( uint8_t )chan ].tx_queue;
  
	// копируем кадр в очередь отправки
	memcpy( &( p_queue->frame_buffer[ p_queue->wr_idx ] ), 
			p_msg, 
			sizeof( kw_can_msg_t ) );
	
	// смещаем индекс	
	p_queue->wr_idx++;
	p_queue->wr_idx &= ( CAN_FRAME_COUNT - 1);
  
	return 1;
}

uint32_t kw_can_get_rx_msg( kw_can_channel_t chan, kw_can_msg_t *p_msg )
{
	kw_can_queue_t *p_queue;

	
	if( ( uint8_t )chan >=KW_CAN_CANNEL_NUMBERS )
		return 0;
	
	p_queue = &kw_can_module[ ( uint8_t )chan ].rx_queue;
	
	//  в очереди есть принятые данные 
	if( p_queue->wr_idx != p_queue->rd_idx )
	{
		// копируем кадр из очереди приема
		memcpy( p_msg,
				&( p_queue->frame_buffer[ p_queue->rd_idx ] ), 				 
				sizeof( kw_can_msg_t ) );

		// смещаем индекс		
		p_queue->rd_idx++;
		p_queue->rd_idx &= ( CAN_FRAME_COUNT - 1);

		return 1;	
	}
	
	//  нет данных в очереди	
	return 0;
}
