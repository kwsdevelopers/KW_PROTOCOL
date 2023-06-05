/**
 *
 *	\file		kw_proto_vars.h
 *	\brief	Модуль для работы c переменными протокола на CAN шине
 *
 *
 */

#ifndef __KW_PROTO_PACK_UNPAK_H
#define __KW_PROTO_PACK_UNPAK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>
#include "kw_proto_vars.h"
#include "kw_proto_enums.h"
#include "kw_protocol.h"


///< Тип номер входного канала
typedef enum 
{
  IN_CHANNEL_1                  = 0, 
  IN_CHANNEL_2, 
  IN_CHANNEL_3, 
  IN_CHANNEL_MAX, 
}ENUM_IN_CHANNELS;


///< Тип номер выходного канала
typedef enum 
{
  OUT_CHANNEL_1                  = 0, 
  OUT_CHANNEL_2, 
  OUT_CHANNEL_3, 
  OUT_CHANNEL_MAX, 
}ENUM_OUT_CHANNELS;

///< Тип номер канала байпасс
typedef enum 
{
  BYPASS_CHANNEL_1                  = 0, 
  BYPASS_CHANNEL_2, 
  BYPASS_CHANNEL_3, 
  BYPASS_CHANNEL_MAX, 
}ENUM_BYPASS_CHANNELS;



/**
  * @brief  Упаковать и передать фрейм статуса аварий (PGN 0xFF00).
  * @retval none.
  */
void kw_proto_fault_status_pack_and_send( void );


/**
  * @brief  Распаковать и передать фрейм статуса аварий (PGN 0xFF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_fault_status_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм входных напряжениий(PGN FF01).
  * @param  in_chan: Номер канала входа.
  * @retval none.
  */
void kw_proto_in_voltage_pack_and_send( ENUM_IN_CHANNELS in_chan );

/**
  * @brief  Распаковать фрейм входных напряжениий(PGN FF01).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_in_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм входных токов(PGN FF02).
  * @param  in_chan: Номер канала входа.
  * @retval none.
  */
void kw_proto_in_current_pack_and_send( ENUM_IN_CHANNELS in_chan );
 
/**
  * @brief  Распаковать фрейм входных входных токов(PGN FF02).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_in_current_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм частоты входного напряжения(PGN FF03).
  * @param  in_chan: Номер канала входа.
  * @retval none.
  */
void kw_proto_in_frequency_pack_and_send( ENUM_IN_CHANNELS in_chan );

/**
  * @brief  Распаковать фрейм частоты входного напряжения(PGN FF03).
  * @param  in_chan: Номер канала входа.
  * @retval none.
  */
void kw_proto_in_frequency_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм статуса входных линий(PGN FF0F).
  * @param  in_chan: Номер канала входа.
  * @retval none.
  */
void kw_proto_in_status_pack_and_send( void );

/**
  * @brief  Распаковать фрейм статуса входных линий(PGN FF0F).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_in_status_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм выходных напряжений(PGN 0xFF11).
  * @param  out_chan: Номер канала выхода.
  * @retval none.
  */
void kw_proto_out_voltage_pack_and_send( ENUM_OUT_CHANNELS out_chan );

/**
  * @brief  Распаковать фрейм выходных напряжений(PGN 0xFF11).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_out_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм выходных токов(PGN 0xFF12).
  * @param  out_chan: Номер канала выхода.
  * @retval none.
  */
void kw_proto_out_current_pack_and_send( ENUM_OUT_CHANNELS out_chan );

/**
  * @brief  Распаковать и передать фрейм выходных токов(PGN 0xFF12).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_out_current_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм частоты выходного напряжения(PGN 0xFF1E).
  * @retval none.
  */
void kw_proto_out_frequency_pack_and_send( void );

/**
  * @brief  Распаковать фрейм частоты выходного напряжения(PGN 0xFF1E).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_out_frequency_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм фазового сдвига выходного напряжения(PGN 0xFF1F).
  * @retval none.
  */
void kw_proto_out_phase_pack_and_send( void );

/**
  * @brief  Распаковать и передать фрейм фазового сдвига выходного напряжения(PGN 0xFF1F).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_out_phase_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм байпасс напряжениий(PGN FF21).
  * @param  bypass_chan: Номер канала байпасс.
  * @retval none.
  */
