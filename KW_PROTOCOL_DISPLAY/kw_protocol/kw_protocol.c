#include "kw_proto_cfg.h"
#include "kw_protocol.h"


#if( KW_PROTO_MODULE == KW_POWER_MODULE )
  #include "kw_proto_module_power.h"
#elif( KW_PROTO_MODULE == KW_DISPLAY_MODULE )
  #include "kw_proto_module_display.h"
#elif( KW_PROTO_MODULE == KW_KIP6_MODULE )
  #include "kw_proto_module_kip6.h"
#else
  #error
#endif



///< указатель на интерфейс модуля
static kw_proto_module_interface_t *p_mod;

void kw_proto_init()
{
	// инициализация ног CAN
	kw_can_gpio_init( KW_CAN_PROTO_CHANNEL );

	// инициализация перефирии CAN и связанного с ним переменных
	kw_can_module_init( KW_CAN_PROTO_CHANNEL, KW_CAN_PROTO_BAUD );
    
#if( KW_PROTO_MODULE == KW_POWER_MODULE )
  p_mod = &mod_power_inerface;
#elif( KW_PROTO_MODULE == KW_DISPLAY_MODULE )
  p_mod = &mod_display_inerface;
#elif( KW_PROTO_MODULE == KW_KIP6_MODULE )
  p_mod = &mod_kip6_inerface;
#endif
  
  p_mod->mod_init();
}


uint32_t kw_proto_listen()
{
	kw_can_msg_t msg_can;  
  
  // получение и обработка сообщения can
  if( kw_can_get_rx_msg( KW_CAN_PROTO_CHANNEL, &msg_can ) )
  {		
		p_mod->mod_msg_develope( &msg_can );
    
    return 1;
  }
    
  return 0;
}



uint32_t kw_proto_tick_operate()
{  
  return p_mod->mod_tick_operate(); 
}



uint32_t kw_proto_special_operation( PROTO_SPC_OPERATION_ENUM operation, uint32_t param )
{  
  return p_mod->mod_special_operation( operation, param );
}

