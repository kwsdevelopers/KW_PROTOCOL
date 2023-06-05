#include <stdint.h>
#include <string.h>
#include "kw_can.h"
#include "kw_proto_module_power.h"
#include "kw_proto_vars_power.h"
#include "kw_proto_pack_unpack.h"
#include "sys_timer.h"
#include "kw_proto_enums.h"
#include "kw_proto_structs.h"
#include "kw_proto_sys.h"

#if( KW_PROTO_MODULE == KW_POWER_MODULE )




// 
static int32_t kw_mod_power_unpack_special_cmd( kw_can_msg_t *p_msg )
{
  static uint32_t password_good = 0;
  
  switch( p_msg->data[ 0 ] )
  {
    case SPC_CMD_SWITCH_TO_MODE:
        
      break;
    
    case SPC_CMD_WRITE_SETPOINT:            
      return kw_proto_setpoint_unpack( p_msg );

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
      
    case SPC_CMD_TEST_START:

      break;
        
    default: return -1;
  }
  
  return 0;
  
}



//========================================

void kw_mod_power_init( void )
{
	kw_vars_power_init();
}


uint32_t kw_mod_power_msg_develope( kw_can_msg_t *p_msg )
{
/*  
  	// Read request from other ECU 
		if (id0 == 0x18 && id1 == 0xEA && (DA == j1939->information_this_ECU.this_ECU_address || DA == 0xFF))
			SAE_J1939_Read_Request(j1939, SA, data);
*/
  proto_id_t *p_id = ( proto_id_t *)&p_msg->id;
  
  if(p_id->addr_id.PDF == 0xEA && ( p_id->addr_id.DA == OWN_ADDR || p_id->addr_id.DA == 0xFF ) && p_msg->dlc == 3 )
  { // request
    sys_request_t *p_msg_data = (sys_request_t *)&p_msg->data[ 0 ];
    
    if( p_msg_data->data_bits.pgn == PGN_PROP_SETPOINTS )
    {
      // уставки
      kw_proto_prop_setpoints_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_SETPOINTS );
      
      return 1;
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_ID_CARD )
    { // id card
      kw_proto_prop_id_card_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_ID_CARD );
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_TEST_RESULT_DETAIL )
    { // id card
      kw_proto_prop_test_result_str_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_TEST_RESULT_DETAIL );
    }
    else if( p_msg_data->data_bits.pgn == PGN_PROP_IN_STATUS )
    { // in status
      kw_proto_in_status_pack_and_send();
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_TEST_RESULT_DETAIL );
    }
    
    else
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_NOT_SUPPORTED, GROUP_FUNCTION_VALUE_NO_CAUSE, p_msg_data->data_bits.pgn );  
    }
    
    
    
  }
  if(p_id->addr_id.PDF == 0xEF && ( p_id->addr_id.DA == OWN_ADDR ) )
  { 
    // secial cmd
    
    if( 0 == kw_mod_power_unpack_special_cmd( p_msg ) )
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_SUPPORTED, GROUP_FUNCTION_VALUE_NORMAL, PGN_PROP_SPC_CMD );      
    }
    else
    {
      kw_proto_sys_ack_pack_and_send( p_id->addr_id.SA, CONTROL_BYTE_ACKNOWLEDGEMENT_PGN_ACCESS_DENIED, GROUP_FUNCTION_VALUE_NO_CAUSE, PGN_PROP_SPC_CMD );        
    }
    
  }
  
  return 1;
}



uint32_t kw_mod_power_tick_operate( void )
{
	
	static uint32_t ticks_0_5_sec = 0;
	static uint32_t ticks_5_sec = 0;
	
	// 0.5 sec event
	if( ( unsigned )( sys_tick_count - ticks_0_5_sec) >= 500 )
	{
		ticks_0_5_sec = sys_tick_count;
		
    // FF00
    kw_proto_fault_status_pack_and_send();
    
    // FF01
		kw_proto_in_voltage_pack_and_send( IN_CHANNEL_1 );

    // FF02
    kw_proto_in_current_pack_and_send( IN_CHANNEL_1 );
    
    // FF03
    kw_proto_in_frequency_pack_and_send( IN_CHANNEL_1 );
		
    // FF11
    kw_proto_out_voltage_pack_and_send( OUT_CHANNEL_1 );

    // FF12
    kw_proto_out_current_pack_and_send( OUT_CHANNEL_1 );
    
    // FF1E    
    kw_proto_out_frequency_pack_and_send();

    // FF1F
    kw_proto_out_phase_pack_and_send();
    
    // FF21
    kw_proto_bypass_voltage_pack_and_send( BYPASS_CHANNEL_1 );

    // FF22    
    kw_proto_bypass_current_pack_and_send( BYPASS_CHANNEL_1 );
    
    // FF2E
    kw_proto_bypass_frequency_pack_and_send();
    
    // FF2F
    kw_proto_bypass_phase_pack_and_send();

    // FF31
    kw_proto_prop_middle_voltage_pack_and_send();
      
    // FF32      
    kw_proto_prop_inverter_current_pack_and_send();

    // FF33
    kw_proto_prop_battery_voltage_pack_and_send();
    
    // FF34
    kw_proto_prop_battery_status_pack_and_send();

    // FF38
    kw_proto_inverter_voltage_pack_and_send();

//    kw_proto_prop_setpoints_pack_and_send(); 

//    for ( int i = 0; i < 50000; i++ ); //     
	}
	
	
	// 5 sec event
	if( ( unsigned )( sys_tick_count - ticks_5_sec) >= 5000 )
	{
		ticks_5_sec = sys_tick_count;
    
//    kw_proto_prop_setpoints_pack_and_send();    

    // FF35
    kw_proto_prop_modules_temperature_status_pack_and_send();
    
    // FF36
    kw_proto_prop_fun_speed_pack_and_send();
	}
	
  
  return 1;  
}

uint32_t kw_mod_power_special_operation( PROTO_SPC_OPERATION_ENUM operation, uint32_t param )
{
    
  return 1;
}





kw_proto_module_interface_t mod_power_inerface =
{
  kw_mod_power_init,
  kw_mod_power_msg_develope,
  kw_mod_power_tick_operate
};

#endif //( KW_PROTO_MODULE == KW_POWER_MODULE )

