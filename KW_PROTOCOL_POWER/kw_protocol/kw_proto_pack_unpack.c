
#include <math.h>
#include <string.h>

#include "kw_protocol.h"
#include "kw_proto_pack_unpack.h"
#include "kw_proto_structs.h"
#include "kw_proto_enums.h"
#include "kw_can.h"
#include "kw_proto_cfg.h"
#include "kw_proto_sys.h"



static void kw_proto_prepare_msg( kw_can_msg_t *p_msg, ENUM_PGN_CODES pgn, uint8_t prio ) 
{
  proto_id_t *p_id;
	
	p_id = ( proto_id_t *)&p_msg->id;  
  
  p_id->id = 0;
  p_id->broadcast_id.PGN = pgn;
  p_id->broadcast_id.priority = prio;  
  p_id->broadcast_id.SA = OWN_ADDR;

  p_msg->id_type = KW_CAN_ID_EXTENDED;
  p_msg->frame_type = KW_CAN_TFT_DATA;
  
  p_msg->dlc = 8;
  
	memset( &p_msg->data[ 0 ], 0xFF, sizeof( p_msg->data ) ); 
}




void kw_proto_fault_status_pack_and_send( void )
{
  kw_can_msg_t msg;
    
  prop_fault_status_t *p_data = ( prop_fault_status_t *)&msg.data[ 0 ];

  // формируем заголовок кадра
  kw_proto_prepare_msg( &msg, PGN_PROP_ALARM_STATUS, 6 ); 

  // заполняем поле данных
	memset( &msg.data[ 0 ], 0, sizeof( msg.data ) );

  // Неверное подключение нейтрали входного напряжения ИБП
  p_data->data_bits.neutral_alarm = p_vars->vars_get_alarm_status( ALARM_NEUTRAL );                                       
    
  // Входное напряжение ИБП в фазе А вне допустимого диапазона  
  p_data->data_bits.in_v_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_VOLTAGE_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  // Входное напряжение ИБП в фазе B вне допустимого диапазона
  p_data->data_bits.in_v_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_VOLTAGE_PHASE_B_OUT_RANGE );

  // Входное напряжение ИБП в фазе C вне допустимого диапазона
  p_data->data_bits.in_v_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_VOLTAGE_PHASE_C_OUT_RANGE ); 
#endif

  // Значение входного тока ИБП в фазе A вне допустимого диапазона
  p_data->data_bits.in_i_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_CURRENT_PHASE_A_OUT_RANGE ); 

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Значение входного тока ИБП в фазе B вне допустимого диапазона
  p_data->data_bits.in_i_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_CURRENT_PHASE_B_OUT_RANGE ); 
  
  // Значение входного тока ИБП в фазе C вне допустимого диапазона
  p_data->data_bits.in_i_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_CURRENT_PHASE_C_OUT_RANGE ); 
#endif

  // Частота входного напряжения ИБП в фазе A вне допустимого диапазона
  p_data->data_bits.in_frequency_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_FREQUENCY_PHASE_A_OUT_RANGE );        

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Частота входного напряжения ИБП в фазе B вне допустимого диапазона
  p_data->data_bits.in_frequency_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_FREQUENCY_PHASE_B_OUT_RANGE );
  
  // Частота входного напряжения ИБП в фазе C вне допустимого диапазона
  p_data->data_bits.in_frequency_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_FREQUENCY_PHASE_C_OUT_RANGE );        
#endif

  // Фазовый сдвиг входного напряжения ИБП (фаза A) вне допустимого диапазона
  p_data->data_bits.in_phase_shift_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Фазовый сдвиг входного напряжения ИБП (фаза B) вне допустимого диапазона
  p_data->data_bits.in_phase_shift_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_B_OUT_RANGE );
  
  // Фазовый сдвиг входного напряжения ИБП (фаза C) вне допустимого диапазона
  p_data->data_bits.in_phase_shift_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_C_OUT_RANGE );
#endif

  // Положительное напряжение на шине постоянного тока не соответствует уставке
  p_data->data_bits.middle_v_positive_alarm = p_vars->vars_get_alarm_status( ALARM_MIDDLE_POSITIVE_VOLTAGE_DOESNT_MATCH_SETPOINT );
  
  // Отрицательное напряжение на шине постоянного тока не соответствует уставке
  p_data->data_bits.middle_v_negative_alarm = p_vars->vars_get_alarm_status( ALARM_MIDDLE_NEGATIVE_VOLTAGE_DOESNT_MATCH_SETPOINT );

  // Выходное напряжение ИБП в фазе А вне допустимого диапазона
  p_data->data_bits.out_v_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )      
  // Выходное напряжение ИБП в фазе B вне допустимого диапазона
  p_data->data_bits.out_v_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_B_OUT_RANGE );
  
  // Выходное напряжение ИБП в фазе C вне допустимого диапазона
  p_data->data_bits.out_v_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_C_OUT_RANGE );      
#endif

  // Превышение выходного тока ИБП в фазе A
  p_data->data_bits.out_i_phase_a_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_A_EXCEEED );      

#if ( KW_PROTO_PHASE_NUMBERS > 1 )        
  // Превышение выходного тока ИБП в фазе B
  p_data->data_bits.out_i_phase_b_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_B_EXCEEED );      
  
  // Превышение выходного тока ИБП в фазе C
  p_data->data_bits.out_i_phase_c_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_C_EXCEEED );
#endif

  // Короткое замыкание на выходе ИБП в фазе A
  p_data->data_bits.out_short_circut_phase_a_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_A );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )          
  // Короткое замыкание на выходе ИБП в фазе B
  p_data->data_bits.out_short_circut_phase_b_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_B );      
  
  // Короткое замыкание на выходе ИБП в фазе C
  p_data->data_bits.out_short_circut_phase_c_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_C );      
#endif

  // Превышение выходной мощности
  p_data->data_bits.out_power_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_POWER_EXCEEED );      

  
  // Превышение пикового значения выходного тока ИБП в фазе A
  p_data->data_bits.out_peak_i_phase_a_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Превышение пикового значения выходного тока ИБП в фазе B
  p_data->data_bits.out_peak_i_phase_b_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED );
  
  // Превышение пикового значения выходного тока ИБП в фазе C
  p_data->data_bits.out_peak_i_phase_c_exceed_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED ); 
#endif

  // Перенапряжение на выходе ИБП в фазе A
  p_data->data_bits.out_over_v_phase_a_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_A );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Перенапряжение на выходе ИБП в фазе B
  p_data->data_bits.out_over_v_phase_b_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_B );
  
  // Перенапряжение на выходе ИБП в фазе C
  p_data->data_bits.out_over_v_phase_c_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_C ); 
#endif
  // Частота выходного напряжения ИБП в фазе A вне допустимого диапазона
  p_data->data_bits.out_frequency_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_FREQUENCY_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Частота выходного напряжения ИБП в фазе B вне допустимого диапазона
  p_data->data_bits.out_frequency_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_FREQUENCY_PHASE_B_OUT_RANGE ); 
  
  // Частота выходного напряжения ИБП в фазе C вне допустимого диапазона
  p_data->data_bits.out_frequency_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_FREQUENCY_PHASE_C_OUT_RANGE ); 
#endif
  // Фазовый сдвиг выходного напряжения ИБП (фаза A) вне допустимого диапазона
  p_data->data_bits.out_v_phase_shift_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Фазовый сдвиг выходного напряжения ИБП (фаза B) вне допустимого диапазона
  p_data->data_bits.out_v_phase_shift_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B_OUT_RANGE );

  // Фазовый сдвиг выходного напряжения ИБП (фаза C) вне допустимого диапазона
  p_data->data_bits.out_v_phase_shift_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C_OUT_RANGE );
#endif

  // Фазовый сдвиг выходного тока ИБП (фаза A) вне допустимого диапазона
  p_data->data_bits.out_i_phase_shift_phase_a_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_A_OUT_RANGE );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Фазовый сдвиг выходного тока ИБП (фаза B) вне допустимого диапазона
  p_data->data_bits.out_i_phase_shift_phase_b_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_B_OUT_RANGE );
  
  // Фазовый сдвиг выходного тока ИБП (фаза C) вне допустимого диапазона
  p_data->data_bits.out_i_phase_shift_phase_c_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_C_OUT_RANGE ); 
#endif

  // Значение тока зарядного устройства не соответствует уставке
  p_data->data_bits.charger_i_value_dosent_match_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_CHARGER_CURRENT_VALUE_DOESNT_MATCH_SETPOINT );  
  
  // Напряжение АКБ вне допустимого диапазона
  p_data->data_bits.battery_v_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_BATTERY_VOLTAGE_OUT_RANGE );  
  
  // Ток разряда АКБ вне допустимого диапазона
  p_data->data_bits.battery_i_out_range_alarm = p_vars->vars_get_alarm_status( ALARM_BATTERY_CURRENT_OUT_RANGE );  
  
  // Отсутствует АКБ
  p_data->data_bits.no_battery_alarm = p_vars->vars_get_alarm_status( ALARM_NO_BATTERY );  
  
  // АКБ разряжена
  p_data->data_bits.battery_discharge_alarm = p_vars->vars_get_alarm_status( ALARM_BATTERY_DISCHARGE );  

  // Температура охладителя ККМ превысила уставку
  p_data->data_bits.temp_kkm_cooler_exceed_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_TEMPERATURE_KKM_COOLER_EXCEED_SETPOINT );  
  
  // Температура охладителя инвертора превысила уставку
  p_data->data_bits.temp_inverter_cooler_exceed_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_TEMPERATURE_INVERTER_COOLER_EXCEED_SETPOINT );
  
  // Температура батареи превысила уставку
  p_data->data_bits.temp_battery_exceed_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_TEMPERATURE_BATTERY_EXCEED_SETPOINT );
  
  // Температура воздуха внутри корпуса ИБП превысила уставку
  p_data->data_bits.temp_inbox_air_exceed_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_TEMPERATURE_INBOX_AIR_EXCEED_SETPOINT ); 

  // Авария вентилятора 1
  p_data->data_bits.fun_1_emergency_alarm = p_vars->vars_get_alarm_status( ALARM_FUN_1_EMERGENCY );  
  
  // Авария вентилятора 2
  p_data->data_bits.fun_2_emergency_alarm = p_vars->vars_get_alarm_status( ALARM_FUN_2_EMERGENCY );  

  // Время работы от АКБ менше заданного при текущей нагрузке
  p_data->data_bits.battery_time_less_setpoint_alarm = p_vars->vars_get_alarm_status( ALARM_BATTERY_TIME_LESS_SETPOINT );  
  
  // Требуется замена АКБ
  p_data->data_bits.battery_replacement_required_alarm = p_vars->vars_get_alarm_status( ALARM_BATTERY_REPLACEMENT_REQUIRED );  
  
  // Авария байпаса.
  p_data->data_bits.bypass_emergency_alarm = p_vars->vars_get_alarm_status( ALARM_BYPASS_EMERGENCY );  

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}


void kw_proto_fault_status_unpack( kw_can_msg_t *p_msg )
{
  prop_fault_status_t *p_data = ( prop_fault_status_t *)&p_msg->data[ 0 ];

  // Неверное подключение нейтрали входного напряжения ИБП
  p_vars->vars_set_alarm_status( ALARM_NEUTRAL, p_data->data_bits.neutral_alarm );                                       
    
  // Входное напряжение ИБП в фазе А вне допустимого диапазона  
  p_vars->vars_set_alarm_status( ALARM_IN_VOLTAGE_PHASE_A_OUT_RANGE, p_data->data_bits.in_v_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  // Входное напряжение ИБП в фазе B вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_VOLTAGE_PHASE_B_OUT_RANGE, p_data->data_bits.in_v_phase_b_out_range_alarm );

  // Входное напряжение ИБП в фазе C вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_VOLTAGE_PHASE_C_OUT_RANGE, p_data->data_bits.in_v_phase_c_out_range_alarm ); 
#endif

  // Значение входного тока ИБП в фазе A вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_CURRENT_PHASE_A_OUT_RANGE, p_data->data_bits.in_i_phase_a_out_range_alarm ); 

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Значение входного тока ИБП в фазе B вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_CURRENT_PHASE_B_OUT_RANGE, p_data->data_bits.in_i_phase_b_out_range_alarm ); 
  
  // Значение входного тока ИБП в фазе C вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_CURRENT_PHASE_C_OUT_RANGE, p_data->data_bits.in_i_phase_c_out_range_alarm ); 
#endif

  // Частота входного напряжения ИБП в фазе A вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_FREQUENCY_PHASE_A_OUT_RANGE, p_data->data_bits.in_frequency_phase_a_out_range_alarm );        

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Частота входного напряжения ИБП в фазе B вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_FREQUENCY_PHASE_B_OUT_RANGE, p_data->data_bits.in_frequency_phase_b_out_range_alarm );
  
  // Частота входного напряжения ИБП в фазе C вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_FREQUENCY_PHASE_C_OUT_RANGE, p_data->data_bits.in_frequency_phase_c_out_range_alarm );        
#endif

  // Фазовый сдвиг входного напряжения ИБП (фаза A) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_A_OUT_RANGE, p_data->data_bits.in_phase_shift_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Фазовый сдвиг входного напряжения ИБП (фаза B) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_B_OUT_RANGE, p_data->data_bits.in_phase_shift_phase_b_out_range_alarm );
  
  // Фазовый сдвиг входного напряжения ИБП (фаза C) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_IN_PHASE_SHIFT_PHASE_C_OUT_RANGE, p_data->data_bits.in_phase_shift_phase_c_out_range_alarm );
