#include "kw_proto_cfg.h"
#include "kw_proto_vars_display.h"
#include "string.h"


#if( KW_PROTO_MODULE == KW_DISPLAY_MODULE )


void kw_vars_display_init( void )
{
  p_vars = &vars_display_interface;
    
}


int32_t kw_vars_display_set_alarm_status( ENUM_ALARM_NAME alarm_name, uint32_t val )
{
  if(alarm_name >= ALARM_MAX )
    return -1;
  
  switch( alarm_name )
  {
    case ALARM_NEUTRAL: break;
    case ALARM_IN_VOLTAGE_PHASE_A_OUT_RANGE: break;
    case ALARM_IN_VOLTAGE_PHASE_B_OUT_RANGE: break;
    case ALARM_IN_VOLTAGE_PHASE_C_OUT_RANGE: break;
    case ALARM_IN_CURRENT_PHASE_A_OUT_RANGE: break;
    case ALARM_IN_CURRENT_PHASE_B_OUT_RANGE: break;
    case ALARM_IN_CURRENT_PHASE_C_OUT_RANGE: break;
    case ALARM_IN_FREQUENCY_PHASE_A_OUT_RANGE: break;
    case ALARM_IN_FREQUENCY_PHASE_B_OUT_RANGE: break;
    case ALARM_IN_FREQUENCY_PHASE_C_OUT_RANGE: break;
    case ALARM_IN_PHASE_SHIFT_PHASE_A_OUT_RANGE: break;
    case ALARM_IN_PHASE_SHIFT_PHASE_B_OUT_RANGE: break;
    case ALARM_IN_PHASE_SHIFT_PHASE_C_OUT_RANGE: break;
    case ALARM_MIDDLE_POSITIVE_VOLTAGE_DOESNT_MATCH_SETPOINT: break;
    case ALARM_MIDDLE_NEGATIVE_VOLTAGE_DOESNT_MATCH_SETPOINT: break;
    case ALARM_OUT_VOLTAGE_PHASE_A_OUT_RANGE: break;
    case ALARM_OUT_VOLTAGE_PHASE_B_OUT_RANGE: break;
    case ALARM_OUT_VOLTAGE_PHASE_C_OUT_RANGE:	 break;
    case ALARM_OUT_CURRENT_PHASE_A_EXCEEED: break;
    case ALARM_OUT_CURRENT_PHASE_B_EXCEEED: break;
    case ALARM_OUT_CURRENT_PHASE_C_EXCEEED: break;
    case ALARM_OUT_SHORT_CIRCUIT_PHASE_A: break;
    case ALARM_OUT_SHORT_CIRCUIT_PHASE_B: break;
    case ALARM_OUT_SHORT_CIRCUIT_PHASE_C: break;
    case ALARM_OUT_POWER_EXCEEED: break;
    case ALARM_OUT_CURRENT_PEAK_PHASE_A_EXCEEED: break;
    case ALARM_OUT_CURRENT_PEAK_PHASE_B_EXCEEED: break;
    case ALARM_OUT_CURRENT_PEAK_PHASE_C_EXCEEED: break;
    case ALARM_OUT_OVER_VOLTAGE_PHASE_A: break;
    case ALARM_OUT_OVER_VOLTAGE_PHASE_B: break;
    case ALARM_OUT_OVER_VOLTAGE_PHASE_C: break;	
    case ALARM_OUT_FREQUENCY_PHASE_A_OUT_RANGE: break;
    case ALARM_OUT_FREQUENCY_PHASE_B_OUT_RANGE: break;
    case ALARM_OUT_FREQUENCY_PHASE_C_OUT_RANGE:	 break;
    case ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_A_OUT_RANGE: break;
    case ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_B_OUT_RANGE: break;
    case ALARM_OUT_VOLTAGE_PHASE_SHIFT_PHASE_C_OUT_RANGE: break;
    case ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_A_OUT_RANGE: break;
    case ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_B_OUT_RANGE: break;
    case ALARM_OUT_CURRENT_PHASE_SHIFT_PHASE_C_OUT_RANGE: break;
    case ALARM_CHARGER_CURRENT_VALUE_DOESNT_MATCH_SETPOINT: break;
    case ALARM_BATTERY_VOLTAGE_OUT_RANGE: break;
    case ALARM_BATTERY_CURRENT_OUT_RANGE: break;
    case ALARM_NO_BATTERY: break;
    case ALARM_BATTERY_DISCHARGE: break;
    case ALARM_TEMPERATURE_KKM_COOLER_EXCEED_SETPOINT: break;
    case ALARM_TEMPERATURE_INVERTER_COOLER_EXCEED_SETPOINT: break;
    case ALARM_TEMPERATURE_BATTERY_EXCEED_SETPOINT: break;
    case ALARM_TEMPERATURE_INBOX_AIR_EXCEED_SETPOINT: break;
    case ALARM_FUN_1_EMERGENCY: break;
    case ALARM_FUN_2_EMERGENCY: break;
    case ALARM_BATTERY_TIME_LESS_SETPOINT: break;
    case ALARM_BATTERY_REPLACEMENT_REQUIRED: break;
    case ALARM_BYPASS_EMERGENCY: break;
  }
  
  
    
  return -2;
}


