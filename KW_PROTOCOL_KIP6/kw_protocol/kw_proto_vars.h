/**
 *
 *	\file		kw_proto_vars.h
 *	\brief	Модуль для работы c переменными протокола на CAN шине
 *
 *
 */

#ifndef __KW_PROTO_VARS_H
#define __KW_PROTO_VARS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "kw_proto_cfg.h"

///< Универсальный тип для передачи значений в функцию из функции
typedef union
{
  volatile float val_float;
  volatile int32_t val_int;
  volatile uint8_t val_byte[4];
}value_pack_t;

///< Тип данных для передачи даты/времени в функцию из функции
typedef struct 
{
    uint8_t sec;   // секунды 0 - 60
    uint8_t min;   // минуты 0 - 59
    uint8_t hour;  // часы 0 - 23
    uint8_t mday;  // день месяца 1 - 31
    uint8_t mon;   // месяц 1-12
    uint8_t year;  // год, начиная с 1985 года: 0-1985, 1-1986
}prop_dt_t;


///< Перечисление, которое описывает стандартные скорости модбас
typedef enum 
{
  BAUD_110      = 0,
  BAUD_300,
  BAUD_1200,
  BAUD_2400,
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200,
  BAUD_230400,
  BAUD_460800,
  BAUD_921600,
}ENUM_MB_BAUDRATE;


///< Перечисление, которое описывает тип IP адресации
typedef enum 
{
  IP_STATIC      = 0,
  IP_DYNAMIC,
}ENUM_IP_ADRESSING_TYPE;

///< Перечисление, которое описывает функцию дискретного входа сухих контактов
typedef enum 
{
  INPUT_FUNC_TO_SLEEP    = 1,     // Перейти в спящий режим
  INPUT_FUNC_TO_STANDBY,          // Перейти в режим ожидания
  INPUT_FUNC_TO_BYPASS,           // Перейти в режим байпасс
  INPUT_FUNC_TO_ONLINE,           // Перейти в сетевой режим
  INPUT_FUNC_TO_ONBATTERY,        // Перейти в автономный режим
}ENUM_DRY_CONTACT_INPUT_FUNCTION; 

///< Перечисление, которое описывает функцию дискретного выхода сухих контактов
typedef enum 
{
  OUTPUT_FUNC_FAULT_MODE,         // Показывается режим аварии
  OUTPUT_FUNC_BYPASS_MODE,        // Показывается  режим байпасс
  OUTPUT_FUNC_ONLINE_MODE,        // Показывается  сетевой режим 
  OUTPUT_FUNC_ONBATTERY_MODE,     // Показывается автономный режим 
  OUTPUT_FUNC_BATTERY_LOW,        // Показывается разряд батареи 
}ENUM_DRY_CONTACT_OUTPUT_FUNCTION; 


