/**
 *
 *	\file		kw_proto_vars.h
 *	\brief	Модуль для работы c переменными протокола на CAN шине
 *
 *
 */

#ifndef __KW_PROTO_STRUCTS_H
#define __KW_PROTO_STRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_vars.h"


typedef union
{
  volatile uint32_t id;
  struct 
  {
    volatile uint32_t SA        : 8;
    volatile uint32_t PGN       : 16;
    volatile uint32_t DP        : 1;
    volatile uint32_t EDP       : 1;
    volatile uint32_t priority  : 3;
    volatile uint32_t reserved  : 3;
  }__attribute__((packed)) broadcast_id;
  struct 
  {
    volatile uint32_t SA        : 8;
    volatile uint32_t DA        : 8;
    volatile uint32_t PDF       : 8;    
    volatile uint32_t DP        : 1;
    volatile uint32_t EDP       : 1;
    volatile uint32_t priority  : 3;
    volatile uint32_t reserved  : 3;
  }__attribute__((packed)) addr_id;  
}proto_id_t;


// E800
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t control_word          : 8; 
    volatile uint32_t group_func            : 8; 
    volatile uint32_t reserved              : 16;
    volatile uint32_t requester_addr        : 8;     
    volatile uint32_t pgn                   : 24;
  }__attribute__((packed)) data_bits;
}sys_ack_t;

// EA00
typedef union
{
  volatile uint8_t data[ 3 ];
  struct
  {
    volatile uint32_t pgn                   : 24;
  }__attribute__((packed)) data_bits;
}sys_request_t;


// EB00
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t pkg_number            : 8; 
  }__attribute__((packed)) data_bits;
}sys_tp_dt_t;

// EC00
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t control_word          : 8; 
    volatile uint32_t msg_total_len         : 16; 
    volatile uint32_t pkg_numbers           : 8;
    volatile uint32_t reserved              : 8;
    volatile uint32_t pgn                   : 24;
  }__attribute__((packed)) data_bits;
}sys_tp_cm_t;

// FEE6
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t res_1                 : 2; 
    volatile uint32_t seconds               : 6; 
    volatile uint32_t minutes               : 8; 
    volatile uint32_t hours                 : 8; 
    volatile uint32_t month                 : 8; 
    volatile uint32_t res_3                 : 2; 
    volatile uint32_t dom                   : 6; 
    volatile uint32_t years                 : 8;
    volatile uint32_t res_4                 : 16; 
  }__attribute__((packed)) data_bits;
}prop_date_time_t;




// FF01, FF04, FF07
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t v_rms_phase_a					: 10; 
    volatile uint32_t v_rms_phase_b        	: 10; 
    volatile uint32_t v_rms_phase_c       	: 10;
    volatile uint32_t phase_shift_a        	: 9; 
    volatile uint32_t phase_shift_b        	: 9; 
    volatile uint32_t phase_shift_c        	: 9; 
    volatile uint32_t pm_working_mode      	: 4; 
    volatile uint32_t on_off_btn_status    	: 1; 
    volatile uint32_t reserved             	: 2; 
  }__attribute__((packed)) data_bits;

}prop_in_voltage_t;

// FF02, FF05, FF08, 
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t i_rms_phase_a					: 14; 
    volatile uint32_t i_rms_phase_b        	: 14; 
    volatile uint32_t i_rms_phase_c       	: 14;
    volatile uint32_t in_power       	      : 16;    
    volatile uint32_t reserved             	: 6; 
  }__attribute__((packed)) data_bits;
}prop_in_current_t;

// FF03, FF06, FF09 
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t freq_phase_a					: 14; 
    volatile uint32_t freq_phase_b        	: 14; 
    volatile uint32_t freq_phase_c       	  : 14;
    volatile uint32_t reserved             	: 22; 
  }__attribute__((packed)) data_bits;
}prop_in_frequency_t;

// FF0F
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t bad_states_count			: 32; 
    volatile uint32_t in_lines_number       : 2; 
    volatile uint32_t reserved             	: 30; 
  }__attribute__((packed)) data_bits;
}prop_in_status_t;