void kw_proto_bypass_voltage_pack_and_send( ENUM_BYPASS_CHANNELS bypass_chan );

/**
  * @brief  Распаковать фрейм байпасс напряжениий(PGN FF21).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_bypass_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм байпасс токов(PGN FF22).
  * @param  bypass_chan: Номер канала байпасс.
  * @retval none.
  */
void kw_proto_bypass_current_pack_and_send( ENUM_BYPASS_CHANNELS bypass_chan );


/**
  * @brief  Распаковать фрейм байпасс токов(PGN FF22).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_bypass_current_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм байпасс частот(PGN FF2E).
  * @param  bypass_chan: Номер канала байпасс.
  * @retval none.
  */
void kw_proto_bypass_frequency_pack_and_send( void );

/**
  * @brief  Распаковать фрейм байпасс частот(PGN FF2E).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_bypass_frequency_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм байпасс фазового сдвига(PGN FF2F).
  * @param  bypass_chan: Номер канала байпасс.
  * @retval none.
  */
void kw_proto_bypass_phase_pack_and_send( void );

/**
  * @brief  Распаковать фрейм байпасс фазового сдвига(PGN FF2F).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_bypass_phase_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм напряжений промежуточной шины(PGN FF31).
  * @retval none.
  */
void kw_proto_prop_middle_voltage_pack_and_send( void );

/**
  * @brief  Распаковать фрейм напряжений промежуточной шины(PGN FF31).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_middle_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм напряжений и токов АКБ и зарядного устройства(PGN FF33).
  * @retval none.
  */
void kw_proto_prop_battery_voltage_pack_and_send( void );

/**
  * @brief  Распаковать фрейм напряжений и токов АКБ и зарядного устройства(PGN FF33).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_battery_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм статусов АКБ(PGN FF34).
  * @retval none.
  */
void kw_proto_prop_battery_status_pack_and_send( void );

/**
  * @brief  Упаковать и передать фрейм статусов АКБ(PGN FF34).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_battery_status_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм температур модулей(PGN FF35).
  * @retval none.
  */
void kw_proto_prop_modules_temperature_status_pack_and_send( void );

/**
  * @brief  Распаковать фрейм температур модулей(PGN FF35).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_modules_temperature_status_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм выходных токов инвертора(PGN FF32).
  * @retval none.
  */
void kw_proto_prop_inverter_current_pack_and_send( void );

/**
  * @brief  Упаковать и передать фрейм выходных токов инвертора(PGN FF32).
  * @retval none.
  */
void kw_proto_prop_inverter_current_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм скоростей вентиляторов(PGN FF36).
  * @retval none.
  */
void kw_proto_prop_fun_speed_pack_and_send( void );

/**
  * @brief  Распаковать фрейм скоростей вентиляторов(PGN FF36).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_fun_speed_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фреймы уставок(PGN FF40).
  * @retval none.
  */
void kw_proto_prop_setpoints_pack_and_send( void );

/**
  * @brief  Распаковать фреймы уставок(PGN FF40).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_prop_setpoints_unpack( uint8_t *p_setpoints );

/**
  * @brief  Упаковать и передать фреймы IDcard(PGN FF60).
  * @retval none.
  */
void kw_proto_prop_id_card_pack_and_send( void );

/**
  * @brief  Распаковать фрейм записи уставки(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
int32_t kw_proto_setpoint_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм записи уставки(PGN EF00).
  * @param  setpoint_name: наименование уставки.
  * @retval none.
  */
void kw_proto_setpoint_pack_and_send( ENUM_SETPOINT_NAME setpoint_name );

/**
  * @brief  Упаковать и передать фрейм записи IP адреса(PGN EF00).
  * @param  setpoint_name: наименование уставки.
  * @retval none.
  */
void kw_proto_kip6_wr_ip_addr_pack_and_send( void );

/**
  * @brief  Распаковать фрейм записи IP адреса((PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_ip_addr_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм маски сети(PGN EF00).
  * @param  setpoint_name: наименование уставки.
  * @retval none.
  */
void kw_proto_kip6_wr_net_mask_pack_and_send( void );

/**
  * @brief  Распаковать фрейм маски сети(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_net_mask_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм записи IP адреса шлюза сети(PGN EF00).
  * @param  setpoint_name: наименование уставки.
  * @retval none.
  */