///< Перечисление, которое описывает аварии
typedef enum 
{
	ALARM_NEUTRAL                           = 0x00,
	ALARM_IN_VOLTAGE_PHASE_A_OUT_RANGE,
	ALARM_IN_VOLTAGE_PHASE_B_OUT_RANGE,
	ALARM_IN_VOLTAGE_PHASE_C_OUT_RANGE,
	ALARM_IN_CURRENT_PHASE_A_OUT_RANGE,
	ALARM_IN_CURRENT_PHASE_B_OUT_RANGE,
	ALARM_IN_CURRENT_PHASE_C_OUT_RANGE,
	ALARM_IN_FREQUENCY_PHASE_A_OUT_RANGE,
	ALARM_IN_FREQUENCY_PHASE_B_OUT_RANGE,
	ALARM_IN_FREQUENCY_PHASE_C_OUT_RANGE,
	ALARM_IN_PHASE_SHIFT_PHASE_A_OUT_RANGE,
	ALARM_IN_PHASE_SHIFT_PHASE_B_OUT_RANGE,
	ALARM_IN_PHASE_SHIFT_PHASE_C_OUT_RANGE,
	ALARM_MIDDLE_POSITIVE_VOLTAGE_DOESNT_MATCH_SETPOINT,  // does not match the setpoint
	ALARM_MIDDLE_NEGATIVE_VOLTAGE_DOESNT_MATCH_SETPOINT,  // does not match the setpoint
	ALARM_OUT_VOLTAGE_PHASE_A_OUT_RANGE,
	ALARM_OUT_VOLTAGE_PHASE_B_OUT_RANGE,
	ALARM_OUT_VOLTAGE_PHASE_C_OUT_RANGE,	
	ALARM_OUT_CURRENT_PHASE_A_EXCEEED,
	ALARM_OUT_CURRENT_PHASE_B_EXCEEED,
	ALARM_OUT_CURRENT_PHASE_C_EXCEEED,
  ALARM_OUT_SHORT_CIRCUIT_PHASE_A,
  ALARM_OUT_SHORT_CIRCUIT_PHASE_B,
  ALARM_OUT_SHORT_CIRCUIT_PHASE_C,
	ALARM_OUT_POWER_EXCEEED,
	ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED,
	ALARM_OUT_CURRENT_PEAK_PHASE_B_EXCEEED,
	ALARM_OUT_CURRENT_PEAK_PHASE_C_EXCEEED,
	ALARM_OUT_OVER_VOLTAGE_PHASE_A,
	ALARM_OUT_OVER_VOLTAGE_PHASE_B,
	ALARM_OUT_OVER_VOLTAGE_PHASE_C,	
	ALARM_OUT_FREQUENCY_PHASE_A_OUT_RANGE,
	ALARM_OUT_FREQUENCY_PHASE_B_OUT_RANGE,
	ALARM_OUT_FREQUENCY_PHASE_C_OUT_RANGE,	
	ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A_OUT_RANGE,
	ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B_OUT_RANGE,
	ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C_OUT_RANGE,
	ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_A_OUT_RANGE,
	ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_B_OUT_RANGE,
	ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_C_OUT_RANGE,
	ALARM_CHARGER_CURRENT_VALUE_DOESNT_MATCH_SETPOINT,
	ALARM_BATTERY_VOLTAGE_OUT_RANGE,
	ALARM_BATTERY_CURRENT_OUT_RANGE,
	ALARM_NO_BATTERY,
	ALARM_BATTERY_DISCHARGE,
	ALARM_TEMPERATURE_KKM_COOLER_EXCEED_SETPOINT,
	ALARM_TEMPERATURE_INVERTER_COOLER_EXCEED_SETPOINT,
	ALARM_TEMPERATURE_BATTERY_EXCEED_SETPOINT,
	ALARM_TEMPERATURE_INBOX_AIR_EXCEED_SETPOINT,
	ALARM_FUN_1_EMERGENCY,
	ALARM_FUN_2_EMERGENCY,
	ALARM_BATTERY_TIME_LESS_SETPOINT,
	ALARM_BATTERY_REPLACEMENT_REQUIRED,
  ALARM_BYPASS_EMERGENCY,
  ALARM_MAX,
}ENUM_ALARM_NAME;