#endif

  // Положительное напряжение на шине постоянного тока не соответствует уставке
  p_vars->vars_set_alarm_status( ALARM_MIDDLE_POSITIVE_VOLTAGE_DOESNT_MATCH_SETPOINT, p_data->data_bits.middle_v_positive_alarm );
  
  // Отрицательное напряжение на шине постоянного тока не соответствует уставке
  p_vars->vars_set_alarm_status( ALARM_MIDDLE_NEGATIVE_VOLTAGE_DOESNT_MATCH_SETPOINT, p_data->data_bits.middle_v_negative_alarm );

  // Выходное напряжение ИБП в фазе А вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_A_OUT_RANGE, p_data->data_bits.out_v_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )      
  // Выходное напряжение ИБП в фазе B вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_B_OUT_RANGE, p_data->data_bits.out_v_phase_b_out_range_alarm );
  
  // Выходное напряжение ИБП в фазе C вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_C_OUT_RANGE, p_data->data_bits.out_v_phase_c_out_range_alarm );      
#endif

  // Превышение выходного тока ИБП в фазе A
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_A_EXCEEED, p_data->data_bits.out_i_phase_a_exceed_alarm );      

#if ( KW_PROTO_PHASE_NUMBERS > 1 )        
  // Превышение выходного тока ИБП в фазе B
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_B_EXCEEED, p_data->data_bits.out_i_phase_b_exceed_alarm );      
  
  // Превышение выходного тока ИБП в фазе C
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_C_EXCEEED, p_data->data_bits.out_i_phase_c_exceed_alarm );
#endif

  // Короткое замыкание на выходе ИБП в фазе A
  p_vars->vars_set_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_A, p_data->data_bits.out_short_circut_phase_a_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )          
  // Короткое замыкание на выходе ИБП в фазе B
  p_vars->vars_set_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_B, p_data->data_bits.out_short_circut_phase_b_alarm );      
  
  // Короткое замыкание на выходе ИБП в фазе C
  p_vars->vars_set_alarm_status( ALARM_OUT_SHORT_CIRCUIT_PHASE_C, p_data->data_bits.out_short_circut_phase_c_alarm );      
#endif

  // Превышение выходной мощности
  p_vars->vars_set_alarm_status( ALARM_OUT_POWER_EXCEEED, p_data->data_bits.out_power_exceed_alarm );      

  
  // Превышение пикового значения выходного тока ИБП в фазе A
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED, p_data->data_bits.out_peak_i_phase_a_exceed_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Превышение пикового значения выходного тока ИБП в фазе B
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED, p_data->data_bits.out_peak_i_phase_b_exceed_alarm );
  
  // Превышение пикового значения выходного тока ИБП в фазе C
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED, p_data->data_bits.out_peak_i_phase_c_exceed_alarm ); 
#endif

  // Перенапряжение на выходе ИБП в фазе A
  p_vars->vars_set_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_A, p_data->data_bits.out_over_v_phase_a_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Перенапряжение на выходе ИБП в фазе B
  p_vars->vars_set_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_B, p_data->data_bits.out_over_v_phase_b_alarm );
  
  // Перенапряжение на выходе ИБП в фазе C
  p_vars->vars_set_alarm_status( ALARM_OUT_OVER_VOLTAGE_PHASE_C, p_data->data_bits.out_over_v_phase_c_alarm ); 
#endif
  // Частота выходного напряжения ИБП в фазе A вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_FREQUENCY_PHASE_A_OUT_RANGE, p_data->data_bits.out_frequency_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Частота выходного напряжения ИБП в фазе B вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_FREQUENCY_PHASE_B_OUT_RANGE, p_data->data_bits.out_frequency_phase_b_out_range_alarm ); 
  
  // Частота выходного напряжения ИБП в фазе C вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_FREQUENCY_PHASE_C_OUT_RANGE, p_data->data_bits.out_frequency_phase_c_out_range_alarm ); 
#endif
  // Фазовый сдвиг выходного напряжения ИБП (фаза A) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A_OUT_RANGE, p_data->data_bits.out_v_phase_shift_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  // Фазовый сдвиг выходного напряжения ИБП (фаза B) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B_OUT_RANGE, p_data->data_bits.out_v_phase_shift_phase_b_out_range_alarm );

  // Фазовый сдвиг выходного напряжения ИБП (фаза C) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C_OUT_RANGE, p_data->data_bits.out_v_phase_shift_phase_c_out_range_alarm );
#endif

  // Фазовый сдвиг выходного тока ИБП (фаза A) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_A_OUT_RANGE, p_data->data_bits.out_i_phase_shift_phase_a_out_range_alarm );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )    
  // Фазовый сдвиг выходного тока ИБП (фаза B) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_B_OUT_RANGE, p_data->data_bits.out_i_phase_shift_phase_b_out_range_alarm );
  
  // Фазовый сдвиг выходного тока ИБП (фаза C) вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_C_OUT_RANGE, p_data->data_bits.out_i_phase_shift_phase_c_out_range_alarm ); 
#endif

  // Значение тока зарядного устройства не соответствует уставке
  p_vars->vars_set_alarm_status( ALARM_CHARGER_CURRENT_VALUE_DOESNT_MATCH_SETPOINT, p_data->data_bits.charger_i_value_dosent_match_setpoint_alarm );  
  
  // Напряжение АКБ вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_BATTERY_VOLTAGE_OUT_RANGE, p_data->data_bits.battery_v_out_range_alarm );  
  
  // Ток разряда АКБ вне допустимого диапазона
  p_vars->vars_set_alarm_status( ALARM_BATTERY_CURRENT_OUT_RANGE, p_data->data_bits.battery_i_out_range_alarm );  
  
  // Отсутствует АКБ
  p_vars->vars_set_alarm_status( ALARM_NO_BATTERY, p_data->data_bits.no_battery_alarm );  
  
  // АКБ разряжена
  p_vars->vars_set_alarm_status( ALARM_BATTERY_DISCHARGE, p_data->data_bits.battery_discharge_alarm );  

  // Температура охладителя ККМ превысила уставку
  p_vars->vars_set_alarm_status( ALARM_TEMPERATURE_KKM_COOLER_EXCEED_SETPOINT, p_data->data_bits.temp_kkm_cooler_exceed_setpoint_alarm );  
  
  // Температура охладителя инвертора превысила уставку
  p_vars->vars_set_alarm_status( ALARM_TEMPERATURE_INVERTER_COOLER_EXCEED_SETPOINT, p_data->data_bits.temp_inverter_cooler_exceed_setpoint_alarm );
  
  // Температура батареи превысила уставку
  p_vars->vars_set_alarm_status( ALARM_TEMPERATURE_BATTERY_EXCEED_SETPOINT, p_data->data_bits.temp_battery_exceed_setpoint_alarm );
  
  // Температура воздуха внутри корпуса ИБП превысила уставку
  p_vars->vars_set_alarm_status( ALARM_TEMPERATURE_INBOX_AIR_EXCEED_SETPOINT, p_data->data_bits.temp_inbox_air_exceed_setpoint_alarm ); 

  // Авария вентилятора 1
  p_vars->vars_set_alarm_status( ALARM_FUN_1_EMERGENCY, p_data->data_bits.fun_1_emergency_alarm );  
  
  // Авария вентилятора 2
  p_vars->vars_set_alarm_status( ALARM_FUN_2_EMERGENCY, p_data->data_bits.fun_2_emergency_alarm );  

  // Время работы от АКБ менше заданного при текущей нагрузке
  p_vars->vars_set_alarm_status( ALARM_BATTERY_TIME_LESS_SETPOINT, p_data->data_bits.battery_time_less_setpoint_alarm );  
  
  // Требуется замена АКБ
  p_vars->vars_set_alarm_status( ALARM_BATTERY_REPLACEMENT_REQUIRED, p_data->data_bits.battery_replacement_required_alarm );  
  
  // Авария байпаса.
  p_vars->vars_set_alarm_status( ALARM_BYPASS_EMERGENCY, p_data->data_bits.bypass_emergency_alarm );   
}


void kw_proto_in_voltage_pack_and_send( ENUM_IN_CHANNELS in_chan )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_VOLTAGE, 
		PGN_PROP_IN2_VOLTAGE,
    PGN_PROP_IN3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_IN_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_IN_3_VOLTAGE_RMS_PHASE_A 
	};
	
#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  const ENUM_VALUE_NAME V_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_VOLTAGE_RMS_PHASE_B,
    VALUE_IN_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_IN_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_VOLTAGE_RMS_PHASE_C,
    VALUE_IN_2_VOLTAGE_RMS_PHASE_C,
    VALUE_IN_3_VOLTAGE_RMS_PHASE_C 
  };
#endif

  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_A[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_A, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_A, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_A 
  };

#if ( KW_PROTO_PHASE_NUMBERS > 1 )	  
  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_B[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_B, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_B, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_B 
  };
  
  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_C[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_C, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_C, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_C 
  };
#endif  

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )in_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_in_voltage_t *p_data = ( prop_in_voltage_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( V_PHASE_A[ ind ], &val );
	
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( V_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_b = tmp;
  
	p_vars->vars_get_value( V_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_c = tmp;
#endif  
	
	p_vars->vars_get_value( PHASE_SHIFT_PHASE_A[ ind ], &val );
	p_data->data_bits.phase_shift_a = val.val_int;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( PHASE_SHIFT_PHASE_B[ ind ], &val );
	p_data->data_bits.phase_shift_b = val.val_int;

	p_vars->vars_get_value( PHASE_SHIFT_PHASE_C[ ind ], &val );
	p_data->data_bits.phase_shift_c = val.val_int;
#endif

	p_vars->vars_get_value( VALUE_UPS_WORKING_MODE, &val );
	p_data->data_bits.pm_working_mode = val.val_int;

	p_vars->vars_get_value( VALUE_ON_OFF_BUTTON_STATE, &val );
	p_data->data_bits.on_off_btn_status = val.val_int;
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}

void kw_proto_in_voltage_unpack( kw_can_msg_t *p_msg )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_VOLTAGE, 
		PGN_PROP_IN2_VOLTAGE,
    PGN_PROP_IN3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_IN_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_IN_3_VOLTAGE_RMS_PHASE_A 
	};
	
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	  
  const ENUM_VALUE_NAME V_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_VOLTAGE_RMS_PHASE_B,
    VALUE_IN_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_IN_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_VOLTAGE_RMS_PHASE_C,
    VALUE_IN_2_VOLTAGE_RMS_PHASE_C,
    VALUE_IN_3_VOLTAGE_RMS_PHASE_C 
  };
#endif

  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_A[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_A, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_A, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_A 
  };
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	  
  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_B[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_B, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_B, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_B 
  };
  
  const ENUM_VALUE_NAME PHASE_SHIFT_PHASE_C[ IN_CHANNEL_MAX ] = 
  { 
    VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_C, 
    VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_C, 
    VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_C 
  };
#endif  

	value_pack_t val;

  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3)
    return;


  // обработка данных
  prop_in_voltage_t *p_data = ( prop_in_voltage_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( V_PHASE_A[ ind ], p_data->data_bits.v_rms_phase_a );
    
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( V_PHASE_B[ ind ], p_data->data_bits.v_rms_phase_b );
  kw_proto_vars_unpack_value( V_PHASE_C[ ind ], p_data->data_bits.v_rms_phase_c );  
#endif  
	
  kw_proto_vars_unpack_value( PHASE_SHIFT_PHASE_A[ ind ], p_data->data_bits.phase_shift_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( PHASE_SHIFT_PHASE_B[ ind ], p_data->data_bits.phase_shift_b );
  kw_proto_vars_unpack_value( PHASE_SHIFT_PHASE_C[ ind ], p_data->data_bits.phase_shift_c );
#endif
  
  kw_proto_vars_unpack_value( VALUE_UPS_WORKING_MODE, p_data->data_bits.pm_working_mode );
  kw_proto_vars_unpack_value( VALUE_ON_OFF_BUTTON_STATE, p_data->data_bits.on_off_btn_status );  
}


void kw_proto_in_current_pack_and_send( ENUM_IN_CHANNELS in_chan )
{
    // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_CURRENT, 
		PGN_PROP_IN2_CURRENT,
    PGN_PROP_IN3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_CURRENT_RMS_PHASE_A, 
		VALUE_IN_2_CURRENT_RMS_PHASE_A, 
		VALUE_IN_3_CURRENT_RMS_PHASE_A 
	};
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	
  const ENUM_VALUE_NAME I_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_CURRENT_RMS_PHASE_B,
    VALUE_IN_2_CURRENT_RMS_PHASE_B, 
		VALUE_IN_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_CURRENT_RMS_PHASE_C,
    VALUE_IN_2_CURRENT_RMS_PHASE_C,
    VALUE_IN_3_CURRENT_RMS_PHASE_C 
  };