int32_t kw_vars_display_get_setpoint( ENUM_SETPOINT_NAME setpoint_name, value_pack_t *p_value )
{
  value_pack_t result;
  
  if( setpoint_name >= SETPOINT_MAX )
    return -1;
	
	switch( setpoint_name )
	{
    case SETPOINT_OUT_VOLTAGE:                               // Уставка номинального значения выходного напряжения
      p_value->val_float = 119.5F;
      break;
    case SETPOINT_MEASURED_OUT_VOLTAGE:                      //  Измеренное значение выходного напря жения для расчета калибровочных коэффициентов
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE:            // Калибровочный коэффициент выходного напряжения
      break;
    case SETPOINT_DEVIATION_OUT_VOLTAGE:                     // Допустимое отклонение выходного напряжения от номинального значения
      break;
    case SETPOINT_OUT_CURRENT:                               // Уставка номинального значения выходного тока
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_A:              // Измеренное значение выходного тока в фазе А для расчета калибровочного коэффициента
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_B:              // Измеренное значение выходного тока в фазе B для расчета калибровочного коэффициента
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_C:              // Измеренное значение выходного тока в фазе C для расчета калибровочного коэффициента
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A:    // Калибровочный коэффициент выходного тока в фазе А
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B:    // Калибровочный коэффициент выходного тока в фазе B
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C:    // Калибровочный коэффициент выходного тока в фазе C
      break;
    case SETPOINT_OUT_FREQUENCY:                             // Уставка номинального значения частоты выходного напряжения
      break;
    case SETPOINT_DEVIATION_OUT_FREQUENCY:                   // Допустимое отклонение частоты выходного напряжения от номинального значения
      break;
    case SETPOINT_OUT_COS_MAX:                               // Уставка максимального значения cos? на выходе ИБП
      break;
    case SETPOINT_OUT_POWER:                                 // Уставка номинального значения выходной мощности
      break;
    case SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER:         // Допустимое время превышения 100% выходной мощности
      break;
    case SETPOINT_FIRST_THRESHHOLD_OUT_POWER:                // Первый порог превышения выходной мощности в %
      break;
    case SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER:    // Допустимое время превышения первого порога выходной мощности
      break;
    case SETPOINT_SECOND_THRESHHOLD_OUT_POWER:               // Второй порог превышения выходной мощности в %
      break;
    case SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER:   // Допустимое время превышения второго порога выходной мощности
      break;
    case SETPOINT_OUT_PEAK_CURRENT:                          // Уставка максимального пикового выходного тока
      break;
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
      break;
    case SETPOINT_COOLER_KKM_MAX_TEMP:                       // Уставка максимальной температуры охладителя ККМ
      break;
    case SETPOINT_COOLER_INVERTER_MAX_TEMP:                  // Уставка максимальной температуры охладителя инвертора
      break;
    case SETPOINT_BATTERY_MAX_TEMP:                          // Уставка максимальной температуры батареи
      break;
    case SETPOINT_INBOX_AIR_MAX_TEMP:                        // Уставка максимальной температуры воздуха внутри корпуса ИБП
      break;
    case SETPOINT_BATTERY_MIN_VOLTAGE:                       // Уставка минимального допустимого напряжения АКБ
      break;
    case SETPOINT_BATTERY_MAX_VOLTAGE:                       // Уставка максимального допустимого напряжения АКБ
      break;
    case SETPOINT_MEASURED_VOLTAGE_BATTERY:                  // Измеренное значение напряжения АКБ для расчета калибровочных коэффициентов
      break;
    case SETPOINT_TEMP_COEFFICIENT_BATTERY:                  // Температурный коэффициент АКБ
      break;
    case SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY:             // Уставка максимального тока разряда АКБ
      break;
    case SETPOINT_MAX_CHARGE_CURRENT_BATTERY:                // Уставка максимального тока заряда АКБ
      break;
    case SETPOINT_MIN_CHARGE_CURRENT_BATTERY:                //Уставка минимального тока заряда АКБ
      break;
    case SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE:        // Уставка напряжения заряда АКБ в циклическом режиме 
      break;
    case SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE:        // Уставка напряжения заряда АКБ в буферном режиме 	
      break;
    case SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY:           // Измеренное значение тока заряда АКБ для расчета калибровочных коэффициентов
      break;
    case SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY: // Калибровочный коэффициент тока заряда АКБ
      break;
    case SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY:           // Измеренное значение напряжения заряда АКБ для расчета калибровочных коэффициентов
      break;
    case SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY: // Калибровочный коэффициент напряжения заряда АКБ
      break;
    case SETPOINT_CAPACITY_BATTERY:                          // Номинальная ёмкость АКБ
      break;
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // Уставка верхней границы допустимого входного напряжения ИБП
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // Уставка нижней границы допустимого входного напряжения ИБП
      break;
    case SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT:          // Коэффициент несимметрии по входному напряжению
      break;
    case SETPOINT_IN_CURRENT_MAX:                            // Уставка максимального значения входного тока ИБП
      break;
    case SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT:          // Коэффициент несимметрии по входному току
      break;
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // Уставка верхней границы допустимой частоты входного напряжения: % от номинального значения
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // Уставка нижней границы допустимой частоты входного напряжения: % от номинального значения
      break;
    case SETPOINT_MIDDLE_VOLTAGE:                            // Уставка номинального значения напряжения промежуточной шины постоянного тока
      break;
    case SETPOINT_FUN_1_MAX_SPEED:                           // Максимальная скорость вентилятора 1
      break;
    case SETPOINT_FUN_2_MAX_SPEED:                           // Максимальная скорость вентилятора 2
      break;
    case SETPOINT_RES_1_MAX_TEMP:                            // Уставка максимальной температуры резерв 1
      break;
    case SETPOINT_RES_2_MAX_TEMP:                            // Уставка максимальной температуры резерв 2
      break;
    case SETPOINT_RES_3_MAX_TEMP:                            // Уставка максимальной температуры резерв 3
      break;
    case SETPOINT_FUN_RES_1_MAX_SPEED:                       // Максимальная скорость резерв 1
      break;
    case SETPOINT_FUN_RES_2_MAX_SPEED:                       // Максимальная скорость резерв 2
      break;
    case SETPOINT_FUN_RES_3_MAX_SPEED:                       // Максимальная скорость резерв 3
      break;
    case SETPOINT_WORKING_MODE_AFTER_POWER_UP:               // Режим работы модуля ИБП после включения
      break;
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // Переход между режимами работы модуля ИБП при возникновении аварийного события 	
      break;
    case SETPOINT_POWER_LINE_SYNC:                           // Синхронизация с входной сетью
      break;
    case SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE:             // Уставка времени работы от батареи, ниже которой уровень заряда батареи считается низким
      break;

    default: return -2;
   
  } //switch( setpoint_name )
  
  return 0;  
}