///< Перечисление, которое описывает уставки
typedef enum 
{
	SETPOINT_OUT_VOLTAGE  = 0x01,                       // Уставка номинального значения выходного напряжения
	SETPOINT_MEASURED_OUT_VOLTAGE,                      //  Измеренное значение выходного напря жения для расчета калибровочных коэффициентов
	SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE,            // Калибровочный коэффициент выходного напряжения
	SETPOINT_DEVIATION_OUT_VOLTAGE,                     // Допустимое отклонение выходного напряжения от номинального значения
	SETPOINT_OUT_CURRENT,                               // Уставка номинального значения выходного тока
	SETPOINT_MEASURED_OUT_CURRENT_PHASE_A,              // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента
	SETPOINT_MEASURED_OUT_CURRENT_PHASE_B,              // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента
	SETPOINT_MEASURED_OUT_CURRENT_PHASE_C,              // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента
  SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A,    // Калибровочный коэффициент выходного тока в фазе А
  SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B,    // Калибровочный коэффициент выходного тока в фазе B
  SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C,    // Калибровочный коэффициент выходного тока в фазе C
  SETPOINT_OUT_FREQUENCY,                             // Уставка номинального значения частоты выходного напряжения
  SETPOINT_DEVIATION_OUT_FREQUENCY,                   // Допустимое отклонение частоты выходного напряжения от номинального значения
	SETPOINT_OUT_COS_MAX,                               // Уставка максимального значения cosφ на выходе ИБП
	SETPOINT_OUT_POWER,                                 // Уставка номинального значения выходной мощности
  SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER,         // Допустимое время превышения 100% выходной мощности
	SETPOINT_FIRST_THRESHHOLD_OUT_POWER,                // Первый порог превышения выходной мощности в %
	SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER,    // Допустимое время превышения первого порога выходной мощности
  SETPOINT_SECOND_THRESHHOLD_OUT_POWER,               // Второй порог превышения выходной мощности в %
	SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER,   // Допустимое время превышения второго порога выходной мощности
	SETPOINT_OUT_PEAK_CURRENT,                          // Уставка максимального пикового выходного тока
	SETPOINT_OUT_SHORT_CIRCUT_CURRENT,                  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
	SETPOINT_COOLER_KKM_MAX_TEMP,                       // Уставка максимальной температуры охладителя ККМ
	SETPOINT_COOLER_INVERTER_MAX_TEMP,                  // Уставка максимальной температуры охладителя инвертора
	SETPOINT_BATTERY_MAX_TEMP,                          // Уставка максимальной температуры батареи
	SETPOINT_INBOX_AIR_MAX_TEMP,                        // Уставка максимальной температуры воздуха внутри корпуса ИБП
	SETPOINT_BATTERY_MIN_VOLTAGE,                       // Уставка минимального допустимого напряжения АКБ
	SETPOINT_BATTERY_MAX_VOLTAGE,                       // Уставка максимального допустимого напряжения АКБ
	SETPOINT_MEASURED_VOLTAGE_BATTERY,                  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов
	SETPOINT_TEMP_COEFFICIENT_BATTERY,                  // Температурный коэффициент АКБ
	SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY,             // Уставка максимального тока разряда АКБ
	SETPOINT_MAX_CHARGE_CURRENT_BATTERY,                // Уставка максимального тока заряда АКБ
	SETPOINT_MIN_CHARGE_CURRENT_BATTERY,                //Уставка минимального тока заряда АКБ
	SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE,        // Уставка напряжения заряда АКБ в циклическом режиме 
	SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE,        // Уставка напряжения заряда АКБ в буферном режиме 	
  SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY,           // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов
	SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY, // Калибровочный коэффициент тока заряда АКБ
	SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY,           // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов
	SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY, // Калибровочный коэффициент напряжения заряда АКБ
	SETPOINT_CAPACITY_BATTERY,                          // Номинальная ёмкость АКБ
	SETPOINT_IN_VOLTAGE_HI_THRESHHOLD,                  // Уставка верхней границы допустимого входного напряжения ИБП
	SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD,                 // Уставка нижней границы допустимого входного напряжения ИБП
	SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT,          // Коэффициент несимметрии по входному напряжению
	SETPOINT_IN_CURRENT_MAX,                            // Уставка максимального значения входного тока ИБП
	SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT,          // Коэффициент несимметрии по входному току
	SETPOINT_IN_FREQUENCY_HI_THRESHHOLD,                // Уставка верхней границы допустимой частоты входного напряжения, % от номинального значения
	SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD,               // Уставка нижней границы допустимой частоты входного напряжения, % от номинального значения
	SETPOINT_MIDDLE_VOLTAGE,                            // Уставка номинального значения напряжения промежуточной шины постоянного тока
	SETPOINT_FUN_1_MAX_SPEED,                           // Максимальная скорость вентилятора 1
	SETPOINT_FUN_2_MAX_SPEED,                           // Максимальная скорость вентилятора 2
	SETPOINT_RES_1_MAX_TEMP,                            // Уставка максимальной температуры резерв 1
	SETPOINT_RES_2_MAX_TEMP,                            // Уставка максимальной температуры резерв 2
	SETPOINT_RES_3_MAX_TEMP,                            // Уставка максимальной температуры резерв 3
	SETPOINT_FUN_RES_1_MAX_SPEED,                       // Максимальная скорость резерв 1
	SETPOINT_FUN_RES_2_MAX_SPEED,                       // Максимальная скорость резерв 2
	SETPOINT_FUN_RES_3_MAX_SPEED,                       // Максимальная скорость резерв 3
	SETPOINT_WORKING_MODE_AFTER_POWER_UP,               // Режим работы модуля ИБП после включения
	SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT,          // Переход между режимами работы модуля ИБП при возникновении аварийного события 	
  SETPOINT_POWER_LINE_SYNC,                           // Синхронизация с входной сетью
	SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE,             // Уставка времени работы от батареи, ниже которой уровень заряда батареи считается низким

	SETPOINT_KIP6_IP_ADR,                               // Уставка IP адрес устройства
	SETPOINT_KIP6_IP_MASK,                              // Уставка IP маска сети
	SETPOINT_KIP6_IP_GATE,                              // Уставка IP арес шлюза сети
	SETPOINT_KIP6_IP_TYPE,                              // Уставка тип IP адресации 
	SETPOINT_KIP6_MB_ADR,                               // Уставка адрес устройстваства на шине ModBus
	SETPOINT_KIP6_MB_BAUD,                              // Уставка скорость устройстваства на шине ModBus
	SETPOINT_KIP6_IN_1_FUNCTION,                        // Уставка функция сухого контакта входа 1
	SETPOINT_KIP6_IN_2_FUNCTION,                        // Уставка функция сухого контакта входа 2
	SETPOINT_KIP6_IN_3_FUNCTION,                        // Уставка функция сухого контакта входа 3
	SETPOINT_KIP6_IN_4_FUNCTION,                        // Уставка функция сухого контакта входа 4
	SETPOINT_KIP6_IN_5_FUNCTION,                        // Уставка функция сухого контакта входа 5
	SETPOINT_KIP6_OUT_1_FUNCTION,                       // Уставка функция сухого контакта выхода 1
	SETPOINT_KIP6_OUT_2_FUNCTION,                       // Уставка функция сухого контакта выхода 2
	SETPOINT_KIP6_OUT_3_FUNCTION,                       // Уставка функция сухого контакта выхода 3
	SETPOINT_KIP6_OUT_4_FUNCTION,                       // Уставка функция сухого контакта выхода 4
	SETPOINT_KIP6_OUT_5_FUNCTION,                       // Уставка функция сухого контакта выхода 5
	SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW,               // Уставка процент заряда батареи, когда заряд считаетс низким  

  SETPOINT_MAX,
}ENUM_SETPOINT_NAME;