#endif

  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_POWER,
    VALUE_IN_2_POWER,
    VALUE_IN_3_POWER 
  };
  
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )in_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_in_current_t *p_data = ( prop_in_current_t *)&msg.data[ 0 ];

  // токи по входу
	p_vars->vars_get_value( I_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( I_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_b = tmp;

	p_vars->vars_get_value( I_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_c = tmp;
#endif  
  
  // мощность по входу
	p_vars->vars_get_value( POWER[ ind ], &val );
	p_data->data_bits.in_power = val.val_int;  


	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_in_current_unpack( kw_can_msg_t *p_msg )
{
    // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_CURRENT, 
		PGN_PROP_IN2_CURRENT,
    PGN_PROP_IN3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_CURRENT_RMS_PHASE_A, 
		VALUE_IN_2_CURRENT_RMS_PHASE_A, 
		VALUE_IN_3_CURRENT_RMS_PHASE_A 
	};
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME I_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_CURRENT_RMS_PHASE_B,
    VALUE_IN_2_CURRENT_RMS_PHASE_B, 
		VALUE_IN_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_CURRENT_RMS_PHASE_C,
    VALUE_IN_2_CURRENT_RMS_PHASE_C,
    VALUE_IN_3_CURRENT_RMS_PHASE_C 
  };
#endif  

  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_POWER,
    VALUE_IN_2_POWER,
    VALUE_IN_3_POWER 
  };
  
  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3)
    return;

  prop_in_current_t *p_data = ( prop_in_current_t *)&p_msg->data[ 0 ];

  // токи по входу
  kw_proto_vars_unpack_value( I_PHASE_A[ ind ], p_data->data_bits.i_rms_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( I_PHASE_B[ ind ], p_data->data_bits.i_rms_phase_b );
  kw_proto_vars_unpack_value( I_PHASE_C[ ind ], p_data->data_bits.i_rms_phase_c );
#endif  
  
  // мощность по входу
  kw_proto_vars_unpack_value( POWER[ ind ], p_data->data_bits.in_power );
}


void kw_proto_in_frequency_pack_and_send( ENUM_IN_CHANNELS in_chan )
{
    // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_FREQENCY, 
		PGN_PROP_IN2_FREQENCY,
    PGN_PROP_IN3_FREQENCY 
  }; 

  const ENUM_VALUE_NAME FREQ_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_FREQUENCY_PHASE_A, 
		VALUE_IN_2_FREQUENCY_PHASE_A, 
		VALUE_IN_3_FREQUENCY_PHASE_A 
	};
	
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	  
  const ENUM_VALUE_NAME FREQ_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_FREQUENCY_PHASE_B, 
		VALUE_IN_2_FREQUENCY_PHASE_B, 
		VALUE_IN_3_FREQUENCY_PHASE_B 
	};
  
  const ENUM_VALUE_NAME FREQ_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_FREQUENCY_PHASE_C, 
		VALUE_IN_2_FREQUENCY_PHASE_C, 
		VALUE_IN_3_FREQUENCY_PHASE_C 
  };
#endif  

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )in_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_in_frequency_t *p_data = ( prop_in_frequency_t *)&msg.data[ 0 ];

  // частота по входу
	p_vars->vars_get_value( FREQ_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1F ) );
	p_data->data_bits.freq_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( FREQ_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_b = tmp;

	p_vars->vars_get_value( FREQ_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_c = tmp;
#endif  

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_in_frequency_unpack( kw_can_msg_t *p_msg )
{

    // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ IN_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_IN1_FREQENCY, 
		PGN_PROP_IN2_FREQENCY,
    PGN_PROP_IN3_FREQENCY 
  }; 

  const ENUM_VALUE_NAME FREQ_PHASE_A[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_FREQUENCY_PHASE_A, 
		VALUE_IN_2_FREQUENCY_PHASE_A, 
		VALUE_IN_3_FREQUENCY_PHASE_A 
	};

#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME FREQ_PHASE_B[ IN_CHANNEL_MAX ] = 
	{
    VALUE_IN_1_FREQUENCY_PHASE_B, 
		VALUE_IN_2_FREQUENCY_PHASE_B, 
		VALUE_IN_3_FREQUENCY_PHASE_B 
	};
  
  const ENUM_VALUE_NAME FREQ_PHASE_C[ IN_CHANNEL_MAX ] = 
  {
    VALUE_IN_1_FREQUENCY_PHASE_C, 
		VALUE_IN_2_FREQUENCY_PHASE_C, 
		VALUE_IN_3_FREQUENCY_PHASE_C 
  };
#endif

  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3 )
    return;

  prop_in_frequency_t *p_data = ( prop_in_frequency_t *)&p_msg->data[ 0 ];

  // частота по входу
  kw_proto_vars_unpack_value( FREQ_PHASE_A[ ind ], p_data->data_bits.freq_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( FREQ_PHASE_B[ ind ], p_data->data_bits.freq_phase_b );
  kw_proto_vars_unpack_value( FREQ_PHASE_C[ ind ], p_data->data_bits.freq_phase_c );
#endif  

}

void kw_proto_in_status_pack_and_send( void )
{
  kw_can_msg_t msg;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_IN_STATUS, 6 ); // заголовок	

  prop_in_status_t *p_data = ( prop_in_status_t *)&msg.data[ 0 ];

  // счетчик плохих состояний
	p_vars->vars_get_value( VALUE_IN_LINES_BAD_STATES_COUNT, &val );
	p_data->data_bits.bad_states_count = val.val_int;

  // число линий
	p_vars->vars_get_value( VALUE_IN_LINES_NUMBERS, &val );
	p_data->data_bits.in_lines_number = val.val_int;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );   
}

void kw_proto_in_status_unpack( kw_can_msg_t *p_msg )
{
  prop_in_status_t *p_data = ( prop_in_status_t *)&p_msg->data[ 0 ];

  // счетчик плохих состояний

  kw_proto_vars_unpack_value( VALUE_IN_LINES_BAD_STATES_COUNT, p_data->data_bits.bad_states_count );


  // число линий
  kw_proto_vars_unpack_value( VALUE_IN_LINES_NUMBERS, p_data->data_bits.in_lines_number );
}

void kw_proto_out_voltage_pack_and_send( ENUM_OUT_CHANNELS out_chan )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ OUT_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_OUT1_VOLTAGE, 
		PGN_PROP_OUT2_VOLTAGE,
    PGN_PROP_OUT3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_OUT_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_OUT_3_VOLTAGE_RMS_PHASE_A 
	};
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME V_PHASE_B[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_B,
    VALUE_OUT_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_OUT_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ OUT_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_C,
    VALUE_OUT_2_VOLTAGE_RMS_PHASE_C,
    VALUE_OUT_3_VOLTAGE_RMS_PHASE_C 
  };
#endif  

  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_POWER,
    VALUE_OUT_2_POWER,
    VALUE_OUT_3_POWER 
  };

  const ENUM_VALUE_NAME PERCENT[ IN_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_PERCENT,
    VALUE_OUT_2_PERCENT,
    VALUE_OUT_3_PERCENT 
  };

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )out_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( V_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( V_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_b = tmp;
  
	p_vars->vars_get_value( V_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_c = tmp;
#endif  

	p_vars->vars_get_value( POWER[ ind ], &val );
	p_data->data_bits.out_power = val.val_int;

	p_vars->vars_get_value( PERCENT[ ind ], &val );
	p_data->data_bits.out_percent = val.val_int;
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}

void kw_proto_out_voltage_unpack( kw_can_msg_t *p_msg )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ OUT_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_OUT1_VOLTAGE, 
		PGN_PROP_OUT2_VOLTAGE,
    PGN_PROP_OUT3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_OUT_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_OUT_3_VOLTAGE_RMS_PHASE_A 
	};
#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME V_PHASE_B[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_B,
    VALUE_OUT_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_OUT_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ OUT_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_VOLTAGE_RMS_PHASE_C,
    VALUE_OUT_2_VOLTAGE_RMS_PHASE_C,
    VALUE_OUT_3_VOLTAGE_RMS_PHASE_C 
  };
#endif

  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_POWER,
    VALUE_OUT_2_POWER,
    VALUE_OUT_3_POWER 
  };

  const ENUM_VALUE_NAME PERCENT[ IN_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_PERCENT,
    VALUE_OUT_2_PERCENT,
    VALUE_OUT_3_PERCENT 
  };

  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3 )
    return;

  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( V_PHASE_A[ ind ], p_data->data_bits.v_rms_phase_a );
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( V_PHASE_B[ ind ], p_data->data_bits.v_rms_phase_b );
  kw_proto_vars_unpack_value( V_PHASE_C[ ind ], p_data->data_bits.v_rms_phase_c );
#endif  

  kw_proto_vars_unpack_value( POWER[ ind ], p_data->data_bits.out_power );
  kw_proto_vars_unpack_value( PERCENT[ ind ], p_data->data_bits.out_percent );
}

void kw_proto_out_current_pack_and_send( ENUM_OUT_CHANNELS out_chan )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ OUT_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_OUT1_CURRENT, 
		PGN_PROP_OUT2_CURRENT,
    PGN_PROP_OUT3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_CURRENT_RMS_PHASE_A, 
		VALUE_OUT_2_CURRENT_RMS_PHASE_A, 
		VALUE_OUT_3_CURRENT_RMS_PHASE_A 
	};
#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME I_PHASE_B[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_CURRENT_RMS_PHASE_B,
    VALUE_OUT_2_CURRENT_RMS_PHASE_B, 
		VALUE_OUT_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ OUT_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_CURRENT_RMS_PHASE_C,
    VALUE_OUT_2_CURRENT_RMS_PHASE_C,
    VALUE_OUT_3_CURRENT_RMS_PHASE_C 
  };
#endif

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )out_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_out_current_t *p_data = ( prop_out_current_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( I_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( I_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_b = tmp;
  
	p_vars->vars_get_value( I_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_c = tmp;
#endif  
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}


void kw_proto_out_current_unpack( kw_can_msg_t *p_msg )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ OUT_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_OUT1_CURRENT, 
		PGN_PROP_OUT2_CURRENT,
    PGN_PROP_OUT3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_CURRENT_RMS_PHASE_A, 
		VALUE_OUT_2_CURRENT_RMS_PHASE_A, 
		VALUE_OUT_3_CURRENT_RMS_PHASE_A 
	};
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	
	
  const ENUM_VALUE_NAME I_PHASE_B[ OUT_CHANNEL_MAX ] = 
	{
    VALUE_OUT_1_CURRENT_RMS_PHASE_B,
    VALUE_OUT_2_CURRENT_RMS_PHASE_B, 
		VALUE_OUT_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ OUT_CHANNEL_MAX ] = 
  {
    VALUE_OUT_1_CURRENT_RMS_PHASE_C,
    VALUE_OUT_2_CURRENT_RMS_PHASE_C,
    VALUE_OUT_3_CURRENT_RMS_PHASE_C 
  };
#endif

  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3 )
    return;

  prop_out_current_t *p_data = ( prop_out_current_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( I_PHASE_A[ ind ], p_data->data_bits.i_rms_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( I_PHASE_B[ ind ], p_data->data_bits.i_rms_phase_b );
  kw_proto_vars_unpack_value( I_PHASE_C[ ind ], p_data->data_bits.i_rms_phase_c );
#endif  
}


void kw_proto_out_frequency_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_OUT_FREQENCY, 6 ); // заголовок	

  prop_out_frequency_t *p_data = ( prop_out_frequency_t *)&msg.data[ 0 ];

  // частота по выходу
	p_vars->vars_get_value( VALUE_OUT_FREQUENCY_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1F ) );
	p_data->data_bits.freq_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_OUT_FREQUENCY_PHASE_B, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_b = tmp;

	p_vars->vars_get_value( VALUE_OUT_FREQUENCY_PHASE_C, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_c = tmp;
#endif  

	p_vars->vars_get_value( VALUE_OUT_POWER_SOURCE, &val );
	p_data->data_bits.out_power_source = val.val_int;

	p_vars->vars_get_value( VALUE_OUT_LINES_NUMBER, &val );
	p_data->data_bits.out_lines_number = val.val_int;

	p_vars->vars_get_value( VALUE_TEST_RESULT, &val );
	p_data->data_bits.test_result = val.val_int;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_out_frequency_unpack( kw_can_msg_t *p_msg )
{
  prop_out_frequency_t *p_data = ( prop_out_frequency_t *)&p_msg->data[ 0 ];

  // частота по выходу
  kw_proto_vars_unpack_value( VALUE_OUT_FREQUENCY_PHASE_A, p_data->data_bits.freq_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_OUT_FREQUENCY_PHASE_B, p_data->data_bits.freq_phase_b );
  kw_proto_vars_unpack_value( VALUE_OUT_FREQUENCY_PHASE_C, p_data->data_bits.freq_phase_c );
#endif  

  kw_proto_vars_unpack_value( VALUE_OUT_POWER_SOURCE, p_data->data_bits.out_power_source );

  kw_proto_vars_unpack_value( VALUE_OUT_LINES_NUMBER, p_data->data_bits.out_lines_number );

  kw_proto_vars_unpack_value( VALUE_TEST_RESULT, p_data->data_bits.test_result );
}


void kw_proto_out_phase_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_OUT_PHASE_SHIFT, 6 ); // заголовок	

  prop_out_frequency_t *p_data = ( prop_out_frequency_t *)&msg.data[ 0 ];

  // частота по выходу
	p_vars->vars_get_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.freq_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.freq_phase_b = tmp;

	p_vars->vars_get_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.freq_phase_c = tmp;