// FF11, FF13, FF15 + FF21, FF23, FF25
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t v_rms_phase_a					: 10; 
    volatile uint32_t v_rms_phase_b        	: 10; 
    volatile uint32_t v_rms_phase_c       	: 10;
    volatile uint32_t reserved1             : 2;     
    volatile uint32_t out_power        	    : 16; 
    volatile uint32_t out_percent        	  : 8; 
    volatile uint32_t reserved2             : 8; 
  }__attribute__((packed)) data_bits;

}prop_out_voltage_t;

// FF12, FF14, FF16 + FF22, FF24, FF26 + FF32
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t i_rms_phase_a					: 14; 
    volatile uint32_t i_rms_phase_b        	: 14; 
    volatile uint32_t i_rms_phase_c       	: 14;
    volatile uint32_t reserved             	: 22; 
  }__attribute__((packed)) data_bits;
}prop_out_current_t;

// FF1E
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t freq_phase_a					: 14; 
    volatile uint32_t freq_phase_b        	: 14; 
    volatile uint32_t freq_phase_c       	  : 14;
    volatile uint32_t out_power_source      : 3;
    volatile uint32_t out_lines_number      : 2;
    volatile uint32_t test_result           : 3;
    volatile uint32_t reserved             	: 14; 
  }__attribute__((packed)) data_bits;
}prop_out_frequency_t;

// FF2E
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t freq_phase_a					: 14; 
    volatile uint32_t freq_phase_b        	: 14; 
    volatile uint32_t freq_phase_c       	  : 14;
    volatile uint32_t bypass_lines_number      : 2;
  }__attribute__((packed)) data_bits;
}prop_bypass_frequency_t;



// FF1F + FF2F
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t phase_shift_phase_a   : 9; 
    volatile uint32_t phase_shift_phase_b   : 9; 
    volatile uint32_t phase_shift_phase_c   : 9; 
//    volatile uint32_t reserved             	: 37; 
  }__attribute__((packed)) data_bits;
}prop_out_phase_shift_t;


// FF31
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t v_positive					              : 10; 
    volatile uint32_t v_negative        	              : 10;
    volatile uint32_t reserved1                         : 4;
    volatile uint32_t phase_shift_out_current_phase_a   : 9;
    volatile uint32_t phase_shift_out_current_phase_b   : 9;
    volatile uint32_t phase_shift_out_current_phase_c   : 9;
    volatile uint32_t reserved2                         : 5;
  }__attribute__((packed)) data_bits;
}prop_middle_voltage_t;


// FF33
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t v_battery					                : 15;
    volatile uint32_t reserved11					              : 1;
    volatile uint32_t i_battery					                : 15;
    volatile uint32_t reserved12					              : 1;
    volatile uint32_t v_charger					                : 15;
    volatile uint32_t reserved13					              : 1;
    volatile uint32_t i_charger					                : 15;
    volatile uint32_t reserved14					              : 1;
  }__attribute__((packed)) data_bits;
}prop_battery_voltage_t;



// FF34
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t charge_percent					          : 7;
    volatile uint32_t remaining_time					          : 17;
    volatile uint32_t working_time					            : 16;
    volatile uint32_t battery_status					          : 3;
    volatile uint32_t reserved13					              : 21;
  }__attribute__((packed)) data_bits;
}prop_battery_status_t;

// FF35
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t KKM_cooler_temp					          : 8;
    volatile uint32_t into_box_air_temp					        : 8;
    volatile uint32_t battery_temp					            : 8;
    volatile uint32_t inverter_temp					            : 8;
    volatile uint32_t res1_temp					                : 8;
    volatile uint32_t res2_temp					                : 8;
    volatile uint32_t res3_temp					                : 8;
    volatile uint32_t reserved					                : 8;
  }__attribute__((packed)) data_bits;
}prop_modules_temperature_t;