/*
///< Перечисление, которое описывает уставки
typedef enum 
{
	SETPOINT_KIP6_IP_ADR,                               // Уставка IP адрес устройства
	SETPOINT_KIP6_IP_MASK,                              // Уставка IP маска сети
	SETPOINT_KIP6_IP_GATE,                              // Уставка IP арес шлюза сети
	SETPOINT_KIP6_IP_TYPE,                              // Уставка тип IP адресации 
	SETPOINT_KIP6_MB_ADR,                               // Уставка адрес устройстваства на шине ModBus
	SETPOINT_KIP6_MB_BAUD,                              // Уставка скорость устройстваства на шине ModBus
	SETPOINT_KIP6_IN_1_FUNCTION,                        // Уставка функция сухого контакта входа 1
	SETPOINT_KIP6_IN_2_FUNCTION,                        // Уставка функция сухого контакта входа 2
	SETPOINT_KIP6_IN_3_FUNCTION,                        // Уставка функция сухого контакта входа 3
	SETPOINT_KIP6_IN_4_FUNCTION,                        // Уставка функция сухого контакта входа 4
	SETPOINT_KIP6_IN_5_FUNCTION,                        // Уставка функция сухого контакта входа 5
	SETPOINT_KIP6_OUT_1_FUNCTION,                       // Уставка функция сухого контакта выхода 1
	SETPOINT_KIP6_OUT_2_FUNCTION,                       // Уставка функция сухого контакта выхода 2
	SETPOINT_KIP6_OUT_3_FUNCTION,                       // Уставка функция сухого контакта выхода 3
	SETPOINT_KIP6_OUT_4_FUNCTION,                       // Уставка функция сухого контакта выхода 4
	SETPOINT_KIP6_OUT_5_FUNCTION,                       // Уставка функция сухого контакта выхода 5
	SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW,               // Уставка процент заряда батареи, когда заряд считаетс низким  

  SETPOINT_KIP6_MAX,
}ENUM_SETPOINT_KIP6_NAME;
*/