#endif  

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_out_phase_unpack( kw_can_msg_t *p_msg )
{
  prop_out_frequency_t *p_data = ( prop_out_frequency_t *)&p_msg->data[ 0 ];

  // частота по выходу
  kw_proto_vars_unpack_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A, p_data->data_bits.freq_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B, p_data->data_bits.freq_phase_b );
  kw_proto_vars_unpack_value( VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C, p_data->data_bits.freq_phase_c );
#endif    
}

void kw_proto_bypass_voltage_pack_and_send( ENUM_BYPASS_CHANNELS bypass_chan )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ BYPASS_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_BYPASS1_VOLTAGE, 
		PGN_PROP_BYPASS2_VOLTAGE,
    PGN_PROP_BYPASS3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_A 
	};
#if ( KW_PROTO_PHASE_NUMBERS > 1 )		
  const ENUM_VALUE_NAME V_PHASE_B[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_B,
    VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ BYPASS_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_C,
    VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_C,
    VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_C 
  };
#endif

  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_POWER,
    VALUE_BYPASS_2_POWER,
    VALUE_BYPASS_3_POWER 
  };


  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )bypass_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( V_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( V_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_b = tmp;
  
	p_vars->vars_get_value( V_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5 ) );
	p_data->data_bits.v_rms_phase_c = tmp;
#endif  

	p_vars->vars_get_value( POWER[ ind ], &val );
	p_data->data_bits.out_power = val.val_int;

	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}


void kw_proto_bypass_voltage_unpack( kw_can_msg_t *p_msg )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ BYPASS_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_BYPASS1_VOLTAGE, 
		PGN_PROP_BYPASS2_VOLTAGE,
    PGN_PROP_BYPASS3_VOLTAGE 
  }; 

  const ENUM_VALUE_NAME V_PHASE_A[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_A, 
		VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_A, 
		VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_A 
	};
	
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	
  const ENUM_VALUE_NAME V_PHASE_B[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_B,
    VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_B, 
		VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME V_PHASE_C[ BYPASS_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_C,
    VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_C,
    VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_C 
  };
#endif
  const ENUM_VALUE_NAME POWER[ IN_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_POWER,
    VALUE_BYPASS_2_POWER,
    VALUE_BYPASS_3_POWER 
  };


  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3 )
    return;

  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( V_PHASE_A[ ind ], p_data->data_bits.v_rms_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( V_PHASE_B[ ind ], p_data->data_bits.v_rms_phase_b );
  kw_proto_vars_unpack_value( V_PHASE_C[ ind ], p_data->data_bits.v_rms_phase_c );
#endif  

  kw_proto_vars_unpack_value( POWER[ ind ], p_data->data_bits.out_power );
}

void kw_proto_bypass_current_pack_and_send( ENUM_BYPASS_CHANNELS bypass_chan )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ BYPASS_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_BYPASS1_CURRENT, 
		PGN_PROP_BYPASS2_CURRENT,
    PGN_PROP_BYPASS3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_A, 
		VALUE_BYPASS_2_CURRENT_RMS_PHASE_A, 
		VALUE_BYPASS_3_CURRENT_RMS_PHASE_A 
	};

#if ( KW_PROTO_PHASE_NUMBERS > 1 )	
  const ENUM_VALUE_NAME I_PHASE_B[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_B,
    VALUE_BYPASS_2_CURRENT_RMS_PHASE_B, 
		VALUE_BYPASS_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ BYPASS_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_C,
    VALUE_BYPASS_2_CURRENT_RMS_PHASE_C,
    VALUE_BYPASS_3_CURRENT_RMS_PHASE_C 
  };