// FF36
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t fun_1_speed					              : 15;
    volatile uint32_t reserved_1					              : 1;
    volatile uint32_t fun_2_speed					              : 15;
    volatile uint32_t reserved_2					              : 1;
    volatile uint32_t fun_res_1_speed					          : 15;
    volatile uint32_t reserved_3					              : 1;
    volatile uint32_t fun_res_2_speed					          : 15;
    volatile uint32_t reserved_4					              : 1;
  }__attribute__((packed)) data_bits;
}prop_fun_speed_t;

// FF37
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t fun_res_3_speed					          : 15;
    volatile uint32_t reserved_1					              : 1;
    volatile uint32_t fun_1_speed					              : 15;
    volatile uint32_t reserved_2					              : 1;
//    volatile uint32_t reserved					                : 48;
  } __attribute__((packed)) data_bits;
}prop_fun_speed_2_t;


// FF40

typedef union
{
  volatile uint8_t data[ 84 ];
  struct
  {
    volatile uint32_t out_v_setpoint					                  : 10; // Уставка номинального значения выходного напряжения(код 01h)
    volatile uint32_t out_v_mesured_setpoint					          : 10; // Измеренное значение выходного напряжения для расчета калибровочных коэффициентов(код 02h)
    volatile uint32_t in_v_hi_level_setpoint					          : 10; // Уставка верхней границы допустимого входного напряжения ИБП(код 29h)
    volatile uint32_t in_v_low_level_setpoint					          : 10; // Уставка нижней границы допустимого входного напряжения ИБП(код 2Ah)
    volatile uint32_t middle_v_setpoint					                : 10; // Уставка номинального значения напряжения промежуточной шины постоянного тока(код 30h)
    volatile uint32_t out_v_calibration_factor					        : 11; // Калибровочный коэффициент выходного напряжения (код 03h)    
    volatile uint32_t our_v_deviation_percent_setpoint	        : 7;  // Допустимое отклонение выходного напряжения от номинального значения(код 04h)
    volatile uint32_t out_i_setpoint					                  : 14; // Уставка номинального значения выходного тока(код 05h)
    volatile uint32_t out_i_mesured_phase_a_setpoint		        : 14; // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента(код 06h )
    volatile uint32_t out_i_mesured_phase_b_setpoint		        : 14; // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента(код 07h)   
    volatile uint32_t out_i_mesured_phase_c_setpoint		        : 14; // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента(код 08h )
    volatile uint32_t out_i_calibration_factor_phase_a          : 11; // Калибровочный коэффициент выходного тока в фазе А (код 09h)
    volatile uint32_t out_i_calibration_factor_phase_b          : 11; // Калибровочный коэффициент выходного тока в фазе B (код 0Ah)
    volatile uint32_t out_i_calibration_factor_phase_c          : 11; // Калибровочный коэффициент выходного тока в фазе C (код 0Bh)
    volatile uint32_t out_frequency_setpoint					          : 14; // Уставка номинального значения частоты выходного напряжения (код 0Сh)
    volatile uint32_t out_freq_dev_percent_setpoint			        : 5;  // Допустимое отклонение частоты выходного напряжения от номинального значения (код 0Dh)
    volatile uint32_t out_v_max_cos_setpoint					          : 10; // Уставка максимального значения cosφ на выходе ИБП (код 0Eh)
    volatile uint32_t out_va_setpoint					                  : 16; // Уставка номинального значения выходной мощности (код 0Fh)
    volatile uint32_t time_exceed_100_percent_out_power	        : 16; // Допустимое время превышения 100% выходной мощности (код 10h)
    volatile uint32_t time_exceed_1_level_out_power			        : 16; // Допустимое время превышения  первого порога выходной мощности (код 12h)
    volatile uint32_t time_exceed_2_level_out_power			        : 16; // Допустимое время превышения  второго порога выходной мощности (код 14h)
    volatile uint32_t level_1_percent_out_va_setpoint		        : 8;  // Первый порог превышения выходной мощности(код 11h)
    volatile uint32_t level_2_percent_out_va_setpoint		        : 8;  // Второй порог превышения выходной мощности(код 13h)
    volatile uint32_t max_peak_out_i_setpoint					          : 15; // Уставка максимального пикового выходного тока (код 15h)
    volatile uint32_t bypass_mode_short_circut_setpoint	        : 10; // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)(код 16h
    volatile uint32_t max_temp_kkm_cooler_setpoint			        : 8;  // Уставка максимальной температуры охладителя ККМ, (код 17h)
    volatile uint32_t max_temp_inverter_cooler_setpoint	        : 8;  // Уставка максимальной температуры охладителя инвертора (код 18h )
    volatile uint32_t max_temp_battery_cooler_setpoint	        : 8;  // Уставка максимальной температуры батареи (код 19h )
    volatile uint32_t max_temp_air_setpoint	                    : 8;  // Уставка максимальной температуры воздуха внутри корпуса ИБП (код 1Ah )
    volatile uint32_t min_v_battery_setpoint					          : 15; // Уставка минимального допустимого напряжения АКБ (код 1Bh)
    volatile uint32_t max_v_battery_setpoint					          : 15; // Уставка максимального допустимого напряжения АКБ (код 1Ch)
    volatile uint32_t v_battery_mesured_setpoint				        : 15; // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов(код 1Dh)
    volatile uint32_t temp_battery_k_setpoint					          : 10; // Температурный коэффициент АКБ (код 1Eh)
    volatile uint32_t max_i_discharge_battery_setpoint	        : 12; // Уставка максимального тока разряда АКБ (код 1Fh)
    volatile uint32_t max_i_charge_battery_setpoint	            : 12; // Уставка максимального тока заряда АКБ (код 20h)
    volatile uint32_t min_i_charge_battery_setpoint	            : 12; // Уставка минимального тока заряда АКБ (код 21h)
    volatile uint32_t i_charge_battery_mesured_setpoint	        : 12; // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов(код 24h)
    volatile uint32_t battery_v_cycle_mode_setpoint		          : 15; // Уставка напряжения заряда АКБ в  циклическом режиме (код 22h)
    volatile uint32_t battery_v_buffer_mode_setpoint		        : 15; // Уставка напряжения заряда АКБ в буферном режиме (код 23h)
    volatile uint32_t battery_v_mesured_setpoint				        : 15; // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов (код 26h)
    volatile uint32_t fractional_factor_batt_i_charge_setpoint  : 11; // Калибровочный коэффициент тока заряда АКБ(код 25h)
    volatile uint32_t fractional_factor_batt_u_setpoint					: 11; // Калибровочный коэффициент напряжения заряда АКБ(код 27h)
    volatile uint32_t nominal_battery_capacity_setpoint					: 15; // Номинальная ёмкость АКБ (код 28h)
    volatile uint32_t unbalance_factor_in_v_setpoint					  : 4;  // Коэффициент несимметрии по входному напряжению (код 2Bh)
    volatile uint32_t unbalance_factor_in_i_setpoint					  : 4;  // Коэффициент несимметрии по входному току (код 2Dh)
    volatile uint32_t in_i_max_setpoint					                : 10; // Уставка максимального значения входного тока ИБП (код 2Сh)
    volatile uint32_t in_frequency_max_setpoint					        : 8;  // Уставка верхней границы допустимой частоты входного напряжения,  % от номинального значенеия  (код 2Eh)
    volatile uint32_t in_frequency_min_setpoint					        : 8;  //  Уставка нижней границы допустимой частоты входного напряжения, % от номинального значенеия  (код 2Fh)
    volatile uint32_t max_speed_fun_1_setpoint					        : 15; // Максимальная скорость вентилятора 1(код 31h)
    volatile uint32_t max_speed_fun_2_setpoint					        : 15; // Максимальная скорость вентилятора 2(код 32h)
    volatile uint32_t max_speed_fun_res_1_setpoint					    : 15; // Максимальная скорость вентилятора резерв 1(код 36h)
    volatile uint32_t max_speed_fun_res_2_setpoint					    : 15; // Максимальная скорость вентилятора резерв 2 (код 37h)
    volatile uint32_t max_speed_fun_res_3_setpoint					    : 15; // Максимальная скорость вентилятора резерв 3 (код 38h)
    volatile uint32_t max_temperature_res_1_setpoint					  : 8;  // Уставка максимальной температуры резерв 1(код 33h)
    volatile uint32_t max_temperature_res_2_setpoint					  : 8;  // Уставка максимальной температуры резерв 2(код 34h)
    volatile uint32_t max_temperature_res_3_setpoint					  : 8;  // Уставка максимальной температуры резерв 3(код 35h)
    volatile uint32_t operating_mode_after_power_on_setpoint	  : 1;  // Режим работы ИБП после включения (код 39h)
    volatile uint32_t operating_mode_after_emergency_setpoint   : 1;  // Режим работы ИБП при аварии (код 3Ah)
    volatile uint32_t in_power_line_synchronization_setpoint	  : 2;  // Синхронизация с входной сетью (код 3Bh)
    volatile uint32_t battery_time_as_low_battery_setpoint		  : 16; // Уставка времени работы от батареи, ниже которой заряд батареи считается низким  (код 3Ch)
  }__attribute__((packed)) data_bits;
}prop_setpoints_t;