///< Перечисление, которое описывает переменные
typedef enum 
{
  VALUE_IN_1_VOLTAGE_RMS_PHASE_A   = 0,
  VALUE_IN_1_VOLTAGE_RMS_PHASE_B,
  VALUE_IN_1_VOLTAGE_RMS_PHASE_C,
  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_A,
  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_B,
  VALUE_IN_1_VOLTAGE_PHASE_SHIFT_PHASE_C,
  VALUE_UPS_WORKING_MODE,
  VALUE_ON_OFF_BUTTON_STATE,
  VALUE_IN_2_VOLTAGE_RMS_PHASE_A,
  VALUE_IN_2_VOLTAGE_RMS_PHASE_B,
  VALUE_IN_2_VOLTAGE_RMS_PHASE_C,
  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_A,
  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_B,
  VALUE_IN_2_VOLTAGE_PHASE_SHIFT_PHASE_C,
  VALUE_IN_3_VOLTAGE_RMS_PHASE_A,
  VALUE_IN_3_VOLTAGE_RMS_PHASE_B,
  VALUE_IN_3_VOLTAGE_RMS_PHASE_C,
  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_A,
  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_B,
  VALUE_IN_3_VOLTAGE_PHASE_SHIFT_PHASE_C,
  VALUE_IN_1_CURRENT_RMS_PHASE_A,
  VALUE_IN_1_CURRENT_RMS_PHASE_B,
  VALUE_IN_1_CURRENT_RMS_PHASE_C,
  VALUE_IN_1_POWER,
  VALUE_IN_2_CURRENT_RMS_PHASE_A,
  VALUE_IN_2_CURRENT_RMS_PHASE_B,
  VALUE_IN_2_CURRENT_RMS_PHASE_C,
  VALUE_IN_2_POWER,
  VALUE_IN_3_CURRENT_RMS_PHASE_A,
  VALUE_IN_3_CURRENT_RMS_PHASE_B,
  VALUE_IN_3_CURRENT_RMS_PHASE_C,
  VALUE_IN_3_POWER,
  VALUE_IN_1_FREQUENCY_PHASE_A,
  VALUE_IN_1_FREQUENCY_PHASE_B,
  VALUE_IN_1_FREQUENCY_PHASE_C,
  VALUE_IN_2_FREQUENCY_PHASE_A,
  VALUE_IN_2_FREQUENCY_PHASE_B,
  VALUE_IN_2_FREQUENCY_PHASE_C,
  VALUE_IN_3_FREQUENCY_PHASE_A,
  VALUE_IN_3_FREQUENCY_PHASE_B,
  VALUE_IN_3_FREQUENCY_PHASE_C,
  VALUE_IN_LINES_BAD_STATES_COUNT,
  VALUE_IN_LINES_NUMBERS,
  VALUE_OUT_1_VOLTAGE_RMS_PHASE_A,
  VALUE_OUT_1_VOLTAGE_RMS_PHASE_B,
  VALUE_OUT_1_VOLTAGE_RMS_PHASE_C,
  VALUE_OUT_1_POWER,
  VALUE_OUT_1_PERCENT,
  VALUE_OUT_2_VOLTAGE_RMS_PHASE_A,
  VALUE_OUT_2_VOLTAGE_RMS_PHASE_B,
  VALUE_OUT_2_VOLTAGE_RMS_PHASE_C,
  VALUE_OUT_2_POWER,
  VALUE_OUT_2_PERCENT,
  VALUE_OUT_3_VOLTAGE_RMS_PHASE_A,
  VALUE_OUT_3_VOLTAGE_RMS_PHASE_B,
  VALUE_OUT_3_VOLTAGE_RMS_PHASE_C,
  VALUE_OUT_3_POWER,
  VALUE_OUT_3_PERCENT,
  VALUE_OUT_1_CURRENT_RMS_PHASE_A,
  VALUE_OUT_1_CURRENT_RMS_PHASE_B,
  VALUE_OUT_1_CURRENT_RMS_PHASE_C,
  VALUE_OUT_2_CURRENT_RMS_PHASE_A,
  VALUE_OUT_2_CURRENT_RMS_PHASE_B,
  VALUE_OUT_2_CURRENT_RMS_PHASE_C,
  VALUE_OUT_3_CURRENT_RMS_PHASE_A,
  VALUE_OUT_3_CURRENT_RMS_PHASE_B,
  VALUE_OUT_3_CURRENT_RMS_PHASE_C,
  VALUE_OUT_FREQUENCY_PHASE_A,
  VALUE_OUT_FREQUENCY_PHASE_B,
  VALUE_OUT_FREQUENCY_PHASE_C,
  VALUE_OUT_POWER_SOURCE,
  VALUE_OUT_LINES_NUMBER,
  VALUE_TEST_RESULT,
  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A,
  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B,
  VALUE_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C,
  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_A,
  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_B,
  VALUE_BYPASS_1_VOLTAGE_RMS_PHASE_C,
  VALUE_BYPASS_1_POWER,
  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_A,
  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_B,
  VALUE_BYPASS_2_VOLTAGE_RMS_PHASE_C,
  VALUE_BYPASS_2_POWER,
  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_A,
  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_B,
  VALUE_BYPASS_3_VOLTAGE_RMS_PHASE_C,
  VALUE_BYPASS_3_POWER,
  VALUE_BYPASS_1_CURRENT_RMS_PHASE_A,
  VALUE_BYPASS_1_CURRENT_RMS_PHASE_B,
  VALUE_BYPASS_1_CURRENT_RMS_PHASE_C,
  VALUE_BYPASS_2_CURRENT_RMS_PHASE_A,
  VALUE_BYPASS_2_CURRENT_RMS_PHASE_B,
  VALUE_BYPASS_2_CURRENT_RMS_PHASE_C,
  VALUE_BYPASS_3_CURRENT_RMS_PHASE_A,
  VALUE_BYPASS_3_CURRENT_RMS_PHASE_B,
  VALUE_BYPASS_3_CURRENT_RMS_PHASE_C,
  VALUE_BYPASS_FREQUENCY_PHASE_A,
  VALUE_BYPASS_FREQUENCY_PHASE_B,
  VALUE_BYPASS_FREQUENCY_PHASE_C,
  VALUE_BYPASS_LINES_NUMBER,
  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_A,
  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_B,
  VALUE_BYPASS_VOLTAGE_PHASE_SHIFT_PHASE_C,
  VALUE_INVERTER_CURRENT_RMS_PHASE_A,
  VALUE_INVERTER_CURRENT_RMS_PHASE_B,
  VALUE_INVERTER_CURRENT_RMS_PHASE_C,
  VALUE_MIDDLE_BUS_POSITIVE_VOLTAGE,
  VALUE_MIDDLE_BUS_NEGATIVE_VOLTAGE,
  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_A,
  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_B,
  VALUE_OUT_CURRENT_PHASE_SHIFT_PHASE_C,
  VALUE_INVERTER_VOLTAGE_RMS_PHASE_A,
  VALUE_INVERTER_VOLTAGE_RMS_PHASE_B,
  VALUE_INVERTER_VOLTAGE_RMS_PHASE_C,
  VALUE_BATTERY_VOLTAGE,
  VALUE_BATTERY_CURRENT,
  VALUE_CHARGER_VOLTAGE,
  VALUE_CHARGER_CURRENT,
  VALUE_BATTERY_CHARGE_PERCENT,
  VALUE_BATTERY_REMAINING_TIME,
  VALUE_BATTERY_WORKING_TIME,
  VALUE_BATTERY_STATUS,
  VALUE_KKM_COOLER_TEMPERATURE,
  VALUE_INTO_UPS_AIR_TEMPERATURE,
  VALUE_BATTERY_TEMPERATURE,
  VALUE_INVERTER_COOLER_TEMPERATURE,
  VALUE_RESERVE_1_TEMPERATURE,
  VALUE_RESERVE_2_TEMPERATURE,
  VALUE_RESERVE_3_TEMPERATURE,
  VALUE_FUN_1_SPEED,
  VALUE_FUN_2_SPEED,
  VALUE_FUN_RES1_SPEED,
  VALUE_FUN_RES2_SPEED,
  VALUE_FUN_RES3_SPEED,
  VALUE_MAX,
}ENUM_VALUE_NAME;