#endif

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  uint32_t ind = ( uint32_t )bypass_chan; // Индекс в массиве

  kw_proto_prepare_msg( &msg, PGN[ ind ], 6 ); // заголовок	

  prop_out_current_t *p_data = ( prop_out_current_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( I_PHASE_A[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( I_PHASE_B[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_b = tmp;
  
	p_vars->vars_get_value( I_PHASE_C[ ind ], &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_c = tmp;
#endif  
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}

void kw_proto_bypass_current_unpack( kw_can_msg_t *p_msg )
{
  // переменные для разных каналов
  const ENUM_PGN_CODES PGN[ BYPASS_CHANNEL_MAX ] = 
	{ 
		PGN_PROP_BYPASS1_CURRENT, 
		PGN_PROP_BYPASS2_CURRENT,
    PGN_PROP_BYPASS3_CURRENT 
  }; 

  const ENUM_VALUE_NAME I_PHASE_A[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_A, 
		VALUE_BYPASS_2_CURRENT_RMS_PHASE_A, 
		VALUE_BYPASS_3_CURRENT_RMS_PHASE_A 
	};
#if ( KW_PROTO_PHASE_NUMBERS > 1 )	
  const ENUM_VALUE_NAME I_PHASE_B[ BYPASS_CHANNEL_MAX ] = 
	{
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_B,
    VALUE_BYPASS_2_CURRENT_RMS_PHASE_B, 
		VALUE_BYPASS_3_CURRENT_RMS_PHASE_B 
	};
  
  const ENUM_VALUE_NAME I_PHASE_C[ BYPASS_CHANNEL_MAX ] = 
  {
    VALUE_BYPASS_1_CURRENT_RMS_PHASE_C,
    VALUE_BYPASS_2_CURRENT_RMS_PHASE_C,
    VALUE_BYPASS_3_CURRENT_RMS_PHASE_C 
  };
#endif

  uint32_t ind; // Индекс в массиве
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  

  // поиск канала
  for( ind = 0; ind < 3; ind++ )
  {
    if( PGN[ ind ] == p_id->broadcast_id.PGN )
      break;    
  }
  
  if( ind >= 3 )
    return;

  prop_out_current_t *p_data = ( prop_out_current_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( I_PHASE_A[ ind ], p_data->data_bits.i_rms_phase_a );
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( I_PHASE_B[ ind ], p_data->data_bits.i_rms_phase_b );
  kw_proto_vars_unpack_value( I_PHASE_C[ ind ], p_data->data_bits.i_rms_phase_c );
#endif    
}

void kw_proto_bypass_frequency_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_BYPASS_FREQENCY, 6 ); // заголовок	

  prop_bypass_frequency_t *p_data = ( prop_bypass_frequency_t *)&msg.data[ 0 ];

  // частота по выходу
	p_vars->vars_get_value( VALUE_BYPASS_FREQUENCY_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1F ) );
	p_data->data_bits.freq_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_BYPASS_FREQUENCY_PHASE_B, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_b = tmp;

	p_vars->vars_get_value( VALUE_BYPASS_FREQUENCY_PHASE_C, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.1 ) );
	p_data->data_bits.freq_phase_c = tmp;
#endif  

	p_vars->vars_get_value( VALUE_BYPASS_LINES_NUMBER, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.bypass_lines_number = tmp;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_bypass_frequency_unpack( kw_can_msg_t *p_msg )
{
  prop_bypass_frequency_t *p_data = ( prop_bypass_frequency_t *)&p_msg->data[ 0 ];

  // частота по выходу
  kw_proto_vars_unpack_value( VALUE_BYPASS_FREQUENCY_PHASE_A, p_data->data_bits.freq_phase_a );


#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_BYPASS_FREQUENCY_PHASE_B, p_data->data_bits.freq_phase_b );
  kw_proto_vars_unpack_value( VALUE_BYPASS_FREQUENCY_PHASE_C, p_data->data_bits.freq_phase_c );
#endif  

  kw_proto_vars_unpack_value( VALUE_BYPASS_LINES_NUMBER, p_data->data_bits.bypass_lines_number );
}

void kw_proto_bypass_phase_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_BYPASS_PHASE_SHIFT, 6 ); // заголовок	

  prop_out_phase_shift_t *p_data = ( prop_out_phase_shift_t *)&msg.data[ 0 ];

  // частота по выходу
	p_vars->vars_get_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_A, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_B, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_phase_b = tmp;

	p_vars->vars_get_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_C, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_phase_c = tmp;
#endif  

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_bypass_phase_unpack( kw_can_msg_t *p_msg )
{
  prop_out_phase_shift_t *p_data = ( prop_out_phase_shift_t *)&p_msg->data[ 0 ];

  kw_proto_vars_unpack_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_A, p_data->data_bits.phase_shift_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )  
  kw_proto_vars_unpack_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_B, p_data->data_bits.phase_shift_phase_b );
  kw_proto_vars_unpack_value( VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_C, p_data->data_bits.phase_shift_phase_c );
#endif  

}


void kw_proto_prop_middle_voltage_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_MIDDLE_VOLTAGE, 6 ); // заголовок	

  prop_middle_voltage_t *p_data = ( prop_middle_voltage_t *)&msg.data[ 0 ];

  // напряжения промежуточной шины
	p_vars->vars_get_value( VALUE_MIDDLE_BUS_POSITIVE_VOLTAGE, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_positive = tmp;

	p_vars->vars_get_value( VALUE_MIDDLE_BUS_NEGATIVE_VOLTAGE, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_negative = tmp;

  // фазовые сдвиги тока
	p_vars->vars_get_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_A, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_out_current_phase_a = tmp;

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_B, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_out_current_phase_a = tmp;

	p_vars->vars_get_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_C, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.phase_shift_out_current_phase_a = tmp;
#endif  

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_prop_middle_voltage_unpack( kw_can_msg_t *p_msg )
{
  prop_middle_voltage_t *p_data = ( prop_middle_voltage_t *)&p_msg->data[ 0 ];

  // напряжения промежуточной шины
  kw_proto_vars_unpack_value( VALUE_MIDDLE_BUS_POSITIVE_VOLTAGE, p_data->data_bits.v_positive );
  kw_proto_vars_unpack_value( VALUE_MIDDLE_BUS_NEGATIVE_VOLTAGE, p_data->data_bits.v_negative );

  // фазовые сдвиги тока
  kw_proto_vars_unpack_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_A, p_data->data_bits.phase_shift_out_current_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_B, p_data->data_bits.phase_shift_out_current_phase_b );
  kw_proto_vars_unpack_value( VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_C, p_data->data_bits.phase_shift_out_current_phase_c );
#endif    
}

void kw_proto_prop_battery_voltage_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_BATTERY_VOLTAGE, 6 ); // заголовок	

  prop_battery_voltage_t *p_data = ( prop_battery_voltage_t *)&msg.data[ 0 ];

  // напряжения АКБ
	p_vars->vars_get_value( VALUE_BATTERY_VOLTAGE, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.025F ) );
	p_data->data_bits.v_battery = tmp;

  // ток АКБ
	p_vars->vars_get_value( VALUE_BATTERY_CURRENT, &val );
  
  val.val_float += 100.0F; // смещение

	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_battery = tmp;

  // напряжения ЗУ
	p_vars->vars_get_value( VALUE_CHARGER_VOLTAGE, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.025F ) );
	p_data->data_bits.v_charger = tmp;

  // ток ЗУ
	p_vars->vars_get_value( VALUE_CHARGER_CURRENT, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_charger = tmp;


	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_prop_battery_voltage_unpack( kw_can_msg_t *p_msg )
{
  prop_battery_voltage_t *p_data = ( prop_battery_voltage_t *)&p_msg->data[ 0 ];

  // напряжения АКБ
  kw_proto_vars_unpack_value( VALUE_BATTERY_VOLTAGE, p_data->data_bits.v_battery );

  // ток АКБ
  kw_proto_vars_unpack_value( VALUE_BATTERY_CURRENT, p_data->data_bits.i_battery );

  // напряжения ЗУ
  kw_proto_vars_unpack_value( VALUE_CHARGER_VOLTAGE, p_data->data_bits.v_charger );

  // ток ЗУ
  kw_proto_vars_unpack_value( VALUE_CHARGER_CURRENT, p_data->data_bits.i_charger );  
}


void kw_proto_prop_battery_status_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_BATTERY_STATUS, 6 ); // заголовок	

  prop_battery_status_t *p_data = ( prop_battery_status_t *)&msg.data[ 0 ];

  // процент заряда
	p_vars->vars_get_value( VALUE_BATTERY_CHARGE_PERCENT, &val );
	tmp = ( uint32_t )(  val.val_int );
	p_data->data_bits.charge_percent = tmp;

  // время до истощения заряда батареи
	p_vars->vars_get_value( VALUE_BATTERY_REMAINING_TIME, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.remaining_time = tmp;

  // врекмя работы от батареи
	p_vars->vars_get_value( VALUE_BATTERY_WORKING_TIME, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.working_time = tmp;

  // Статус батареи
	p_vars->vars_get_value( VALUE_BATTERY_STATUS, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.battery_status = tmp;


	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_prop_battery_status_unpack( kw_can_msg_t *p_msg )
{
  prop_battery_status_t *p_data = ( prop_battery_status_t *)&p_msg->data[ 0 ];

  // процент заряда
  kw_proto_vars_unpack_value( VALUE_BATTERY_CHARGE_PERCENT, p_data->data_bits.charge_percent );

  // время до истощения заряда батареи
  kw_proto_vars_unpack_value( VALUE_BATTERY_REMAINING_TIME, p_data->data_bits.remaining_time );

  // врекмя работы от батареи
  kw_proto_vars_unpack_value( VALUE_BATTERY_WORKING_TIME, p_data->data_bits.working_time );

  // Статус батареи
  kw_proto_vars_unpack_value( VALUE_BATTERY_STATUS, p_data->data_bits.battery_status );
}

void kw_proto_prop_modules_temperature_status_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_MODULES_TEMPERATURE, 6 ); // заголовок	

  prop_modules_temperature_t *p_data = ( prop_modules_temperature_t *)&msg.data[ 0 ];

  // температура охладителя ККМ
	p_vars->vars_get_value( VALUE_KKM_COOLER_TEMPERATURE, &val );

  val.val_int += 60; // смещение

	tmp = ( uint32_t )(  val.val_int );
	p_data->data_bits.KKM_cooler_temp = tmp;

  // температура воздуха внутри корпуса
	p_vars->vars_get_value( VALUE_INTO_UPS_AIR_TEMPERATURE, &val );

  val.val_int += 60; // смещение

	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.into_box_air_temp = tmp;

  // температура батареи
	p_vars->vars_get_value( VALUE_BATTERY_TEMPERATURE, &val );

  val.val_int += 60; // смещение
	
  tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.battery_temp = tmp;

  // температура охладителя инвертора
	p_vars->vars_get_value( VALUE_INVERTER_COOLER_TEMPERATURE, &val );

  val.val_int += 60; // смещение

	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.inverter_temp = tmp;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_prop_modules_temperature_status_unpack( kw_can_msg_t *p_msg )
{
  prop_modules_temperature_t *p_data = ( prop_modules_temperature_t *)&p_msg->data[ 0 ];

  // температура охладителя ККМ
  kw_proto_vars_unpack_value( VALUE_KKM_COOLER_TEMPERATURE, p_data->data_bits.KKM_cooler_temp );

  // температура воздуха внутри корпуса
  kw_proto_vars_unpack_value( VALUE_INTO_UPS_AIR_TEMPERATURE, p_data->data_bits.into_box_air_temp );

  // температура батареи
  kw_proto_vars_unpack_value( VALUE_BATTERY_TEMPERATURE, p_data->data_bits.battery_temp );

  // температура охладителя инвертора
  kw_proto_vars_unpack_value( VALUE_INVERTER_COOLER_TEMPERATURE, p_data->data_bits.inverter_temp );  
}


void kw_proto_prop_inverter_current_pack_and_send( void )
{

  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_INVERTER_CURRENT, 6 ); // заголовок	

  prop_out_current_t *p_data = ( prop_out_current_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( VALUE_INVERTER_CURRENT_RMS_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01F ) );
	p_data->data_bits.i_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_INVERTER_CURRENT_RMS_PHASE_B, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_b = tmp;
  
	p_vars->vars_get_value( VALUE_INVERTER_CURRENT_RMS_PHASE_C, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.01 ) );
	p_data->data_bits.i_rms_phase_c = tmp;
#endif  
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_prop_inverter_current_unpack( kw_can_msg_t *p_msg )
{
  prop_out_current_t *p_data = ( prop_out_current_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( VALUE_INVERTER_CURRENT_RMS_PHASE_A, p_data->data_bits.i_rms_phase_a );

#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_INVERTER_CURRENT_RMS_PHASE_B, p_data->data_bits.i_rms_phase_b );
  kw_proto_vars_unpack_value( VALUE_INVERTER_CURRENT_RMS_PHASE_C, p_data->data_bits.i_rms_phase_c ); 
#endif  
  
}


void kw_proto_prop_fun_speed_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_FUN_SPEED, 6 ); // заголовок	

  prop_fun_speed_t *p_data = ( prop_fun_speed_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( VALUE_FUN_1_SPEED, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.fun_1_speed = tmp;
  
	p_vars->vars_get_value( VALUE_FUN_2_SPEED, &val );
	tmp = ( uint32_t )( val.val_int );
	p_data->data_bits.fun_2_speed = tmp;
  	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_prop_fun_speed_unpack( kw_can_msg_t *p_msg )
{

  prop_fun_speed_t *p_data = ( prop_fun_speed_t *)&p_msg->data[ 0 ];
  
  kw_proto_vars_unpack_value( VALUE_FUN_1_SPEED, p_data->data_bits.fun_1_speed );
  kw_proto_vars_unpack_value( VALUE_FUN_2_SPEED, p_data->data_bits.fun_2_speed );
}

void kw_proto_prop_setpoints_pack_and_send( void )
{
	value_pack_t val;

	uint8_t buffer[ sizeof(prop_setpoints_t) ];
  prop_setpoints_t *p_data = ( prop_setpoints_t * )buffer;
  
/*
  // Уставка номинального значения выходного напряжения(код 01h)
  p_data->data_bits.out_v_setpoint = 1; 
    
  // Измеренное значение выходного напряжения для расчета калибровочных коэффициентов(код 02h)
  p_data->data_bits.out_v_mesured_setpoint = 1; 
    
  // Уставка верхней границы допустимого входного напряжения ИБП(код 29h)
  p_data->data_bits.in_v_hi_level_setpoint = 1; 
    
  // Уставка нижней границы допустимого входного напряжения ИБП(код 2Ah)  
  p_data->data_bits.in_v_low_level_setpoint = 1; 
  
  // Уставка номинального значения напряжения промежуточной шины постоянного тока(код 30h)
  p_data->data_bits.middle_v_setpoint = 1; 
    
  // Калибровочный коэффициент выходного напряжения (код 03h)       

  p_data->data_bits.out_v_calibration_factor = 1; 
    
  // Допустимое отклонение выходного напряжения от номинального значения(код 04h)  
  p_data->data_bits.our_v_deviation_percent_setpoint = 1;  
    
  // Уставка номинального значения выходного тока(код 05h)
  p_data->data_bits.out_i_setpoint = 1; 
    
  // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента(код 06h )  
  p_data->data_bits.out_i_mesured_phase_a_setpoint = 1; 
    
  // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента(код 07h)  
  p_data->data_bits.out_i_mesured_phase_b_setpoint = 1; 
    
  // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента(код 08h )  
  p_data->data_bits.out_i_mesured_phase_c_setpoint = 1; 
    
  // Калибровочный коэффициент выходного тока в фазе А (код 09h)  -
  p_data->data_bits.out_i_calibration_factor_phase_a = 1; 
    
  // Калибровочный коэффициент выходного тока в фазе B (код 0Ah)
  p_data->data_bits.out_i_calibration_factor_phase_b = 1; 
    
  // Калибровочный коэффициент выходного тока в фазе C (код 0Bh)  
  p_data->data_bits.out_i_calibration_factor_phase_c  = 1; 
    
  // Уставка номинального значения частоты выходного напряжения (код 0Сh)  
  p_data->data_bits.out_frequency_setpoint = 1; 
    
    
  // Допустимое отклонение частоты выходного напряжения от номинального значения (код 0Dh)
  p_data->data_bits.out_freq_dev_percent_setpoint = 1;  
    
  // Уставка максимального значения cosφ на выходе ИБП (код 0Eh)  
  p_data->data_bits.out_v_max_cos_setpoint = 1; 
        
  // Уставка номинального значения выходной мощности (код 0Fh)  
  p_data->data_bits.out_va_setpoint = 1; 
    
  // Допустимое время превышения 100% выходной мощности (код 10h)  
  p_data->data_bits.time_exceed_100_percent_out_power = 1; 
    
  // Допустимое время превышения  первого порога выходной мощности (код 12h)  
  p_data->data_bits.time_exceed_1_level_out_power = 1; 
    
  // Допустимое время превышения  второго порога выходной мощности (код 14h)  
  p_data->data_bits.time_exceed_2_level_out_power = 1; 
    
  // Первый порог превышения выходной мощности(код 11h)  
  p_data->data_bits.level_1_percent_out_va_setpoint = 101;  
    
  // Второй порог превышения выходной мощности(код 13h)
  p_data->data_bits.level_2_percent_out_va_setpoint = 102;
 
  // Уставка максимального пикового выходного тока (код 15h) 
  p_data->data_bits.max_peak_out_i_setpoint = 1; 
    
  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)(код 16h  
  p_data->data_bits.bypass_mode_short_circut_setpoint = 1;     
    
  // Уставка максимальной температуры охладителя ККМ, (код 17h)  
  p_data->data_bits.max_temp_kkm_cooler_setpoint = 1;  
  
  // Уставка максимальной температуры охладителя инвертора (код 18h )
  p_data->data_bits.max_temp_inverter_cooler_setpoint = 1;  
    
  // Уставка максимальной температуры батареи (код 19h )
  p_data->data_bits.max_temp_battery_cooler_setpoint = 1;  
    
  // Уставка максимальной температуры воздуха внутри корпуса ИБП (код 1Ah )
  p_data->data_bits.max_temp_air_setpoint = 1;  
      
  // Уставка минимального допустимого напряжения АКБ (код 1Bh)
  p_data->data_bits.min_v_battery_setpoint = 1; 
  
  // Уставка максимального допустимого напряжения АКБ (код 1Ch)
  p_data->data_bits.max_v_battery_setpoint = 1;
  
  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов(код 1Dh)
  p_data->data_bits.v_battery_mesured_setpoint = 1; 
  
  // Температурный коэффициент АКБ (код 1Eh)
  p_data->data_bits.temp_battery_k_setpoint = 1; 
    
  // Уставка максимального тока разряда АКБ (код 1Fh) [47] = 1, дб  2 
  p_data->data_bits.max_i_discharge_battery_setpoint = 1; 
    
  // Уставка максимального тока заряда АКБ (код 20h)
  p_data->data_bits.max_i_charge_battery_setpoint = 1; 

  // Уставка минимального тока заряда АКБ (код 21h)
  p_data->data_bits.min_i_charge_battery_setpoint = 1; 
    
  // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов(код 24h)  
  p_data->data_bits.i_charge_battery_mesured_setpoint = 1; 
    
    // Уставка напряжения заряда АКБ в  циклическом режиме (код 22h)
  p_data->data_bits.battery_v_cycle_mode_setpoint	=	 1; 

  // Уставка напряжения заряда АКБ в буферном режиме (код 23h)  
  p_data->data_bits.battery_v_buffer_mode_setpoint = 1;     
  
    
  // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов (код 26h)
  p_data->data_bits.battery_v_mesured_setpoint = 1; 

  // Калибровочный коэффициент тока заряда АКБ(код 25h)
  p_data->data_bits.fractional_factor_batt_i_charge_setpoint = 1; 

  // Калибровочный коэффициент напряжения заряда АКБ(код 27h)
  p_data->data_bits.fractional_factor_batt_u_setpoint = 1; 

  // Номинальная ёмкость АКБ (код 28h)    
  p_data->data_bits.nominal_battery_capacity_setpoint = 1; 
  
  // Коэффициент несимметрии по входному напряжению (код 2Bh)
  p_data->data_bits.unbalance_factor_in_v_setpoint = 1;  
    
  // Коэффициент несимметрии по входному току (код 2Dh)
  p_data->data_bits.unbalance_factor_in_i_setpoint = 1;  
    
  // Уставка максимального значения входного тока ИБП (код 2Сh)  
  p_data->data_bits.in_i_max_setpoint = 1; 
    
  // Уставка верхней границы допустимой частоты входного напряжения,  % от номинального значенеия  (код 2Eh)  
  p_data->data_bits.in_frequency_max_setpoint = 1;  
    
  // Уставка нижней границы допустимой частоты входного напряжения, % от номинального значенеия  (код 2Fh)  
  p_data->data_bits.in_frequency_min_setpoint = 1;  

  // Максимальная скорость вентилятора 1(код 31h)  
  p_data->data_bits.max_speed_fun_1_setpoint = 1; 
    
  // Максимальная скорость вентилятора 2(код 32h)
  p_data->data_bits.max_speed_fun_2_setpoint = 1; 
    
  // Максимальная скорость вентилятора резерв 1(код 36h)
  p_data->data_bits.max_speed_fun_res_1_setpoint = 1; 
    
  // Максимальная скорость вентилятора резерв 2 (код 37h)  
  p_data->data_bits.max_speed_fun_res_2_setpoint = 1; 
    
  // Максимальная скорость вентилятора резерв 3 (код 38h)  
  p_data->data_bits.max_speed_fun_res_3_setpoint = 1; 
    
  // Уставка максимальной температуры резерв 1(код 33h)  
  p_data->data_bits.max_temperature_res_1_setpoint = 1;  
    
  // Уставка максимальной температуры резерв 2(код 34h)  
  p_data->data_bits.max_temperature_res_2_setpoint = 1;  
    
  // Уставка максимальной температуры резерв 3(код 35h)    
  p_data->data_bits.max_temperature_res_3_setpoint = 1;  
    
  // Режим работы ИБП после включения (код 39h)
  p_data->data_bits.operating_mode_after_power_on_setpoint = 1;  
    
  // Режим работы ИБП при аварии (код 3Ah)  
  p_data->data_bits.operating_mode_after_emergency_setpoint = 1;  
    
  // Синхронизация с входной сетью (код 3Bh)  
  p_data->data_bits.in_power_line_synchronization_setpoint = 1;  
    
  // Уставка времени работы от батареи, ниже которой заряд батареи считается низким  (код 3Ch)  
  p_data->data_bits.battery_time_as_low_battery_setpoint = 1; 
*/


  // Уставка номинального значения выходного напряжения(код 01h)
  p_data->data_bits.out_v_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_VOLTAGE ); 
    
  // Измеренное значение выходного напряжения для расчета калибровочных коэффициентов(код 02h)
  p_data->data_bits.out_v_mesured_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_OUT_VOLTAGE ); 
    
  // Уставка верхней границы допустимого входного напряжения ИБП(код 29h)
  p_data->data_bits.in_v_hi_level_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_VOLTAGE_HI_THRESHHOLD ); 
    
  // Уставка нижней границы допустимого входного напряжения ИБП(код 2Ah)  
  p_data->data_bits.in_v_low_level_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD ); 
  
  // Уставка номинального значения напряжения промежуточной шины постоянного тока(код 30h)
  p_data->data_bits.middle_v_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MIDDLE_VOLTAGE ); 
    
  // Калибровочный коэффициент выходного напряжения (код 03h)      

  p_data->data_bits.out_v_calibration_factor = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE ); 
    
  // Допустимое отклонение выходного напряжения от номинального значения(код 04h)  
  p_data->data_bits.our_v_deviation_percent_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_DEVIATION_OUT_VOLTAGE );  
    
  // Уставка номинального значения выходного тока(код 05h)
  p_data->data_bits.out_i_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_CURRENT ); 
    
  // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента(код 06h )  
  p_data->data_bits.out_i_mesured_phase_a_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_A ); 
    
  // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента(код 07h)  
  p_data->data_bits.out_i_mesured_phase_b_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_B ); 
    
  // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента(код 08h )  
  p_data->data_bits.out_i_mesured_phase_c_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_C ); 
    
  // Калибровочный коэффициент выходного тока в фазе А (код 09h)  
  p_data->data_bits.out_i_calibration_factor_phase_a = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A ); 
    
  // Калибровочный коэффициент выходного тока в фазе B (код 0Ah)
  p_data->data_bits.out_i_calibration_factor_phase_b = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B ); 
    
  // Калибровочный коэффициент выходного тока в фазе C (код 0Bh)  
  p_data->data_bits.out_i_calibration_factor_phase_c  = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C ); 
    
  // Уставка номинального значения частоты выходного напряжения (код 0Сh)  
  p_data->data_bits.out_frequency_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_FREQUENCY ); 
    
    
  // Допустимое отклонение частоты выходного напряжения от номинального значения (код 0Dh)
  p_data->data_bits.out_freq_dev_percent_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_DEVIATION_OUT_FREQUENCY );  
    
  // Уставка максимального значения cosφ на выходе ИБП (код 0Eh)  
  p_data->data_bits.out_v_max_cos_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_COS_MAX ); 
        
  // Уставка номинального значения выходной мощности (код 0Fh)  
  p_data->data_bits.out_va_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_POWER ); 
    
  // Допустимое время превышения 100% выходной мощности (код 10h)  
  p_data->data_bits.time_exceed_100_percent_out_power = kw_proto_vars_pack_setpoint( SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER ); 
    
  // Допустимое время превышения  первого порога выходной мощности (код 12h)  
  p_data->data_bits.time_exceed_1_level_out_power = kw_proto_vars_pack_setpoint( SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER ); 
    
  // Допустимое время превышения  второго порога выходной мощности (код 14h)  
  p_data->data_bits.time_exceed_2_level_out_power = kw_proto_vars_pack_setpoint( SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER ); 
    
  // Первый порог превышения выходной мощности(код 11h)  
  p_data->data_bits.level_1_percent_out_va_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FIRST_THRESHHOLD_OUT_POWER );  
    
  // Второй порог превышения выходной мощности(код 13h)
  p_data->data_bits.level_2_percent_out_va_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_SECOND_THRESHHOLD_OUT_POWER );
 
  // Уставка максимального пикового выходного тока (код 15h) 
  p_data->data_bits.max_peak_out_i_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_PEAK_CURRENT ); 
    
  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)(код 16h  
  p_data->data_bits.bypass_mode_short_circut_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_OUT_SHORT_CIRCUT_CURRENT );     
    
  // Уставка максимальной температуры охладителя ККМ, (код 17h)  
  p_data->data_bits.max_temp_kkm_cooler_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_COOLER_KKM_MAX_TEMP );  
  
  // Уставка максимальной температуры охладителя инвертора (код 18h )
  p_data->data_bits.max_temp_inverter_cooler_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_COOLER_INVERTER_MAX_TEMP );  
    
  // Уставка максимальной температуры батареи (код 19h )
  p_data->data_bits.max_temp_battery_cooler_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_BATTERY_MAX_TEMP );  
    
  // Уставка максимальной температуры воздуха внутри корпуса ИБП (код 1Ah )
  p_data->data_bits.max_temp_air_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_INBOX_AIR_MAX_TEMP );  
      
  // Уставка минимального допустимого напряжения АКБ (код 1Bh)
  p_data->data_bits.min_v_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_BATTERY_MIN_VOLTAGE ); 
  
  // Уставка максимального допустимого напряжения АКБ (код 1Ch)
  p_data->data_bits.max_v_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_BATTERY_MAX_VOLTAGE ); 
  
  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов(код 1Dh)
  p_data->data_bits.v_battery_mesured_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_VOLTAGE_BATTERY ); 
  
  // Температурный коэффициент АКБ (код 1Eh)
  p_data->data_bits.temp_battery_k_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_TEMP_COEFFICIENT_BATTERY ); 
    
  // Уставка максимального тока разряда АКБ (код 1Fh)
  p_data->data_bits.max_i_discharge_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY ); 
    
  // Уставка максимального тока заряда АКБ (код 20h)
  p_data->data_bits.max_i_charge_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MAX_CHARGE_CURRENT_BATTERY ); 

  // Уставка минимального тока заряда АКБ (код 21h)
  p_data->data_bits.min_i_charge_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MIN_CHARGE_CURRENT_BATTERY ); 
    
  // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов(код 24h)  
  p_data->data_bits.i_charge_battery_mesured_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY ); 
    
  // Уставка напряжения заряда АКБ в  циклическом режиме (код 22h) 
  p_data->data_bits.battery_v_cycle_mode_setpoint	=	 kw_proto_vars_pack_setpoint( SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE );   
    
  // Уставка напряжения заряда АКБ в буферном режиме (код 23h)  
  p_data->data_bits.battery_v_buffer_mode_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE );     
    
  // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов (код 26h)
  p_data->data_bits.battery_v_mesured_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY ); 

  // Калибровочный коэффициент тока заряда АКБ(код 25h)
  p_data->data_bits.fractional_factor_batt_i_charge_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY ); 

  // Калибровочный коэффициент напряжения заряда АКБ(код 27h)
  p_data->data_bits.fractional_factor_batt_u_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY ); 

  // Номинальная ёмкость АКБ (код 28h)    
  p_data->data_bits.nominal_battery_capacity_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_CAPACITY_BATTERY ); 
  
  // Коэффициент несимметрии по входному напряжению (код 2Bh)
  p_data->data_bits.unbalance_factor_in_v_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT );  
    
  // Коэффициент несимметрии по входному току (код 2Dh)
  p_data->data_bits.unbalance_factor_in_i_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT );  
    
  // Уставка максимального значения входного тока ИБП (код 2Сh)  
  p_data->data_bits.in_i_max_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_CURRENT_MAX ); 
    
  // Уставка верхней границы допустимой частоты входного напряжения,  % от номинального значенеия  (код 2Eh)  
  p_data->data_bits.in_frequency_max_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_FREQUENCY_HI_THRESHHOLD );  
    
  // Уставка нижней границы допустимой частоты входного напряжения, % от номинального значенеия  (код 2Fh)  
  p_data->data_bits.in_frequency_min_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD );  

  // Максимальная скорость вентилятора 1(код 31h)  
  p_data->data_bits.max_speed_fun_1_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FUN_1_MAX_SPEED ); 
    
  // Максимальная скорость вентилятора 2(код 32h)
  p_data->data_bits.max_speed_fun_2_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FUN_2_MAX_SPEED ); 
    
  // Максимальная скорость вентилятора резерв 1(код 36h)
  p_data->data_bits.max_speed_fun_res_1_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FUN_RES_1_MAX_SPEED ); 
    
  // Максимальная скорость вентилятора резерв 2 (код 37h)  
  p_data->data_bits.max_speed_fun_res_2_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FUN_RES_2_MAX_SPEED ); 
    
  // Максимальная скорость вентилятора резерв 3 (код 38h)  
  p_data->data_bits.max_speed_fun_res_3_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_FUN_RES_3_MAX_SPEED ); 
    
  // Уставка максимальной температуры резерв 1(код 33h)  
  p_data->data_bits.max_temperature_res_1_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_RES_1_MAX_TEMP );  
    
  // Уставка максимальной температуры резерв 2(код 34h)  
  p_data->data_bits.max_temperature_res_2_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_RES_2_MAX_TEMP );  
    
  // Уставка максимальной температуры резерв 3(код 35h)    
  p_data->data_bits.max_temperature_res_3_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_RES_3_MAX_TEMP );  
    
  // Режим работы ИБП после включения (код 39h)
  p_data->data_bits.operating_mode_after_power_on_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_WORKING_MODE_AFTER_POWER_UP );  
    
  // Режим работы ИБП при аварии (код 3Ah)  
  p_data->data_bits.operating_mode_after_emergency_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT );  
    
  // Синхронизация с входной сетью (код 3Bh)  
  p_data->data_bits.in_power_line_synchronization_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_POWER_LINE_SYNC );  
    
  // Уставка времени работы от батареи, ниже которой заряд батареи считается низким  (код 3Ch)  
  p_data->data_bits.battery_time_as_low_battery_setpoint = kw_proto_vars_pack_setpoint( SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE ); 


  kw_proto_sys_tp_cm_pack_and_send( 0xFF, PGN_PROP_SETPOINTS, buffer, sizeof( prop_setpoints_t ) );
  
  kw_proto_sys_tp_dt_send( 0xFF );
}