void kw_proto_kip6_wr_gate_pack_and_send( void );

/**
  * @brief  Распаковать фрейм записи IP адреса шлюза сети(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_gate_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм записи типа IP адресации(PGN EF00).
  * @param  setpoint_name: наименование уставки.
  * @retval none.
  */
void kw_proto_kip6_wr_ip_adressing_type_pack_and_send( void );

/**
  * @brief  Распаковать фрейм записи типа IP адресации(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_ip_adressing_type_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм записи настроек ModBus(PGN EF00).
  * @retval none.
  */
void kw_proto_kip6_wr_mb_settings_pack_and_send( void );


/**
  * @brief  Распаковать фрейм записи настроек ModBus(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_mb_settings_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм записи настроек сухих контактов(PGN EF00).
  * @retval none.
  */
void kw_proto_kip6_wr_dry_settings_pack_and_send( void );

/**
  * @brief  Распаковать фрейм записи настроек сухих контактов(PGN EF00).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval none.
  */
void kw_proto_kip6_wr_dry_settings_unpack(  kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм IP адреса и маски сети(PGN FF70).
  * @retval none.
  */
void kw_proto_kip6_prop_rd_ip_mask_pack_and_send( void );

/**
  * @brief  Распаковать фрейм IP адреса и маски сети(PGN FF70).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval 0 - ОК, != 0 - ошибки.
  */
void kw_proto_kip6_prop_rd_ip_mask_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм IP адреса шлюза и типа адресации(PGN FF71).
  * @retval none.
  */
void kw_proto_kip6_prop_rd_gate_type_pack_and_send( void );

/**
  * @brief  Распаковать фрейм IP адреса шлюза и типа адресации(PGN FF71).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval 0 - ОК, != 0 - ошибки.
  */
void kw_proto_kip6_prop_rd_gate_type_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм настроек Modbus(PGN FF72).
  * @retval none.
  */
void kw_proto_kip6_prop_rd_mb_settings_pack_and_send( void );


/**
  * @brief  Распаковать фрейм настроек Modbus(PGN FF72).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval 0 - ОК, != 0 - ошибки.
  */
void kw_proto_kip6_prop_rd_mb_settings_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм настроек сухих контактов(PGN FF73).
  * @retval none.
  */
void kw_proto_kip6_prop_rd_dry_conacts_settings_pack_and_send( void );

/**
  * @brief  Распаковать фрейм настроек сухих контактов(PGN FF73).
  * @param  p_msg: Указатель на сообщение CAN.
  * @retval 0 - ОК, != 0 - ошибки.
  */
void kw_proto_kip6_prop_rd_dry_conacts_settings_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Упаковать и передать фрейм установки даты/времени(PGN EF00).
  * @retval none.
  */
void kw_proto_kip6_set_date_time_pack_and_send( void );

int32_t kw_proto_kip6_set_date_time_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Распаковать фрейм фрейм пароля(PGN EF00).
  * @retval 0 - ОК, != ошибки.
  */
int32_t kw_proto_password_unpack( kw_can_msg_t *p_msg );


/**
  * @brief  Распаковать фрейм записи ID CARD(PGN EF00).
  * @retval 0 - ОК, != ошибки.
 */
int32_t kw_proto_write_id_card_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фреймы строки прохождения теста(PGN FF41).
  * @retval 0 - ОК, != ошибки.
  */
void kw_proto_prop_test_result_str_pack_and_send( void );

/**
  * @brief  Упаковать и передать фрейм напряжения инвертора(PGN FF38).
  * @retval none.
  */
void kw_proto_inverter_voltage_pack_and_send( void );

void kw_proto_inverter_voltage_unpack( kw_can_msg_t *p_msg );

/**
  * @brief  Упаковать и передать фрейм текущей даты времени(PGN FEE6).
  * @retval none.  
  */
void kw_proto_date_time_pack_and_send( void );

/**
  * @brief  Распаковать и передать фрейм текущей даты времени(PGN FEE6).
  * @retval none.  
  */
void kw_proto_date_time_unpack( kw_can_msg_t *p_msg  );




void kw_proto_switch_to_mode_pack_and_send( UPS_MODE_ENUM mode );


#ifdef __cplusplus
}
#endif

#endif // __KW_PROTO_PACK_UNPAK_H