///< Перечисление, которое описывает массивы
typedef enum 
{
  ARRAY_ID_CARD   = 0,
  ARRAY_TEST_RESULT_STR,
  ARRAY_MAX,

}ENUM_ARRAY_NAME;



///< Указатель на функцию инициализации переменных
typedef void     ( *func_vars_init_t )              ( void );


///< Указатель на функцию получения статуса аварии
typedef int32_t  ( *func_vars_get_alarm_status_t )  ( ENUM_ALARM_NAME alarm_name );

///< Указатель на функцию установки статуса аварии
typedef int32_t  ( *func_vars_set_alarm_status_t )  ( ENUM_ALARM_NAME alarm_name, uint32_t val );

///< Указатель на функцию получения уставки
typedef int32_t  ( *func_vars_get_setpoint_t )      ( ENUM_SETPOINT_NAME setpoint_name, value_pack_t *p_setpoint );

///< Указатель на функцию установки уставки
typedef int32_t  ( *func_vars_set_setpoint_t )      ( ENUM_SETPOINT_NAME setpoint_name, value_pack_t val );

///< Указатель на функцию получения значения
typedef int32_t  ( *func_vars_get_value_t )         ( ENUM_VALUE_NAME value_name, value_pack_t *p_value );

///< Указатель на функцию установки значения
typedef int32_t  ( *func_vars_set_value_t )         ( ENUM_VALUE_NAME value_name, value_pack_t val );