void kw_proto_prop_setpoints_unpack( uint8_t *p_setpoints )
{
  prop_setpoints_t *p_data = ( prop_setpoints_t * )p_setpoints;


  // Уставка номинального значения выходного напряжения(код 01h)
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_VOLTAGE, p_data->data_bits.out_v_setpoint );

    
  // Измеренное значение выходного напряжения для расчета калибровочных коэффициентов(код 02h)
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_OUT_VOLTAGE, p_data->data_bits.out_v_mesured_setpoint );
    
  // Уставка верхней границы допустимого входного напряжения ИБП(код 29h)
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_VOLTAGE_HI_THRESHHOLD, p_data->data_bits.in_v_hi_level_setpoint );
    
  // Уставка нижней границы допустимого входного напряжения ИБП(код 2Ah)  
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD, p_data->data_bits.in_v_low_level_setpoint );
  
  // Уставка номинального значения напряжения промежуточной шины постоянного тока(код 30h)
  kw_proto_vars_unpack_setpoint( SETPOINT_MIDDLE_VOLTAGE, p_data->data_bits.middle_v_setpoint );
    
  // Калибровочный коэффициент выходного напряжения (код 03h)      
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE, p_data->data_bits.out_v_calibration_factor );
    
  // Допустимое отклонение выходного напряжения от номинального значения(код 04h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_DEVIATION_OUT_VOLTAGE, p_data->data_bits.our_v_deviation_percent_setpoint );
    
  // Уставка номинального значения выходного тока(код 05h)
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_CURRENT, p_data->data_bits.out_i_setpoint );
    
  // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента(код 06h )  
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_A, p_data->data_bits.out_i_mesured_phase_a_setpoint );
    
  // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента(код 07h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_B, p_data->data_bits.out_i_mesured_phase_b_setpoint );
    
  // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента(код 08h )  
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_OUT_CURRENT_PHASE_C, p_data->data_bits.out_i_mesured_phase_c_setpoint );
    
  // Калибровочный коэффициент выходного тока в фазе А (код 09h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A, p_data->data_bits.out_i_calibration_factor_phase_a );
    
  // Калибровочный коэффициент выходного тока в фазе B (код 0Ah)
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B, p_data->data_bits.out_i_calibration_factor_phase_b );
    
  // Калибровочный коэффициент выходного тока в фазе C (код 0Bh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C, p_data->data_bits.out_i_calibration_factor_phase_c );
    
  // Уставка номинального значения частоты выходного напряжения (код 0Сh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_FREQUENCY, p_data->data_bits.out_frequency_setpoint );
        
  // Допустимое отклонение частоты выходного напряжения от номинального значения (код 0Dh)
  kw_proto_vars_unpack_setpoint( SETPOINT_DEVIATION_OUT_FREQUENCY, p_data->data_bits.out_freq_dev_percent_setpoint );
    
  // Уставка максимального значения cosφ на выходе ИБП (код 0Eh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_COS_MAX, p_data->data_bits.out_v_max_cos_setpoint );
        
  // Уставка номинального значения выходной мощности (код 0Fh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_POWER, p_data->data_bits.out_va_setpoint );
    
  // Допустимое время превышения 100% выходной мощности (код 10h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER, p_data->data_bits.time_exceed_100_percent_out_power );
    
  // Допустимое время превышения  первого порога выходной мощности (код 12h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER, p_data->data_bits.time_exceed_1_level_out_power );
    
  // Допустимое время превышения  второго порога выходной мощности (код 14h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER, p_data->data_bits.time_exceed_2_level_out_power );
    
  // Первый порог превышения выходной мощности(код 11h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_FIRST_THRESHHOLD_OUT_POWER, p_data->data_bits.level_1_percent_out_va_setpoint );
    
  // Второй порог превышения выходной мощности(код 13h)
  kw_proto_vars_unpack_setpoint( SETPOINT_SECOND_THRESHHOLD_OUT_POWER, p_data->data_bits.level_2_percent_out_va_setpoint );
 
  // Уставка максимального пикового выходного тока (код 15h) 
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_PEAK_CURRENT, p_data->data_bits.max_peak_out_i_setpoint );
    
  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)(код 16h  
  kw_proto_vars_unpack_setpoint( SETPOINT_OUT_SHORT_CIRCUT_CURRENT, p_data->data_bits.bypass_mode_short_circut_setpoint );
    
  // Уставка максимальной температуры охладителя ККМ, (код 17h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_COOLER_KKM_MAX_TEMP, p_data->data_bits.max_temp_kkm_cooler_setpoint );
  
  // Уставка максимальной температуры охладителя инвертора (код 18h )
  kw_proto_vars_unpack_setpoint( SETPOINT_COOLER_INVERTER_MAX_TEMP, p_data->data_bits.max_temp_inverter_cooler_setpoint );
    
  // Уставка максимальной температуры батареи (код 19h )
  kw_proto_vars_unpack_setpoint( SETPOINT_BATTERY_MAX_TEMP, p_data->data_bits.max_temp_battery_cooler_setpoint );
    
  // Уставка максимальной температуры воздуха внутри корпуса ИБП (код 1Ah )
  kw_proto_vars_unpack_setpoint( SETPOINT_INBOX_AIR_MAX_TEMP, p_data->data_bits.max_temp_air_setpoint );
      
  // Уставка минимального допустимого напряжения АКБ (код 1Bh)
  kw_proto_vars_unpack_setpoint( SETPOINT_BATTERY_MIN_VOLTAGE, p_data->data_bits.min_v_battery_setpoint );
  
  // Уставка максимального допустимого напряжения АКБ (код 1Ch)
  kw_proto_vars_unpack_setpoint( SETPOINT_BATTERY_MAX_VOLTAGE, p_data->data_bits.max_v_battery_setpoint );
  
  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов(код 1Dh)
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_VOLTAGE_BATTERY, p_data->data_bits.v_battery_mesured_setpoint );
  
  // Температурный коэффициент АКБ (код 1Eh)
  kw_proto_vars_unpack_setpoint( SETPOINT_TEMP_COEFFICIENT_BATTERY, p_data->data_bits.temp_battery_k_setpoint );
    
  // Уставка максимального тока разряда АКБ (код 1Fh)
  kw_proto_vars_unpack_setpoint( SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY, p_data->data_bits.max_i_discharge_battery_setpoint );
    
  // Уставка максимального тока заряда АКБ (код 20h)
  kw_proto_vars_unpack_setpoint( SETPOINT_MAX_CHARGE_CURRENT_BATTERY, p_data->data_bits.max_i_charge_battery_setpoint );

  // Уставка минимального тока заряда АКБ (код 21h)
  kw_proto_vars_unpack_setpoint( SETPOINT_MIN_CHARGE_CURRENT_BATTERY, p_data->data_bits.min_i_charge_battery_setpoint );
    
  // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов(код 24h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY, p_data->data_bits.i_charge_battery_mesured_setpoint );
    
  // Уставка напряжения заряда АКБ в  циклическом режиме (код 22h) 
  kw_proto_vars_unpack_setpoint( SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE, p_data->data_bits.battery_v_cycle_mode_setpoint );
    
  // Уставка напряжения заряда АКБ в буферном режиме (код 23h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE, p_data->data_bits.battery_v_buffer_mode_setpoint );
    
  // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов (код 26h)
  kw_proto_vars_unpack_setpoint( SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY, p_data->data_bits.battery_v_mesured_setpoint );

  // Калибровочный коэффициент тока заряда АКБ(код 25h)
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY, p_data->data_bits.fractional_factor_batt_i_charge_setpoint );

  // Калибровочный коэффициент напряжения заряда АКБ(код 27h)
  kw_proto_vars_unpack_setpoint( SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY, p_data->data_bits.fractional_factor_batt_u_setpoint );

  // Номинальная ёмкость АКБ (код 28h)    
  kw_proto_vars_unpack_setpoint( SETPOINT_CAPACITY_BATTERY, p_data->data_bits.nominal_battery_capacity_setpoint );
  
  // Коэффициент несимметрии по входному напряжению (код 2Bh)
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT, p_data->data_bits.unbalance_factor_in_v_setpoint );
    
  // Коэффициент несимметрии по входному току (код 2Dh)
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT, p_data->data_bits.unbalance_factor_in_i_setpoint );
    
  // Уставка максимального значения входного тока ИБП (код 2Сh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_CURRENT_MAX, p_data->data_bits.in_i_max_setpoint );
    
  // Уставка верхней границы допустимой частоты входного напряжения,  % от номинального значенеия  (код 2Eh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_FREQUENCY_HI_THRESHHOLD, p_data->data_bits.in_frequency_max_setpoint );
    
  // Уставка нижней границы допустимой частоты входного напряжения, % от номинального значенеия  (код 2Fh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD, p_data->data_bits.in_frequency_min_setpoint );

  // Максимальная скорость вентилятора 1(код 31h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_FUN_1_MAX_SPEED, p_data->data_bits.max_speed_fun_1_setpoint );
    
  // Максимальная скорость вентилятора 2(код 32h)
  kw_proto_vars_unpack_setpoint( SETPOINT_FUN_2_MAX_SPEED, p_data->data_bits.max_speed_fun_2_setpoint );
    
  // Максимальная скорость вентилятора резерв 1(код 36h)
  kw_proto_vars_unpack_setpoint( SETPOINT_FUN_RES_1_MAX_SPEED, p_data->data_bits.max_speed_fun_res_1_setpoint );
    
  // Максимальная скорость вентилятора резерв 2 (код 37h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_FUN_RES_2_MAX_SPEED, p_data->data_bits.max_speed_fun_res_2_setpoint );
    
  // Максимальная скорость вентилятора резерв 3 (код 38h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_FUN_RES_3_MAX_SPEED, p_data->data_bits.max_speed_fun_res_3_setpoint );
    
  // Уставка максимальной температуры резерв 1(код 33h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_RES_1_MAX_TEMP, p_data->data_bits.max_temperature_res_1_setpoint );
    
  // Уставка максимальной температуры резерв 2(код 34h)  
  kw_proto_vars_unpack_setpoint( SETPOINT_RES_2_MAX_TEMP, p_data->data_bits.max_temperature_res_2_setpoint );
    
  // Уставка максимальной температуры резерв 3(код 35h)    
  kw_proto_vars_unpack_setpoint( SETPOINT_RES_3_MAX_TEMP, p_data->data_bits.max_temperature_res_3_setpoint );
    
  // Режим работы ИБП после включения (код 39h)
  kw_proto_vars_unpack_setpoint( SETPOINT_WORKING_MODE_AFTER_POWER_UP, p_data->data_bits.operating_mode_after_power_on_setpoint );
    
  // Режим работы ИБП при аварии (код 3Ah)  
  kw_proto_vars_unpack_setpoint( SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT, p_data->data_bits.operating_mode_after_emergency_setpoint );
    
  // Синхронизация с входной сетью (код 3Bh)  
  kw_proto_vars_unpack_setpoint( SETPOINT_POWER_LINE_SYNC, p_data->data_bits.in_power_line_synchronization_setpoint );
    
  // Уставка времени работы от батареи, ниже которой заряд батареи считается низким  (код 3Ch)  
  kw_proto_vars_unpack_setpoint( SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE, p_data->data_bits.battery_time_as_low_battery_setpoint );
  
}

