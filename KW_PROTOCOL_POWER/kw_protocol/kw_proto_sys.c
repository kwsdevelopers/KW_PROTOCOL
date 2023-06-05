
#include "kw_protocol.h"
#include "kw_proto_sys.h"
#include "kw_proto_structs.h"
#include "string.h"
#include "kw_proto_pack_unpack.h"


//#define 

#define MAX_TP_DT   256     // 1785


/* PGN: 0x00EC00 - Storing the Transport Protocol Connection Management from the reading process */
typedef struct TP_CM 
{
	uint8_t control_byte;							/* What type of message are we going to send */
	uint16_t total_message_size;					/* Total bytes our complete message includes - 9 to 1785 */
	uint8_t number_of_packages;						/* How many times we are going to send packages via TP_DT - 2 to 224 because 1785/8 is 224 rounded up */
	uint32_t PGN_of_the_packeted_message;			/* Our message is going to activate a PGN */
	uint8_t from_ecu_address;						/* From which ECU came this message */
}
tp_cm_t;

/* PGN: 0x00EB00 - Storing the Transport Protocol Data Transfer from the reading process */
typedef struct TP_DT 
{
	uint8_t sequence_number;						/* When this sequence number is the same as number_of_packages from TP_CM, then we have our complete message */
	uint8_t data[ MAX_TP_DT ];					/* This is the collected data we are going to send. Also we are using this as a filler */
	uint8_t from_ecu_address;						/* From which ECU came this message */
}
tp_dt_t;



typedef struct 
{
	/* Temporary store the information from the reading process - SAE J1939 */
	tp_cm_t from_other_ecu_tp_cm;
	tp_dt_t from_other_ecu_tp_dt;

	/* Temporary hold this values for this ECU when we are going to send data */
	tp_cm_t this_ecu_tp_cm;
	tp_dt_t this_ecu_tp_dt;
}
ecu_t;

ecu_t this;


static void kw_proto_sys_prepare_msg( kw_can_msg_t *p_msg, ENUM_PGN_CODES pgn, uint8_t DA, uint8_t prio ) 
{
  proto_id_t *p_id;
	
	p_id = ( proto_id_t *)&p_msg->id;  
  
  p_id->id = 0;
  p_id->broadcast_id.PGN = pgn;
  p_id->broadcast_id.priority = prio;  

  p_id->broadcast_id.SA = OWN_ADDR;

  p_id->addr_id.DA = DA;

  p_msg->id_type = KW_CAN_ID_EXTENDED;
  p_msg->frame_type = KW_CAN_TFT_DATA;
  
  p_msg->dlc = 8;
  
	memset( &p_msg->data[ 0 ], 0xFF, sizeof( p_msg->data ) ); 
}



void kw_proto_sys_init( void )
{
  memset( &this, 0, sizeof( this ) );
    
}


void kw_proto_sys_ack_unpack( kw_can_msg_t *p_msg )
{
  
  
  
}


void kw_proto_sys_ack_pack_and_send( uint8_t DA, uint8_t control_byte, uint8_t group_function_value, uint32_t PGN_of_requested_info )
{
  kw_can_msg_t msg;
  sys_ack_t *p_msg_data;
  
  kw_proto_sys_prepare_msg( &msg, PGN_ACK, DA, 6 );
  
  p_msg_data = (sys_ack_t *)&msg.data[ 0 ];

	p_msg_data->data_bits.control_word = control_byte;
	p_msg_data->data_bits.group_func = group_function_value;
	p_msg_data->data_bits.requester_addr = DA;				
	p_msg_data->data_bits.pgn = PGN_of_requested_info;
  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}


void kw_proto_sys_request_unpack( kw_can_msg_t *p_msg )
{
  
  
}


void kw_proto_sys_request_pack_and_send( uint8_t DA, uint32_t pgn )
{
  kw_can_msg_t msg;
  sys_request_t *p_msg_data;
  
  
  kw_proto_sys_prepare_msg( &msg, PGN_REQUEST, DA, 6 );

  msg.dlc = 3;
  p_msg_data = (sys_request_t *)&msg.data[ 0 ];
  
  p_msg_data->data_bits.pgn = pgn;

  
	kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );    
}



void kw_proto_sys_tp_cm_unpack( kw_can_msg_t *p_msg )
{
  sys_tp_cm_t *p_msg_data;

  proto_id_t *p_id;
	
	p_id = ( proto_id_t *)&p_msg->id;  
  
  // копируем данные во внутреннюю память и формируем пакет tpcm
  memset( &this.from_other_ecu_tp_cm, 0, sizeof( this.from_other_ecu_tp_cm ) );
  memset( &this.from_other_ecu_tp_dt, 0, sizeof( this.from_other_ecu_tp_dt ) );  

  p_msg_data = ( sys_tp_cm_t *)&p_msg->data[ 0 ];;

	this.from_other_ecu_tp_cm.control_byte = p_msg_data->data_bits.control_word;							
	this.from_other_ecu_tp_cm.total_message_size = p_msg_data->data_bits.msg_total_len;				
	this.from_other_ecu_tp_cm.number_of_packages = p_msg_data->data_bits.pkg_numbers;					
	this.from_other_ecu_tp_cm.PGN_of_the_packeted_message = p_msg_data->data_bits.pgn;
	this.from_other_ecu_tp_cm.from_ecu_address = p_id->broadcast_id.SA;
}