int32_t kw_vars_display_set_setpoint( ENUM_SETPOINT_NAME setpoint_name, value_pack_t val )
{  
  value_pack_t result;
  
  if( setpoint_name >= SETPOINT_MAX )
    return -1;
	
	switch( setpoint_name )
	{
    case SETPOINT_OUT_VOLTAGE:                               // 01h Уставка номинального значения выходного напряжения
      break;     
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // 16h Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
      break;      
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // 41h Уставка верхней границы допустимого входного напряжения ИБП
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // 42h Уставка нижней границы допустимого входного напряжения ИБП
      break;    
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // 2Eh Уставка верхней границы допустимой частоты входного напряжения: % от номинального значения
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // 2Fh Уставка нижней границы допустимой частоты входного напряжения: % от номинального значения
      break;    
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // 3Ah Переход между режимами работы модуля ИБП при возникновении аварийного события 	
      break;

    case SETPOINT_KIP6_IP_ADR:                               // Уставка IP адрес устройства
      break;    
    case SETPOINT_KIP6_IP_MASK:                              // Уставка IP маска сети
      break;    
    case SETPOINT_KIP6_IP_GATE:                              // Уставка IP арес шлюза сети
      break;    
    case SETPOINT_KIP6_IP_TYPE:                              // Уставка тип IP адресации 
      break;    
    case SETPOINT_KIP6_MB_ADR:                               // Уставка адрес устройстваства на шине ModBus
      break;    
    case SETPOINT_KIP6_MB_BAUD:                              // Уставка скорость устройстваства на шине ModBus
      break;    
    case SETPOINT_KIP6_IN_1_FUNCTION:                        // Уставка функция сухого контакта входа 1
      break;    
    case SETPOINT_KIP6_IN_2_FUNCTION:                        // Уставка функция сухого контакта входа 2
      break;    
    case SETPOINT_KIP6_IN_3_FUNCTION:                        // Уставка функция сухого контакта входа 3
      break;    
    case SETPOINT_KIP6_IN_4_FUNCTION:                        // Уставка функция сухого контакта входа 4
      break;    
    case SETPOINT_KIP6_IN_5_FUNCTION:                        // Уставка функция сухого контакта входа 5
      break;    
    case SETPOINT_KIP6_OUT_1_FUNCTION:                       // Уставка функция сухого контакта выхода 1
      break;    
    case SETPOINT_KIP6_OUT_2_FUNCTION:                       // Уставка функция сухого контакта выхода 2
      break;    
    case SETPOINT_KIP6_OUT_3_FUNCTION:                       // Уставка функция сухого контакта выхода 3
      break;    
    case SETPOINT_KIP6_OUT_4_FUNCTION:                       // Уставка функция сухого контакта выхода 4
      break;    
    case SETPOINT_KIP6_OUT_5_FUNCTION:                       // Уставка функция сухого контакта выхода 5
      break;    
    case SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW:               // Уставка процент заряда батареи, когда заряд считаетс низким  
      break;    

    default: return -2;
   
  } //switch( setpoint_name )
  
  return 0;  
}