void kw_proto_prop_id_card_pack_and_send( void )
{
  uint8_t buffer[ 64 ];
  uint32_t len;
  
  len = p_vars->vars_get_array( ARRAY_ID_CARD, buffer, sizeof( buffer ) );
  
  if( len > 0 )
  {
    kw_proto_sys_tp_cm_pack_and_send( 0xFF, PGN_PROP_ID_CARD, buffer, len );
  
    kw_proto_sys_tp_dt_send( 0xFF );        
  }  
}


int32_t kw_proto_setpoint_unpack( kw_can_msg_t *p_msg )
{
  ENUM_SETPOINT_NAME setpoint_name = ( ENUM_SETPOINT_NAME )p_msg->data[ 1 ];
  
  uint32_t packed_value;

  packed_value = p_msg->data[ 3 ];
  packed_value <<= 8;
  packed_value |= p_msg->data[ 2 ];
  
  return kw_proto_vars_unpack_setpoint( setpoint_name, packed_value );
}


void kw_proto_setpoint_pack_and_send( ENUM_SETPOINT_NAME setpoint_name )
{
  kw_can_msg_t msg;
  proto_id_t *p_id;

  uint32_t packed_value = kw_proto_vars_pack_setpoint( setpoint_name );

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = POWER_MODULE_ADDR;


  msg.data[ 0 ] = ( uint8_t )SPC_CMD_WRITE_SETPOINT;
  msg.data[ 1 ] = ( uint8_t )setpoint_name;

  msg.data[ 2 ] = ( uint8_t )( packed_value & 0xFF );
  msg.data[ 3 ] = ( uint8_t )( ( packed_value >> 8 ) & 0xFF );

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}


void kw_proto_kip6_wr_ip_addr_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  proto_id_t *p_id;

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  msg.data[ 0 ] = ( uint8_t )SPC_CMD_WRITE_IP_ADR;

  // не делаем проверок 
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_ADR, &val );

  msg.data[ 1 ] = val.val_byte[0];
  msg.data[ 2 ] = val.val_byte[1];
  msg.data[ 3 ] = val.val_byte[2];
  msg.data[ 4 ] = val.val_byte[3];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}


static void kw_proto_kip6_ip_unpack( kw_can_msg_t *p_msg, ENUM_SETPOINT_NAME ip_setpoint_name)
{
  value_pack_t val;

  // не делаем проверок 
  val.val_byte[0] = p_msg->data[ 1 ];
  val.val_byte[1] = p_msg->data[ 2 ];
  val.val_byte[2] = p_msg->data[ 3 ];
  val.val_byte[3] = p_msg->data[ 4 ];

  p_vars->vars_set_setpoint( ip_setpoint_name, val );      
}

void kw_proto_kip6_wr_ip_addr_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  
  kw_proto_kip6_ip_unpack( p_msg, SETPOINT_KIP6_IP_ADR );
}



void kw_proto_kip6_wr_net_mask_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  proto_id_t *p_id;

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  msg.data[ 0 ] = ( uint8_t )SPC_CMD_WRITE_IP_MASK;

  // не делаем проверок 
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_MASK, &val );

  msg.data[ 1 ] = val.val_byte[0];
  msg.data[ 2 ] = val.val_byte[1];
  msg.data[ 3 ] = val.val_byte[2];
  msg.data[ 4 ] = val.val_byte[3];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );     
}

void kw_proto_kip6_wr_net_mask_unpack(  kw_can_msg_t *p_msg )
{
  kw_proto_kip6_ip_unpack( p_msg, SETPOINT_KIP6_IP_MASK );
}


void kw_proto_kip6_wr_gate_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  proto_id_t *p_id;

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  msg.data[ 0 ] = ( uint8_t )SPC_CMD_WRITE_IP_GATE;

  // не делаем проверок 
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_GATE, &val );

  msg.data[ 1 ] = val.val_byte[0];
  msg.data[ 2 ] = val.val_byte[1];
  msg.data[ 3 ] = val.val_byte[2];
  msg.data[ 4 ] = val.val_byte[3];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );       
}

void kw_proto_kip6_wr_gate_unpack( kw_can_msg_t *p_msg )
{
  kw_proto_kip6_ip_unpack( p_msg, SETPOINT_KIP6_IP_GATE );  
}



void kw_proto_kip6_wr_ip_adressing_type_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  proto_id_t *p_id;
  

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  msg.data[ 0 ] = ( uint8_t )SPC_CMD_WRITE_IP_TYPE;

  // не делаем проверок 
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_TYPE, &val );

  msg.data[ 1 ] &= 0xFE;
  msg.data[ 1 ] |= val.val_byte[0];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );         
}

void kw_proto_kip6_wr_ip_adressing_type_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;

  val.val_int = 0;
  
  val.val_byte[0] = p_msg->data[ 1 ] & 0x01;
  
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IP_TYPE, val );  
}

void kw_proto_kip6_wr_mb_settings_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  prop_spc_cmd_mb_settings_t *p_data;
  proto_id_t *p_id;


  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  p_data = ( prop_spc_cmd_mb_settings_t * )&msg.data[ 0 ];

  p_data->data_bits.cmd_code =  ( uint8_t )SPC_CMD_WRITE_MB_SETTINGS;
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_MB_ADR, &val );
  p_data->data_bits.mb_adr = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_MB_BAUD, &val );
  p_data->data_bits.mb_baudrate = val.val_byte[0];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );           
}

