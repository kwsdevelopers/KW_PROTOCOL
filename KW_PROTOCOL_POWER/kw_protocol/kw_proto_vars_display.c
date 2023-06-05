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
    case SETPOINT_OUT_VOLTAGE:                               // ������� ������������ �������� ��������� ����������
      p_value->val_float = 119.5F;
      break;
    case SETPOINT_MEASURED_OUT_VOLTAGE:                      //  ���������� �������� ��������� ����� ����� ��� ������� ������������� �������������
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_VOLTAGE:            // ������������� ����������� ��������� ����������
      break;
    case SETPOINT_DEVIATION_OUT_VOLTAGE:                     // ���������� ���������� ��������� ���������� �� ������������ ��������
      break;
    case SETPOINT_OUT_CURRENT:                               // ������� ������������ �������� ��������� ����
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_A:              // ���������� �������� ��������� ���� � ���� � ��� ������� �������������� ������������
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_B:              // ���������� �������� ��������� ���� � ���� B ��� ������� �������������� ������������
      break;
    case SETPOINT_MEASURED_OUT_CURRENT_PHASE_C:              // ���������� �������� ��������� ���� � ���� C ��� ������� �������������� ������������
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_A:    // ������������� ����������� ��������� ���� � ���� �
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_B:    // ������������� ����������� ��������� ���� � ���� B
      break;
    case SETPOINT_CALIBRATION_FACTOR_OUT_CURRENT_PHASE_C:    // ������������� ����������� ��������� ���� � ���� C
      break;
    case SETPOINT_OUT_FREQUENCY:                             // ������� ������������ �������� ������� ��������� ����������
      break;
    case SETPOINT_DEVIATION_OUT_FREQUENCY:                   // ���������� ���������� ������� ��������� ���������� �� ������������ ��������
      break;
    case SETPOINT_OUT_COS_MAX:                               // ������� ������������� �������� cos? �� ������ ���
      break;
    case SETPOINT_OUT_POWER:                                 // ������� ������������ �������� �������� ��������
      break;
    case SETPOINT_TIME_EXCEED_100_PERCENT_OUT_POWER:         // ���������� ����� ���������� 100% �������� ��������
      break;
    case SETPOINT_FIRST_THRESHHOLD_OUT_POWER:                // ������ ����� ���������� �������� �������� � %
      break;
    case SETPOINT_TIME_EXCEED_FIRST_THRESHHOLD_OUT_POWER:    // ���������� ����� ���������� ������� ������ �������� ��������
      break;
    case SETPOINT_SECOND_THRESHHOLD_OUT_POWER:               // ������ ����� ���������� �������� �������� � %
      break;
    case SETPOINT_TIME_EXCEED_SECOND_THRESHHOLD_OUT_POWER:   // ���������� ����� ���������� ������� ������ �������� ��������
      break;
    case SETPOINT_OUT_PEAK_CURRENT:                          // ������� ������������� �������� ��������� ����
      break;
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // ������� ���� ��������� ��������� � ������ BYPASS (�� ��������� 16 �)
      break;
    case SETPOINT_COOLER_KKM_MAX_TEMP:                       // ������� ������������ ����������� ���������� ���
      break;
    case SETPOINT_COOLER_INVERTER_MAX_TEMP:                  // ������� ������������ ����������� ���������� ���������
      break;
    case SETPOINT_BATTERY_MAX_TEMP:                          // ������� ������������ ����������� �������
      break;
    case SETPOINT_INBOX_AIR_MAX_TEMP:                        // ������� ������������ ����������� ������� ������ ������� ���
      break;
    case SETPOINT_BATTERY_MIN_VOLTAGE:                       // ������� ������������ ����������� ���������� ���
      break;
    case SETPOINT_BATTERY_MAX_VOLTAGE:                       // ������� ������������� ����������� ���������� ���
      break;
    case SETPOINT_MEASURED_VOLTAGE_BATTERY:                  // ���������� �������� ���������� ��� ��� ������� ������������� �������������
      break;
    case SETPOINT_TEMP_COEFFICIENT_BATTERY:                  // ������������� ����������� ���
      break;
    case SETPOINT_MAX_DISCHARGE_CURRENT_BATTERY:             // ������� ������������� ���� ������� ���
      break;
    case SETPOINT_MAX_CHARGE_CURRENT_BATTERY:                // ������� ������������� ���� ������ ���
      break;
    case SETPOINT_MIN_CHARGE_CURRENT_BATTERY:                //������� ������������ ���� ������ ���
      break;
    case SETPOINT_VOLTAGE_CHARGE_BATTERY_CYCLIC_MODE:        // ������� ���������� ������ ��� � ����������� ������ 
      break;
    case SETPOINT_VOLTAGE_CHARGE_BATTERY_BUFFER_MODE:        // ������� ���������� ������ ��� � �������� ������ 	
      break;
    case SETPOINT_MEASURED_CHARGE_CURRENT_BATTERY:           // ���������� �������� ���� ������ ��� ��� ������� ������������� �������������
      break;
    case SETPOINT_CALIBRATION_FACTOR_CHARGE_CURRENT_BATTERY: // ������������� ����������� ���� ������ ���
      break;
    case SETPOINT_MEASURED_CHARGE_VOLTAGE_BATTERY:           // ���������� �������� ���������� ������ ��� ��� ������� ������������� �������������
      break;
    case SETPOINT_CALIBRATION_FACTOR_CHARGE_VOLTAGE_BATTERY: // ������������� ����������� ���������� ������ ���
      break;
    case SETPOINT_CAPACITY_BATTERY:                          // ����������� ������� ���
      break;
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // ������� ������� ������� ����������� �������� ���������� ���
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // ������� ������ ������� ����������� �������� ���������� ���
      break;
    case SETPOINT_IN_VOLTAGE_UNBALANCE_COEFFICIENT:          // ����������� ����������� �� �������� ����������
      break;
    case SETPOINT_IN_CURRENT_MAX:                            // ������� ������������� �������� �������� ���� ���
      break;
    case SETPOINT_IN_CURRENT_UNBALANCE_COEFFICIENT:          // ����������� ����������� �� �������� ����
      break;
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // ������� ������� ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // ������� ������ ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;
    case SETPOINT_MIDDLE_VOLTAGE:                            // ������� ������������ �������� ���������� ������������� ���� ����������� ����
      break;
    case SETPOINT_FUN_1_MAX_SPEED:                           // ������������ �������� ����������� 1
      break;
    case SETPOINT_FUN_2_MAX_SPEED:                           // ������������ �������� ����������� 2
      break;
    case SETPOINT_RES_1_MAX_TEMP:                            // ������� ������������ ����������� ������ 1
      break;
    case SETPOINT_RES_2_MAX_TEMP:                            // ������� ������������ ����������� ������ 2
      break;
    case SETPOINT_RES_3_MAX_TEMP:                            // ������� ������������ ����������� ������ 3
      break;
    case SETPOINT_FUN_RES_1_MAX_SPEED:                       // ������������ �������� ������ 1
      break;
    case SETPOINT_FUN_RES_2_MAX_SPEED:                       // ������������ �������� ������ 2
      break;
    case SETPOINT_FUN_RES_3_MAX_SPEED:                       // ������������ �������� ������ 3
      break;
    case SETPOINT_WORKING_MODE_AFTER_POWER_UP:               // ����� ������ ������ ��� ����� ���������
      break;
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // ������� ����� �������� ������ ������ ��� ��� ������������� ���������� ������� 	
      break;
    case SETPOINT_POWER_LINE_SYNC:                           // ������������� � ������� �����
      break;
    case SETPOINT_BATTERY_RUNTIME_AS_LOW_CHARGE:             // ������� ������� ������ �� �������, ���� ������� ������� ������ ������� ��������� ������
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
    case SETPOINT_OUT_VOLTAGE:                               // 01h ������� ������������ �������� ��������� ����������
      break;     
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // 16h ������� ���� ��������� ��������� � ������ BYPASS (�� ��������� 16 �)
      break;      
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // 41h ������� ������� ������� ����������� �������� ���������� ���
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // 42h ������� ������ ������� ����������� �������� ���������� ���
      break;    
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // 2Eh ������� ������� ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // 2Fh ������� ������ ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;    
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // 3Ah ������� ����� �������� ������ ������ ��� ��� ������������� ���������� ������� 	
      break;

    case SETPOINT_KIP6_IP_ADR:                               // ������� IP ����� ����������
      break;    
    case SETPOINT_KIP6_IP_MASK:                              // ������� IP ����� ����
      break;    
    case SETPOINT_KIP6_IP_GATE:                              // ������� IP ���� ����� ����
      break;    
    case SETPOINT_KIP6_IP_TYPE:                              // ������� ��� IP ��������� 
      break;    
    case SETPOINT_KIP6_MB_ADR:                               // ������� ����� �������������� �� ���� ModBus
      break;    
    case SETPOINT_KIP6_MB_BAUD:                              // ������� �������� �������������� �� ���� ModBus
      break;    
    case SETPOINT_KIP6_IN_1_FUNCTION:                        // ������� ������� ������ �������� ����� 1
      break;    
    case SETPOINT_KIP6_IN_2_FUNCTION:                        // ������� ������� ������ �������� ����� 2
      break;    
    case SETPOINT_KIP6_IN_3_FUNCTION:                        // ������� ������� ������ �������� ����� 3
      break;    
    case SETPOINT_KIP6_IN_4_FUNCTION:                        // ������� ������� ������ �������� ����� 4
      break;    
    case SETPOINT_KIP6_IN_5_FUNCTION:                        // ������� ������� ������ �������� ����� 5
      break;    
    case SETPOINT_KIP6_OUT_1_FUNCTION:                       // ������� ������� ������ �������� ������ 1
      break;    
    case SETPOINT_KIP6_OUT_2_FUNCTION:                       // ������� ������� ������ �������� ������ 2
      break;    
    case SETPOINT_KIP6_OUT_3_FUNCTION:                       // ������� ������� ������ �������� ������ 3
      break;    
    case SETPOINT_KIP6_OUT_4_FUNCTION:                       // ������� ������� ������ �������� ������ 4
      break;    
    case SETPOINT_KIP6_OUT_5_FUNCTION:                       // ������� ������� ������ �������� ������ 5
      break;    
    case SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW:               // ������� ������� ������ �������, ����� ����� �������� ������  
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
    case SETPOINT_OUT_VOLTAGE:                               // 01h ������� ������������ �������� ��������� ����������
      break;     
    case SETPOINT_OUT_SHORT_CIRCUT_CURRENT:                  // 16h ������� ���� ��������� ��������� � ������ BYPASS (�� ��������� 16 �)
      break;      
    case SETPOINT_IN_VOLTAGE_HI_THRESHHOLD:                  // 41h ������� ������� ������� ����������� �������� ���������� ���
      break;
    case SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD:                 // 42h ������� ������ ������� ����������� �������� ���������� ���
      break;    
    case SETPOINT_IN_FREQUENCY_HI_THRESHHOLD:                // 2Eh ������� ������� ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;
    case SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD:               // 2Fh ������� ������ ������� ���������� ������� �������� ����������: % �� ������������ ��������
      break;    
    case SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT:          // 3Ah ������� ����� �������� ������ ������ ��� ��� ������������� ���������� ������� 	
      break;

    case SETPOINT_KIP6_IP_ADR:                               // ������� IP ����� ����������
      break;    
    case SETPOINT_KIP6_IP_MASK:                              // ������� IP ����� ����
      break;    
    case SETPOINT_KIP6_IP_GATE:                              // ������� IP ���� ����� ����
      break;    
    case SETPOINT_KIP6_IP_TYPE:                              // ������� ��� IP ��������� 
      break;    
    case SETPOINT_KIP6_MB_ADR:                               // ������� ����� �������������� �� ���� ModBus
      break;    
    case SETPOINT_KIP6_MB_BAUD:                              // ������� �������� �������������� �� ���� ModBus
      break;    
    case SETPOINT_KIP6_IN_1_FUNCTION:                        // ������� ������� ������ �������� ����� 1
      break;    
    case SETPOINT_KIP6_IN_2_FUNCTION:                        // ������� ������� ������ �������� ����� 2
      break;    
    case SETPOINT_KIP6_IN_3_FUNCTION:                        // ������� ������� ������ �������� ����� 3
      break;    
    case SETPOINT_KIP6_IN_4_FUNCTION:                        // ������� ������� ������ �������� ����� 4
      break;    
    case SETPOINT_KIP6_IN_5_FUNCTION:                        // ������� ������� ������ �������� ����� 5
      break;    
    case SETPOINT_KIP6_OUT_1_FUNCTION:                       // ������� ������� ������ �������� ������ 1
      break;    
    case SETPOINT_KIP6_OUT_2_FUNCTION:                       // ������� ������� ������ �������� ������ 2
      break;    
    case SETPOINT_KIP6_OUT_3_FUNCTION:                       // ������� ������� ������ �������� ������ 3
      break;    
    case SETPOINT_KIP6_OUT_4_FUNCTION:                       // ������� ������� ������ �������� ������ 4
      break;    
    case SETPOINT_KIP6_OUT_5_FUNCTION:                       // ������� ������� ������ �������� ������ 5
      break;    
    case SETPOINT_KIP6_BATTERY_PERCENT_AS_LOW:               // ������� ������� ������ �������, ����� ����� �������� ������  
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
      
      return 35; // ����� 

    case ARRAY_TEST_RESULT_STR:
      // ��������� �������� ���������� ����������� ����� ������ �� 255 ��������

      if( strlen( test_result_str ) > buf_sz )
      {
        return -3;
      }
      
      strcpy( ( char *)p_buf, test_result_str);
      
      return strlen( test_result_str ); // �����     
    
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
///< ��� ������ ��� �������� ����/������� � ������� �� �������
typedef struct 
{
    uint8_t sec;   // ������� 0 - 60
    uint8_t min;   // ������ 0 - 59
    uint8_t hour;  // ���� 0 - 23
    uint8_t mday;  // ���� ������ 1 - 31
    uint8_t mon;   // ����� 1-12
    uint8_t year;  // ���, ������� � 1985 ����: 0-1985, 1-1986
}prop_dt_t;
*/