void kw_proto_sys_tp_cm_pack_and_send( uint8_t DA, uint16_t PGN, uint8_t *p_data, uint16_t sz_data)
{
  kw_can_msg_t msg;
  sys_tp_cm_t *p_msg_data;
  
  // копируем данные во внутреннюю память и формируем пакет tpcm
  memset( &this.this_ecu_tp_cm, 0, sizeof( this.this_ecu_tp_cm ) );
  memset( &this.this_ecu_tp_dt, 0, sizeof( this.this_ecu_tp_dt ) );  
  
  // копируем данные во внутренние буфера 
  memcpy( &this.this_ecu_tp_dt.data[ 0 ], p_data, sz_data );
  this.this_ecu_tp_cm.total_message_size = sz_data;
 
	this.this_ecu_tp_cm.number_of_packages = this.this_ecu_tp_cm.total_message_size % 7 > 0 ? this.this_ecu_tp_cm.total_message_size/7 + 1 : this.this_ecu_tp_cm.total_message_size/7; 
	this.this_ecu_tp_cm.PGN_of_the_packeted_message = PGN;
	this.this_ecu_tp_cm.control_byte = DA == 0xFF ? CONTROL_BYTE_TP_CM_BAM : CONTROL_BYTE_TP_CM_RTS;  

  kw_proto_sys_prepare_msg( &msg, PGN_TP_CM, DA, 6 );

  p_msg_data = (sys_tp_cm_t *)&msg.data[ 0 ];
  
  p_msg_data->data_bits.control_word = this.this_ecu_tp_cm.control_byte;
  p_msg_data->data_bits.msg_total_len = this.this_ecu_tp_cm.total_message_size;
  p_msg_data->data_bits.pkg_numbers = this.this_ecu_tp_cm.number_of_packages;
  p_msg_data->data_bits.reserved = 0xFF;
  p_msg_data->data_bits.pgn = this.this_ecu_tp_cm.PGN_of_the_packeted_message;
  
  kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
}

void kw_proto_sys_tp_dt_unpack( kw_can_msg_t *p_msg )
{
	uint8_t i;
	uint8_t index;
	uint32_t PGN;

  
  	// Save the sequence data 
	this.from_other_ecu_tp_dt.sequence_number = p_msg->data[0];
//	this.from_other_ecu_tp_dt.from_ecu_address = SA;
	index = p_msg->data[0] - 1;
	for (i = 1; i < 8; i++)
		this.from_other_ecu_tp_dt.data[index*7 + i-1] = p_msg->data[i]; // For every package, we send 7 bytes of data where the first byte data[0] is the sequence number 


	// Check if we have completed our message - Return = Not completed 
	if( this.from_other_ecu_tp_cm.number_of_packages != this.from_other_ecu_tp_dt.sequence_number || this.from_other_ecu_tp_cm.number_of_packages == 0)
		return;

	PGN = this.from_other_ecu_tp_cm.PGN_of_the_packeted_message;

  
  // Check what type of function that message want this ECU to do 
	switch (PGN) 
  {
    // ff40 setpoints
    case PGN_PROP_SETPOINTS:
      kw_proto_prop_setpoints_unpack( &this.from_other_ecu_tp_dt.data[0] );
      break;
      
    default: return;    
  }
  
}


void kw_proto_sys_tp_dt_send( uint8_t DA )
{
  // формируем пакеты из внктренних данных и кидаем в шину
  kw_can_msg_t msg;
  uint8_t i, j;
	uint16_t bytes_sent = 0;

  kw_proto_sys_prepare_msg( &msg, PGN_TP_DT, DA, 7 );

	for(i = 1; i <= this.this_ecu_tp_cm.number_of_packages; i++) 
  {
		msg.data[ 0 ] = i;   // Number of package 
		
    for( j = 0; j < 7; j++ )
    {
			if( bytes_sent < this.this_ecu_tp_cm.total_message_size )
				msg.data[ j + 1 ] = this.this_ecu_tp_dt.data[ bytes_sent++ ];					// Data that we have collected 
			 else
				msg.data[ j + 1 ] = 0xFF; 														// Reserved 
    }

    kw_can_put_tx_msg( KW_CAN_PROTO_CHANNEL, &msg );  
	}
  
}


















