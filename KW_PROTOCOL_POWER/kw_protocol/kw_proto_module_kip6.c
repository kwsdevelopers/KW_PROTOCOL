#include <stdint.h>
#include <string.h>
#include "kw_can.h"
#include "kw_proto_module_kip6.h"
#include "kw_proto_vars_kip6.h"
#include "kw_proto_pack_unpack.h"
#include "sys_timer.h"
#include "kw_proto_enums.h"
#include "kw_proto_structs.h"
#include "kw_proto_sys.h"
#include "kw_protocol.h"


#if( KW_PROTO_MODULE == KW_KIP6_MODULE )


static int32_t kw_mod_display_unpack_special_cmd( kw_can_msg_t *p_msg )
{
  static uint32_t password_good = 0;
  
  switch( p_msg->data[ 0 ] )
  {

    case SPC_CMD_ENTER_PASSWORD:
      
      if( 0 == kw_proto_password_unpack( p_msg ) )
      {
        password_good = 1;
        return 0;
      }
      else
        return -1;

    case SPC_CMD_WRITE_ID_CARD_1:
    case SPC_CMD_WRITE_ID_CARD_2:
    case SPC_CMD_WRITE_ID_CARD_3:
    case SPC_CMD_WRITE_ID_CARD_4:
    case SPC_CMD_WRITE_ID_CARD_5:

      if( password_good ) // был введен корректный пароль
      {
        int32_t res = kw_proto_write_id_card_unpack( p_msg ); 
        
        if( p_msg->data[ 0 ] == SPC_CMD_WRITE_ID_CARD_5 )
        {
          password_good = 0;
        }
        
        return res;
      }

      return -1;
      
    case SPC_CMD_WRITE_IP_ADR:
      kw_proto_kip6_wr_ip_addr_unpack( p_msg );
      break;

    case SPC_CMD_WRITE_IP_MASK:
      kw_proto_kip6_wr_net_mask_unpack( p_msg );
      break;

    case SPC_CMD_WRITE_IP_GATE:
      kw_proto_kip6_wr_gate_unpack( p_msg );
      break;

    case SPC_CMD_WRITE_IP_TYPE:
      kw_proto_kip6_wr_ip_adressing_type_unpack( p_msg );
      break;

    case SPC_CMD_WRITE_MB_SETTINGS:
      kw_proto_kip6_wr_mb_settings_unpack( p_msg );
      break;

    case SPC_CMD_WRITE_DRY_CONTACTS_SETTINGS:
      kw_proto_kip6_wr_dry_settings_unpack( p_msg );
      break;
      
    case SPC_CMD_TEST_START:

      break;
        
    default: return -1;
  }
  
  return 0;
  
}


void kw_mod_kip6_init( void )
{
  kw_vars_kip6_init();
}