// FF00
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t neutral_alarm 				                      : 1; // Неверное подключение нейтрали входного напряжения ИБП
    volatile uint32_t in_v_phase_a_out_range_alarm 							  : 1; // Входное напряжение ИБП в фазе А вне допустимого диапазона
    volatile uint32_t in_v_phase_b_out_range_alarm 							  : 1; // Входное напряжение ИБП в фазе B вне допустимого диапазона
    volatile uint32_t in_v_phase_c_out_range_alarm 							  : 1; // Входное напряжение ИБП в фазе C вне допустимого диапазона
    volatile uint32_t in_i_phase_a_out_range_alarm 							  : 1; // Значение входного тока ИБП в фазе A вне допустимого диапазона
    volatile uint32_t in_i_phase_b_out_range_alarm 							  : 1; // Значение входного тока ИБП в фазе A вне допустимого диапазона
    volatile uint32_t in_i_phase_c_out_range_alarm 							  : 1; // Значение входного тока ИБП в фазе A вне допустимого диапазона
    volatile uint32_t in_frequency_phase_a_out_range_alarm 			  : 1; // Частота входного напряжения ИБП в фазе A вне допустимого диапазона
    volatile uint32_t in_frequency_phase_b_out_range_alarm 			  : 1; // Частота входного напряжения ИБП в фазе B вне допустимого диапазона
    volatile uint32_t in_frequency_phase_c_out_range_alarm 			  : 1; // Частота входного напряжения ИБП в фазе C вне допустимого диапазона
    volatile uint32_t in_phase_shift_phase_a_out_range_alarm 		  : 1; // Фазовый сдвиг входного напряжения ИБП (фаза A) вне допустимого диапазона
    volatile uint32_t in_phase_shift_phase_b_out_range_alarm 		  : 1; // Фазовый сдвиг входного напряжения ИБП (фаза B) вне допустимого диапазона
    volatile uint32_t in_phase_shift_phase_c_out_range_alarm 		  : 1; // Фазовый сдвиг входного напряжения ИБП (фаза C) вне допустимого диапазона
    volatile uint32_t middle_v_positive_alarm 		                : 1; // Положительное напряжение на шине постоянного тока не соответствует уставке
    volatile uint32_t middle_v_negative_alarm 		                : 1; // Отрицательное напряжение на шине постоянного тока не соответствует уставке
    volatile uint32_t out_v_phase_a_out_range_alarm 						  : 1; // Выходное напряжение ИБП в фазе А вне допустимого диапазона
    volatile uint32_t out_v_phase_b_out_range_alarm 						  : 1; // Выходное напряжение ИБП в фазе B вне допустимого диапазона
    volatile uint32_t out_v_phase_c_out_range_alarm 						  : 1; // Выходное напряжение ИБП в фазе C вне допустимого диапазона
    volatile uint32_t out_i_phase_a_exceed_alarm 							    : 1; // Превышение выходного тока ИБП в фазе A
    volatile uint32_t out_i_phase_b_exceed_alarm 							    : 1; // Превышение выходного тока ИБП в фазе B
    volatile uint32_t out_i_phase_c_exceed_alarm 							    : 1; // Превышение выходного тока ИБП в фазе C
    volatile uint32_t out_short_circut_phase_a_alarm 						  : 1; // Короткое замыкание на выходе ИБП в фазе A
    volatile uint32_t out_short_circut_phase_b_alarm 						  : 1; // Короткое замыкание на выходе ИБП в фазе B
    volatile uint32_t out_short_circut_phase_c_alarm 						  : 1; // Короткое замыкание на выходе ИБП в фазе C
    volatile uint32_t out_power_exceed_alarm 						          : 1; // Превышение выходной мощности
    volatile uint32_t out_peak_i_phase_a_exceed_alarm 		        : 1; // Превышение пикового значения выходного тока ИБП в фазе A
    volatile uint32_t out_peak_i_phase_b_exceed_alarm 		        : 1; // Превышение пикового значения выходного тока ИБП в фазе B
    volatile uint32_t out_peak_i_phase_c_exceed_alarm 		        : 1; // Превышение пикового значения выходного тока ИБП в фазе C
    volatile uint32_t out_over_v_phase_a_alarm 		                : 1; // Перенапряжение на выходе ИБП в фазе A
    volatile uint32_t out_over_v_phase_b_alarm 		                : 1; // Перенапряжение на выходе ИБП в фазе B
    volatile uint32_t out_over_v_phase_c_alarm 		                : 1; // Перенапряжение на выходе ИБП в фазе C
    volatile uint32_t out_frequency_phase_a_out_range_alarm 	    : 1; // Частота выходного напряжения ИБП в фазе A вне допустимого диапазона
    volatile uint32_t out_frequency_phase_b_out_range_alarm 	    : 1; // Частота выходного напряжения ИБП в фазе B вне допустимого диапазона
    volatile uint32_t out_frequency_phase_c_out_range_alarm 	    : 1; // Частота выходного напряжения ИБП в фазе C вне допустимого диапазона
    volatile uint32_t out_v_phase_shift_phase_a_out_range_alarm   : 1; // Фазовый сдвиг выходного напряжения ИБП (фаза A) вне допустимого диапазона
    volatile uint32_t out_v_phase_shift_phase_b_out_range_alarm   : 1; // Фазовый сдвиг выходного напряжения ИБП (фаза B) вне допустимого диапазона
    volatile uint32_t out_v_phase_shift_phase_c_out_range_alarm   : 1; // Фазовый сдвиг выходного напряжения ИБП (фаза C) вне допустимого диапазона
    volatile uint32_t out_i_phase_shift_phase_a_out_range_alarm   : 1; // Фазовый сдвиг выходного тока ИБП (фаза A) вне допустимого диапазона
    volatile uint32_t out_i_phase_shift_phase_b_out_range_alarm   : 1; // Фазовый сдвиг выходного тока ИБП (фаза B) вне допустимого диапазона
    volatile uint32_t out_i_phase_shift_phase_c_out_range_alarm   : 1; // Фазовый сдвиг выходного тока ИБП (фаза C) вне допустимого диапазона
    volatile uint32_t charger_i_value_dosent_match_setpoint_alarm : 1; // Значение тока зарядного устройства не соответствует уставке
    volatile uint32_t battery_v_out_range_alarm 		              : 1; // Напряжение АКБ вне допустимого диапазона
    volatile uint32_t battery_i_out_range_alarm 		              : 1; // Ток разряда АКБ вне допустимого диапазона
    volatile uint32_t no_battery_alarm 		                        : 1; // Отсутствует АКБ
    volatile uint32_t battery_discharge_alarm 		                : 1; // АКБ разряжена
    volatile uint32_t temp_kkm_cooler_exceed_setpoint_alarm 		  : 1; // Температура охладителя ККМ превысила уставку
    volatile uint32_t temp_inverter_cooler_exceed_setpoint_alarm  : 1; // Температура охладителя инвертора превысила уставку
    volatile uint32_t temp_battery_exceed_setpoint_alarm          : 1; // Температура батареи превысила уставку
    volatile uint32_t temp_inbox_air_exceed_setpoint_alarm        : 1; // Температура воздуха внутри корпуса ИБП превысила уставку
    volatile uint32_t fun_1_emergency_alarm 		                  : 1; // Авария вентилятора 1
    volatile uint32_t fun_2_emergency_alarm 		                  : 1; // Авария вентилятора 2
    volatile uint32_t battery_time_less_setpoint_alarm 		        : 1; // Время работы от АКБ менше заданного при текущей нагрузке
    volatile uint32_t battery_replacement_required_alarm 		      : 1; // Требуется замена АКБ
    volatile uint32_t bypass_emergency_alarm 		                  : 1; // Авария байпаса.
  }__attribute__((packed)) data_bits;
}prop_fault_status_t;