int32_t  kw_vars_display_set_value( ENUM_VALUE_NAME value_name, value_pack_t value )
{
  value_pack_t result;
  
  if( value_name >= VALUE_MAX )
    return -1;

	
	switch( value_name )
	{
    case SETPOINT_OUT_VOLTAGE:                               // 01h Уставка номинального значения выходного напряжения
      break;     
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // 16h Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
      break;      
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // 41h Уставка верхней границы допустимого входного напряжения ИБП
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // 42h Уставка нижней границы допустимого входного напряжения ИБП
      break;    
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // 2Eh Уставка верхней границы допустимой частоты входного напряжения: % от номинального значения
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // 2Fh Уставка нижней границы допустимой частоты входного напряжения: % от номинального значения
      break;    
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // 3Ah Переход между режимами работы модуля ИБП при возникновении аварийного события 	
      break;

    case SETPOINT_KIP6_IP_ADR:                               // Уставка IP адрес устройства
      break;    
    case SETPOINT_KIP6_IP_MASK:                              // Уставка IP маска сети
      break;    
    case SETPOINT_KIP6_IP_GATE:                              // Уставка IP арес шлюза сети
      break;    
    case SETPOINT_KIP6_IP_TYPE:                              // Уставка тип IP адресации 
      break;    
    case SETPOINT_KIP6_MB_ADR:                               // Уставка адрес устройстваства на шине ModBus
      break;    
    case SETPOINT_KIP6_MB_BAUD:                              // Уставка скорость устройстваства на шине ModBus
      break;    
    case SETPOINT_KIP6_IN_1_FUNCTION:                        // Уставка функция сухого контакта входа 1
      break;    
    case SETPOINT_KIP6_IN_2_FUNCTION:                        // Уставка функция сухого контакта входа 2
      break;    
    case SETPOINT_KIP6_IN_3_FUNCTION:                        // Уставка функция сухого контакта входа 3
      break;    
    case SETPOINT_KIP6_IN_4_FUNCTION:                        // Уставка функция сухого контакта входа 4
      break;    
    case SETPOINT_KIP6_IN_5_FUNCTION:                        // Уставка функция сухого контакта входа 5
      break;    
    case SETPOINT_KIP6_OUT_1_FUNCTION:                       // Уставка функция сухого контакта выхода 1
      break;    
    case SETPOINT_KIP6_OUT_2_FUNCTION:                       // Уставка функция сухого контакта выхода 2
      break;    
    case SETPOINT_KIP6_OUT_3_FUNCTION:                       // Уставка функция сухого контакта выхода 3
      break;    
    case SETPOINT_KIP6_OUT_4_FUNCTION:                       // Уставка функция сухого контакта выхода 4
      break;    
    case SETPOINT_KIP6_OUT_5_FUNCTION:                       // Уставка функция сухого контакта выхода 5
      break;    
    case SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW:               // Уставка процент заряда батареи, когда заряд считаетс низким  
      break;    

		default: return -2;
	}
	  
  return 0;	
}