uint32_t kw_mod_kip6_msg_develope( kw_can_msg_t *p_msg )
{
  
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;  
  
  if(p_id->addr_id.PDF == 0xEA && ( p_id->addr_id.DA == OWN_ADDR || p_id->addr_id.DA == 0xFF ) && p_msg->dlc == 3 )
  { // request
    sys_request_t *p_msg_data = (sys_request_t *)&p_msg->data[ 0 ];
    
    if( p_msg_data->data_bits.pgn == PGN_PROP_ID_CARD )
    { // id card
      kw_proto_prop_id_card_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_ID_CARD );
    }
    
    else if( p_msg_data->data_bits.pgn == PGN_PROP_IP_ADDR_MASK )    // 0xFF70,
    {
      kw_proto_kip6_prop_rd_ip_mask_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_IP_ADDR_MASK );
      
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_IP_GATE_TYPE )    // 0xFF71,
    {
      kw_proto_kip6_prop_rd_gate_type_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_IP_GATE_TYPE );
      
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_MB_SETTINGS )     // 0xFF72,
    {
      kw_proto_kip6_prop_rd_mb_settings_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_MB_SETTINGS );
      
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_DRY_SETTINGS )    // 0xFF73,
    {
      kw_proto_kip6_prop_rd_dry_conacts_settings_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_DRY_SETTINGS );      
    }
    else
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_NOT_SUPPORTED, GROUP_FUNCTION_VALUE_NO_CAUSE, p_msg_data->data_bits.pgn );  
    }   
        
    return 1;
  }
  else if(p_id->addr_id.PDF == 0xEF && ( p_id->addr_id.DA == OWN_ADDR ) )
  { 
    // secial cmd   
    if( 0 == kw_mod_display_unpack_special_cmd( p_msg ) )
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_SPC_CMD );      
    }
    else
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_ACCESS_DENIED, GROUP_FUNCTION_VALUE_NO_CAUSE, PGN_PROP_SPC_CMD );        
    }    
    
    return 1;
  }
  else if( p_id->addr_id.PDF == 0xEC && ( p_id->addr_id.DA == OWN_ADDR || p_id->addr_id.DA == 0xFF ) && p_msg->dlc == 8  ) 
  { // tp_cm
    kw_proto_sys_tp_cm_unpack( p_msg );    
  }  
  else if( p_id->addr_id.PDF == 0xEB && ( p_id->addr_id.DA == OWN_ADDR || p_id->addr_id.DA == 0xFF ) && p_msg->dlc == 8  ) 
  { // tp_dt
    kw_proto_sys_tp_dt_unpack( p_msg );    
  }    
  else if( p_id->broadcast_id.PGN == PGN_PROP_ALARM_STATUS ) // FF00
  {
    kw_proto_fault_status_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_IN1_VOLTAGE ) // FF01
  {
    kw_proto_in_voltage_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_IN1_CURRENT ) // FF02
  { 
    kw_proto_in_current_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_IN1_FREQENCY ) // FF03
  {
    kw_proto_in_frequency_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_OUT1_VOLTAGE ) // FF11
  { 
    kw_proto_out_voltage_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_OUT1_CURRENT ) // FF12
  {
    kw_proto_out_current_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_OUT_FREQENCY ) // FF1E
  { 
    kw_proto_out_frequency_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_OUT_PHASE_SHIFT ) // FF1F
  { 
    kw_proto_out_phase_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_BYPASS1_VOLTAGE ) // FF21
  {
    kw_proto_bypass_voltage_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_BYPASS1_CURRENT ) // FF22
  {
    kw_proto_bypass_current_unpack( p_msg );    
  }  
  
  else if( p_id->broadcast_id.PGN == PGN_PROP_BYPASS_FREQENCY ) // FF2E
  {
    kw_proto_bypass_frequency_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_BYPASS_PHASE_SHIFT ) // FF2F
  { 
    kw_proto_bypass_phase_unpack( p_msg );    

  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_MIDDLE_VOLTAGE ) // FF31
  {
    kw_proto_prop_middle_voltage_unpack( p_msg );    
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_INVERTER_CURRENT ) // FF32
  { 
      kw_proto_prop_inverter_current_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_BATTERY_VOLTAGE ) // FF33
  {
    kw_proto_prop_battery_voltage_unpack( p_msg ); 
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_BATTERY_STATUS ) // FF34
  { 
    kw_proto_prop_battery_status_unpack( p_msg ); 
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_MODULES_TEMPERATURE ) // FF35
  { 
    kw_proto_prop_modules_temperature_status_unpack( p_msg ); 

  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_FUN_SPEED ) // FF36
  { 
    kw_proto_prop_fun_speed_unpack( p_msg ); 

  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_INVERTER_VOLTAGE ) // FF38
  { 
    kw_proto_inverter_voltage_unpack( p_msg );
  }
  else if( p_id->broadcast_id.PGN == PGN_PROP_IN_STATUS ) // FF0F
  {
    kw_proto_in_status_unpack( p_msg );
  }
  
  
  return 1;
  
}