///< Указатель на функцию получения байт данных
typedef int32_t  ( *func_vars_get_array_t )         ( ENUM_ARRAY_NAME array_name, uint8_t *p_buf, uint32_t buf_sz );

///< Указатель на функцию установки байт данных
typedef int32_t  ( *func_vars_set_array_t )         ( ENUM_ARRAY_NAME array_name, uint8_t *p_array, uint32_t array_sz );

///< Указатель на функцию получения даты времени
typedef int32_t  ( *func_vars_get_date_time_t )     ( prop_dt_t *p_date_time );

///< Указатель на функцию установки даты времени
typedef int32_t  ( *func_vars_set_date_time_t )     ( prop_dt_t *p_date_time );



///< Тип данных, который описывает интерфейс работы с переменными
typedef struct
{
  func_vars_init_t              vars_init;
  func_vars_get_alarm_status_t  vars_get_alarm_status;
  func_vars_set_alarm_status_t  vars_set_alarm_status;
  func_vars_get_setpoint_t      vars_get_setpoint;
  func_vars_set_setpoint_t      vars_set_setpoint;
  func_vars_get_value_t         vars_get_value;
  func_vars_set_value_t         vars_set_value;
  func_vars_get_array_t         vars_get_array;
  func_vars_set_array_t         vars_set_array;
  func_vars_get_date_time_t     vars_get_date_time;
  func_vars_set_date_time_t     vars_set_date_time;  
}
kw_proto_vars_interface_t;


extern kw_proto_vars_interface_t* p_vars;


/**
  * @brief  Упаковать уставку. Вычитывается уставка и упаковывается в формат протокола
  * @param  setpoint_name: имя уставки.
  * @retval бинарный образ уставки.
  */    
uint32_t kw_proto_vars_pack_setpoint( ENUM_SETPOINT_NAME setpoint_name );


/**
  * @brief  Распаковать уставку. 
  * @param  setpoint_name: имя уставки.
  * @param  paked_value: бинарный образ уставки.
  * @retval 0 - все хорошо, != 0 - проблемы
  */    
int32_t kw_proto_vars_unpack_setpoint( ENUM_SETPOINT_NAME setpoint_name, uint32_t paked_value );

/**
  * @brief  Упаковать велечина. Вычитывается велечина и упаковывается в формат протокола
  * @param  value_name: имя велечины.
  * @retval бинарный образ велечина.
  */    
uint32_t kw_proto_vars_pack_value( ENUM_VALUE_NAME value_name );

/**
  * @brief  Распаковать велечину. 
  * @param  value_name: имя велечины.
  * @param  paked_value: бинарный образ велечины.
  * @retval 0 - все хорошо, != 0 - проблемы
  */    
int32_t kw_proto_vars_unpack_value( ENUM_VALUE_NAME value_name, uint32_t packed_value );



#ifdef __cplusplus
}
#endif

#endif