//---------------------
char test_id_card[] = "12345678901234567890123456789012345";
//---------------------

//---------------------
char test_result_str[] = "This line describes the result of passing the test.";
//---------------------

int32_t kw_vars_display_get_array( ENUM_ARRAY_NAME array_name, uint8_t *p_buf, uint32_t buf_sz )
{
  if( array_name >= ARRAY_MAX )
    return -1;
	
	switch( array_name )
	{
    case ARRAY_ID_CARD: 
      
      if( sizeof( test_id_card ) > buf_sz )
      {
        return -3;
      }
      
      memcpy( p_buf, test_id_card, 35 );
      
      return 35; // длина 

    case ARRAY_TEST_RESULT_STR:
      // текстовое описание результата прохождения теста длиной до 255 символов

      if( strlen( test_result_str ) > buf_sz )
      {
        return -3;
      }
      
      strcpy( ( char *)p_buf, test_result_str);
      
      return strlen( test_result_str ); // длина     
    
    default: return -2;
  }
  
  return 0;
}

int32_t kw_vars_display_set_array( ENUM_ARRAY_NAME array_name, uint8_t *p_array, uint32_t array_sz )
{
  if( array_name >= ARRAY_MAX )
    return -1;
	
	switch( array_name )
	{
    case ARRAY_ID_CARD: 
      
      if( 35 != array_sz )
      {
        return -3;
      }
      
      memcpy( test_id_card, p_array, 35 );
              
      break;
    
    default: return -2;
  }
  
  return 0;
}
/*
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
*/

int32_t kw_vars_display_get_date_time( prop_dt_t *p_date_time )
{ 
  // это время для установки в КИП6
  
//------------- тест
  p_date_time->sec = 59;   // секунды 0 - 59
  p_date_time->min = 59;   // минуты 0 - 59
  p_date_time->hour = 23;  // часы 0 - 23
  p_date_time->mday = 24;  // день месяца 1 - 31
  p_date_time->mon = 4;   // месяц 1-12
  p_date_time->year = (2023 -1985);  // год, начиная с 1985 года: 0-1985, 1-1986
//---------------------------  
  
  return 0;
}

int32_t kw_vars_display_set_date_time( prop_dt_t *p_date_time )
{
  // время для отображения на дисплее
  
  
  return 0;
}



kw_proto_vars_interface_t vars_display_interface = 
{
  kw_vars_display_init,
  0,
  kw_vars_display_set_alarm_status,                                // не надо устанавливать аварии
  kw_vars_display_get_setpoint,
  kw_vars_display_set_setpoint,
  0,
  kw_vars_display_set_value,                                // не надо устанавливать значения переменных
  kw_vars_display_get_array,
  kw_vars_display_set_array,
  kw_vars_display_get_date_time,
  kw_vars_display_set_date_time
};

#endif // ( KW_PROTO_MODULE == KW_DISPLAY_MODULE )