uint32_t kw_mod_kip6_tick_operate( void )
{
  static uint32_t ticks_1_sec = 0;

  // 1 sec event
	if( ( unsigned )( sys_tick_count - ticks_1_sec) >= 1000 )
	{
    ticks_1_sec = sys_tick_count;
    
    kw_proto_date_time_pack_and_send();     
  }  
  
  return 1;  
}


uint32_t kw_mod_kip6_special_operation( PROTO_SPC_OPERATION_ENUM operation, uint32_t param )
{
  switch (operation)
  {
    case SPC_OP_SEND_REQUEST:
      
      switch( ( PROTO_REQUEST_ENUM )param )
      {      
        case REQUEST_POWER_MODULE_SETPOINTS:
          kw_proto_sys_request_pack_and_send( POWER_MODULE_ADDR, PGN_PROP_SETPOINTS );
          break;  

        case REQUEST_POWER_MODULE_INPUT_LINES_STATUS:  
          kw_proto_sys_request_pack_and_send( POWER_MODULE_ADDR, PGN_PROP_IN_STATUS );
          break;  
          

        default: return 0;
      }

      break;    
    
    case SPC_OP_WRITE_SETPOINT:
      switch( ( PROTO_SETPOINT_ENUM )param )
      {
// надо подумать - скорее всего ничего не будем писать на этом этапе        

        case SETPOINT_POWER_MODULE_OUT_VOLTAGE:                              // Уставка номинального значения выходного напряжения          
          kw_proto_setpoint_pack_and_send( SETPOINT_OUT_VOLTAGE );          
          break;  
          
        case SETPOINT_POWER_MODULE_OUT_SHORT_CIRCUT_CURRENT:                 // Уставка тока короткого замыкания в режиме BYPASS (по умолчанию 16 А)
          kw_proto_setpoint_pack_and_send( SETPOINT_OUT_SHORT_CIRCUT_CURRENT );          
          
          break;    
        case SETPOINT_POWER_MODULE_IN_VOLTAGE_HI_THRESHHOLD:                 // Уставка верхней границы допустимого входного напряжения ИБП
          kw_proto_setpoint_pack_and_send( SETPOINT_IN_VOLTAGE_HI_THRESHHOLD );                    
          break;    
          
        case SETPOINT_POWER_MODULE_IN_VOLTAGE_LOW_THRESHHOLD:                // Уставка нижней границы допустимого входного напряжения ИБП
          kw_proto_setpoint_pack_and_send( SETPOINT_IN_VOLTAGE_LOW_THRESHHOLD );          
          
          break;    
        case SETPOINT_POWER_MODULE_IN_FREQUENCY_HI_THRESHHOLD:               // Уставка верхней границы допустимой частоты входного напряжения: % от номинального значения
          kw_proto_setpoint_pack_and_send( SETPOINT_IN_FREQUENCY_HI_THRESHHOLD );                    
          break;
          
        case SETPOINT_POWER_MODULE_IN_FREQUENCY_LOW_THRESHHOLD:              // Уставка нижней границы допустимой частоты входного напряжения: % от номинального значения
          kw_proto_setpoint_pack_and_send( SETPOINT_IN_FREQUENCY_LOW_THRESHHOLD );                    
          break;
          
        case SETPOINT_POWER_MODULE_SWITCHING_MODES_WHEN_ALARM_EVENT:         // Переход между режимами работы модуля ИБП при возникновении аварийного события 	
          kw_proto_setpoint_pack_and_send( SETPOINT_SWITCHING_MODES_WHEN_ALARM_EVENT );          
          break;
          
        default: return 0;    
      }
    
      break;
      
    case SPC_OP_SWITCH_TO_MODE:
      kw_proto_switch_to_mode_pack_and_send( param );

      break;
      
    default: return 0;    
  }
    
  return 1;
}




kw_proto_module_interface_t mod_kip6_inerface =
{
  kw_mod_kip6_init,
  kw_mod_kip6_msg_develope,
  kw_mod_kip6_tick_operate,
  kw_mod_kip6_special_operation
};

#endif // ( KW_PROTO_MODULE == KW_KIP6_MODULE )