void kw_proto_kip6_wr_mb_settings_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_spc_cmd_mb_settings_t *p_data;


  p_data = ( prop_spc_cmd_mb_settings_t * )&p_msg->data[ 0 ];

  val.val_byte[0] = p_data->data_bits.mb_adr;  
  p_vars->vars_set_setpoint( SETPOINT_KIP6_MB_ADR, val );

  val.val_byte[0] = p_data->data_bits.mb_baudrate;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_MB_BAUD, val );

}




void kw_proto_kip6_wr_dry_settings_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  prop_spc_cmd_dry_settings_t *p_data;
  proto_id_t *p_id;

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;

  p_data = ( prop_spc_cmd_dry_settings_t * )&msg.data[ 0 ];

  p_data->data_bits.cmd_code =  ( uint8_t )SPC_CMD_WRITE_DRY_CONTACTS_SETTINGS;
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_1_FUNCTION, &val );
  p_data->data_bits.dry_in_1 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_2_FUNCTION, &val );
  p_data->data_bits.dry_in_2 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_3_FUNCTION, &val );
  p_data->data_bits.dry_in_3 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_4_FUNCTION, &val );
  p_data->data_bits.dry_in_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_5_FUNCTION, &val );
  p_data->data_bits.dry_in_5 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_1_FUNCTION, &val );
  p_data->data_bits.dry_out_1 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_2_FUNCTION, &val );
  p_data->data_bits.dry_out_2 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_3_FUNCTION, &val );
  p_data->data_bits.dry_out_3 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_4_FUNCTION, &val );
  p_data->data_bits.dry_out_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_5_FUNCTION, &val );
  p_data->data_bits.dry_out_5 = val.val_byte[0];
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW, &val );
  p_data->data_bits.bat_percent_as_low = val.val_byte[0];  
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );            
}


void kw_proto_kip6_wr_dry_settings_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_spc_cmd_dry_settings_t *p_data = ( prop_spc_cmd_dry_settings_t * )&p_msg->data[ 0 ];

  p_data->data_bits.dry_in_1 = val.val_byte[0];  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_1_FUNCTION, &val );

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_2_FUNCTION, &val );
  p_data->data_bits.dry_in_2 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_3_FUNCTION, &val );
  p_data->data_bits.dry_in_3 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_4_FUNCTION, &val );
  p_data->data_bits.dry_in_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_5_FUNCTION, &val );
  p_data->data_bits.dry_in_5 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_1_FUNCTION, &val );
  p_data->data_bits.dry_out_1 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_2_FUNCTION, &val );
  p_data->data_bits.dry_out_2 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_3_FUNCTION, &val );
  p_data->data_bits.dry_out_3 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_4_FUNCTION, &val );
  p_data->data_bits.dry_out_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_5_FUNCTION, &val );
  p_data->data_bits.dry_out_5 = val.val_byte[0];
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW, &val );
  p_data->data_bits.bat_percent_as_low = val.val_byte[0];  

}



void kw_proto_kip6_set_date_time_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;
  prop_date_time_t *p_data;
  proto_id_t *p_id;

  prop_dt_t date_time; 

	p_vars->vars_get_date_time( &date_time );

  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 ); // заголовок	

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = KIP6_MODULE_ADDR;


  msg.data[ 0 ] = SPC_CMD_SET_DATE_TIME;

  p_data = ( prop_date_time_t *)&msg.data[ 1 ];

  p_data->data_bits.seconds = date_time.sec;
  p_data->data_bits.minutes = date_time.min;
  p_data->data_bits.hours = date_time.hour;
  p_data->data_bits.month = date_time.mon;
  p_data->data_bits.dom = date_time.mday;
  p_data->data_bits.years = date_time.year;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );            
}

int32_t kw_proto_kip6_set_date_time_unpack( kw_can_msg_t *p_msg )
{
  return 0;
}



int32_t kw_proto_password_unpack( kw_can_msg_t *p_msg )
{
  if( p_msg->data[ 1 ] == 'K' &&
      p_msg->data[ 2 ] == 'V' &&
      p_msg->data[ 3 ] == 'S' )
  {
    return 0;
  }

  return -1;
}

int32_t kw_proto_write_id_card_unpack( kw_can_msg_t *p_msg )
{
  static uint8_t id_card_buffer[ 35 ];

  uint32_t buf_pos = ( p_msg->data[ 0 ] - ( uint8_t )SPC_CMD_WRITE_ID_CARD_1 ) * 7;
  
  memcpy( &id_card_buffer[ buf_pos ], &p_msg->data[ 1 ], 7 );
  
  
  if( p_msg->data[ 0 ] == ( uint8_t )SPC_CMD_WRITE_ID_CARD_5 )
  {
    return p_vars->vars_set_array( ARRAY_ID_CARD, id_card_buffer, sizeof( id_card_buffer ) );
    
  }
  return 0;
}


void kw_proto_prop_test_result_str_pack_and_send( void )
{
  uint8_t buffer[ 255 ];
  uint32_t len;
  
  len = p_vars->vars_get_array( ARRAY_TEST_RESULT_STR, buffer, sizeof( buffer ) );
  
  if( len > 0 )
  {
    kw_proto_sys_tp_cm_pack_and_send( 0xFF, PGN_PROP_TEST_RESULT_DETAIL, buffer, len );
  
    kw_proto_sys_tp_dt_send( 0xFF );        
  }  
  
}


void kw_proto_inverter_voltage_pack_and_send( void )
{
  kw_can_msg_t msg;
  uint32_t tmp;
	value_pack_t val;


  kw_proto_prepare_msg( &msg, PGN_PROP_INVERTER_VOLTAGE, 6 ); // заголовок	

  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&msg.data[ 0 ];
	
	p_vars->vars_get_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_a = tmp;
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
	p_vars->vars_get_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_b = tmp;
  
	p_vars->vars_get_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_A, &val );
	tmp = ( uint32_t )( round( val.val_float / 0.5F ) );
	p_data->data_bits.v_rms_phase_c = tmp;
#endif  
	
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );
}

void kw_proto_inverter_voltage_unpack( kw_can_msg_t *p_msg )
{
  prop_out_voltage_t *p_data = ( prop_out_voltage_t *)&p_msg->data[ 0 ];
	
  kw_proto_vars_unpack_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_A, p_data->data_bits.v_rms_phase_a  );
  
#if ( KW_PROTO_PHASE_NUMBERS > 1 )
  kw_proto_vars_unpack_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_B, p_data->data_bits.v_rms_phase_b  );
  kw_proto_vars_unpack_value( VALUE_INVERTER_VOLTAGE_RMS_PHASE_C, p_data->data_bits.v_rms_phase_c  );
#endif    
}



void kw_proto_date_time_pack_and_send( void )
{
  kw_can_msg_t msg;
  prop_dt_t date_time; 

	p_vars->vars_get_date_time( &date_time );

  kw_proto_prepare_msg( &msg, PGN_TD, 6 ); // заголовок	

  prop_date_time_t *p_data = ( prop_date_time_t *)&msg.data[ 0 ];

  p_data->data_bits.seconds = date_time.sec;
  p_data->data_bits.minutes = date_time.min;
  p_data->data_bits.hours = date_time.hour;
  p_data->data_bits.month = date_time.mon;
  p_data->data_bits.dom = date_time.mday;
  p_data->data_bits.years = date_time.year;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_date_time_unpack( kw_can_msg_t *p_msg )
{
  prop_dt_t date_time; 

  prop_date_time_t *p_data = ( prop_date_time_t *)&p_msg->data[ 0 ];

  date_time.sec = p_data->data_bits.seconds;
  date_time.min = p_data->data_bits.minutes;
  date_time.hour = p_data->data_bits.hours;
  date_time.mon = p_data->data_bits.month;
  date_time.mday = p_data->data_bits.dom;
  date_time.year = p_data->data_bits.years;

	p_vars->vars_set_date_time( &date_time ); 
}

// FF70
void kw_proto_kip6_prop_rd_ip_mask_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_IP_ADDR_MASK, 6 ); // заголовок	

  prop_ip_mask_t *p_data = ( prop_ip_mask_t *)&msg.data[ 0 ];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_ADR, &val );
  p_data->data_bits.ip_adr = val.val_int;

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_MASK, &val );
  p_data->data_bits.net_mask = val.val_int;

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}

// FF70
void kw_proto_kip6_prop_rd_ip_mask_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_ip_mask_t *p_data = ( prop_ip_mask_t *)&p_msg->data[ 0 ];

  val.val_int = p_data->data_bits.ip_adr;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IP_ADR, val ); 

  val.val_int = p_data->data_bits.net_mask;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IP_MASK, val ); 
  
}
// FF71
void kw_proto_kip6_prop_rd_gate_type_pack_and_send( void )
{
  kw_can_msg_t msg;
  value_pack_t val;

  kw_proto_prepare_msg( &msg, PGN_PROP_IP_GATE_TYPE, 6 ); // заголовок	

  prop_gate_type_t *p_data = ( prop_gate_type_t *)&msg.data[ 0 ];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_GATE, &val );
  p_data->data_bits.gate_adr = val.val_int;

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IP_TYPE, &val );
  p_data->data_bits.ip_adr_type = val.val_byte[0];

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

// FF71
void kw_proto_kip6_prop_rd_gate_type_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_gate_type_t *p_data = ( prop_gate_type_t *)&p_msg->data[ 0 ];

  val.val_int = p_data->data_bits.gate_adr;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IP_GATE, val ); 

  val.val_byte[0] = p_data->data_bits.ip_adr_type;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IP_TYPE, val ); 
  
}

// FF72
void kw_proto_kip6_prop_rd_mb_settings_pack_and_send( void )
{
  value_pack_t val;
  kw_can_msg_t msg;

  kw_proto_prepare_msg( &msg, PGN_PROP_MB_SETTINGS, 6 ); // заголовок	

  prop_mb_settings_t *p_data = ( prop_mb_settings_t *)&msg.data[ 0 ];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_MB_ADR, &val );
  p_data->data_bits.mb_adr = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_MB_BAUD, &val );
  p_data->data_bits.mb_baud = val.val_byte[0];

	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

// FF72
void kw_proto_kip6_prop_rd_mb_settings_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_mb_settings_t *p_data = ( prop_mb_settings_t *)&p_msg->data[ 0 ];

  val.val_byte[0] = p_data->data_bits.mb_adr;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_MB_ADR, val ); 

  val.val_byte[0] = p_data->data_bits.mb_baud;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_MB_BAUD, val );   
  
}

void kw_proto_kip6_prop_rd_dry_conacts_settings_pack_and_send( void )
{
  value_pack_t val;
  kw_can_msg_t msg;

  kw_proto_prepare_msg( &msg, PGN_PROP_DRY_SETTINGS, 6 ); // заголовок	

  prop_dry_settings_t *p_data = ( prop_dry_settings_t *)&msg.data[ 0 ];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_1_FUNCTION, &val ); 
  p_data->data_bits.dry_in_1 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_2_FUNCTION, &val ); 
  p_data->data_bits.dry_in_2 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_3_FUNCTION, &val ); 
  p_data->data_bits.dry_in_3 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_4_FUNCTION, &val ); 
  p_data->data_bits.dry_in_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_IN_5_FUNCTION, &val ); 
  p_data->data_bits.dry_in_5 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_1_FUNCTION, &val ); 
  p_data->data_bits.dry_out_1 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_2_FUNCTION, &val ); 
  p_data->data_bits.dry_out_2 = val.val_byte[0];
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_3_FUNCTION, &val ); 
  p_data->data_bits.dry_out_3 = val.val_byte[0];
  
  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_4_FUNCTION, &val ); 
  p_data->data_bits.dry_out_4 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_OUT_5_FUNCTION, &val ); 
  p_data->data_bits.dry_out_5 = val.val_byte[0];

  p_vars->vars_get_setpoint( SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW, &val ); 
  p_data->data_bits.bat_percent_as_low = val.val_byte[0];
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}




// FF73
void kw_proto_kip6_prop_rd_dry_conacts_settings_unpack( kw_can_msg_t *p_msg )
{
  value_pack_t val;
  prop_dry_settings_t *p_data = ( prop_dry_settings_t *)&p_msg->data[ 0 ];

  val.val_byte[0] = p_data->data_bits.dry_in_1;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IN_1_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_in_2;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IN_2_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_in_3;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IN_3_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_in_4;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IN_4_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_in_5;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_IN_5_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_out_1;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_OUT_1_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_out_2;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_OUT_2_FUNCTION, val ); 
  
  val.val_byte[0] = p_data->data_bits.dry_out_3;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_OUT_3_FUNCTION, val ); 
  
  val.val_byte[0] = p_data->data_bits.dry_out_4;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_OUT_4_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.dry_out_5;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_OUT_5_FUNCTION, val ); 

  val.val_byte[0] = p_data->data_bits.bat_percent_as_low;
  p_vars->vars_set_setpoint( SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW, val ); 
}

void kw_proto_switch_to_mode_pack_and_send( UPS_MODE_ENUM mode )
{
  kw_can_msg_t msg;
  proto_id_t *p_id;

  if( mode >= UPS_MODE_MAX )
    return;
  
  kw_proto_prepare_msg( &msg, PGN_PROP_SPC_CMD, 6 );

	p_id = ( proto_id_t *)&msg.id;  
  p_id->addr_id.DA = POWER_MODULE_ADDR;

  msg.data[0] = SPC_CMD_SWITCH_TO_MODE;
  msg.data[1] = mode;
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}