// EF00
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t cmd_code					                : 8;
    volatile uint32_t ip_adr					                  : 32;
    volatile uint32_t reserve					                  : 24;
  } __attribute__((packed)) data_bits;
}prop_spc_cmd_ip_adr_t;

typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t cmd_code					                : 8;
    volatile uint32_t ip_adr_type					              : 1;
    volatile uint32_t res_1					                    : 24;
    volatile uint32_t res_2					                    : 32;    
  } __attribute__((packed)) data_bits;
}prop_spc_cmd_ip_adr_type_t;

typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t cmd_code					                : 8;
    volatile uint32_t mb_adr					                  : 8;
    volatile uint32_t mb_baudrate					              : 8;
    volatile uint32_t res_1					                    : 8;
    volatile uint32_t res_2					                    : 32;    
  } __attribute__((packed)) data_bits;
}prop_spc_cmd_mb_settings_t;

typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t cmd_code					                : 8;
    volatile uint32_t dry_in_1					                : 4;
    volatile uint32_t dry_in_2					                : 4;
    volatile uint32_t dry_in_3					                : 4;
    volatile uint32_t dry_in_4					                : 4;
    volatile uint32_t dry_in_5					                : 4;
    volatile uint32_t dry_out_1					                : 4;
    volatile uint32_t dry_out_2					                : 4;
    volatile uint32_t dry_out_3					                : 4;
    volatile uint32_t dry_out_4					                : 4;
    volatile uint32_t dry_out_5					                : 4;
    volatile uint32_t bat_percent_as_low					      : 8;
    volatile uint32_t res_1					                    : 8;
  } __attribute__((packed)) data_bits;
}prop_spc_cmd_dry_settings_t;