int32_t kw_vars_display_get_date_time( prop_dt_t *p_date_time )
{ 
  // ��� ����� ��� ��������� � ���6
  
//------------- ����
  p_date_time->sec = 59;   // ������� 0 - 59
  p_date_time->min = 59;   // ������ 0 - 59
  p_date_time->hour = 23;  // ���� 0 - 23
  p_date_time->mday = 24;  // ���� ������ 1 - 31
  p_date_time->mon = 4;   // ����� 1-12
  p_date_time->year = (2023 -1985);  // ���, ������� � 1985 ����: 0-1985, 1-1986
//---------------------------  
  
  return 0;
}

int32_t kw_vars_display_set_date_time( prop_dt_t *p_date_time )
{
  // ����� ��� ����������� �� �������
  
  
  return 0;
}



kw_proto_vars_interface_t vars_display_interface = 
{
  kw_vars_display_init,
  0,
  kw_vars_display_set_alarm_status,                                // �� ���� ������������� ������
  kw_vars_display_get_setpoint,
  kw_vars_display_set_setpoint,
  0,
  kw_vars_display_set_value,                                // �� ���� ������������� �������� ����������
  kw_vars_display_get_array,
  kw_vars_display_set_array,
  kw_vars_display_get_date_time,
  kw_vars_display_set_date_time
};

#endif // ( KW_PROTO_MODULE == KW_DISPLAY_MODULE )