// FF70
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t ip_adr					                  : 32;
    volatile uint32_t net_mask					                : 32;
  } __attribute__((packed)) data_bits;
}prop_ip_mask_t;

// FF71
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t gate_adr					                : 32;
    volatile uint32_t ip_adr_type					              : 1;
    volatile uint32_t res_1					                    : 31;    
  } __attribute__((packed)) data_bits;
}prop_gate_type_t;

// FF72
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t mb_adr					                  : 8;
    volatile uint32_t mb_baud					                  : 8;    
    volatile uint32_t res_1					                    : 16;    
    volatile uint32_t res_2					                    : 32;    
  } __attribute__((packed)) data_bits;
}prop_mb_settings_t;

// FF73
typedef union
{
  volatile uint8_t data[ 8 ];
  struct
  {
    volatile uint32_t dry_in_1					                : 4;
    volatile uint32_t dry_in_2					                : 4;
    volatile uint32_t dry_in_3					                : 4;
    volatile uint32_t dry_in_4					                : 4;
    volatile uint32_t dry_in_5					                : 4;
    volatile uint32_t dry_out_1					                : 4;
    volatile uint32_t dry_out_2					                : 4;
    volatile uint32_t dry_out_3					                : 4;
    volatile uint32_t dry_out_4					                : 4;
    volatile uint32_t dry_out_5					                : 4;
    volatile uint32_t bat_percent_as_low					      : 8;
    volatile uint32_t res_1					                    : 16;
  } __attribute__((packed)) data_bits;
}prop_dry_settings_t;





#ifdef __cplusplus
}
#endif

#endif // __KW_PROTO_STRUCTS_H



