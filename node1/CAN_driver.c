#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>

//int flag=0;

void CAN_init(){

    //////////////////////////////////////////:

    MCUCR |= (1<<ISC01 ) ;
    MCUCR &= ~(1<<ISC00 );
    SREG |= (1<<7);

    GICR |= (1<<INT0 ) ;
    DDRD &= ~(1<<PIND2);

    ///////////////////////////////////////////
    MCP2515_init(); //MCP2515 Init
    _delay_ms(1000);
   // MCP2515_bit_modify(MCP_CANINTE,0b00000111,0b00000100); //set conf mod MCP2515_bit_modify(MCP_CANINTE,0b00000111,0b00000100); //set RX0IE to 1

    MCP2515_bit_modify(MCP_CANINTE,0b00000011,0b00000011); //set RX0IE to 1
    //set the MCP2515 in loopback mode
    MCP2515_bit_modify(MCP_CANCTRL,0b11100000,0b01000000); //Set REQOP0=0, REQOP1=1, REQOP2=0

    
}

void CAN_send(struct Message message){
    
    //write the id in the associated register
    MCP2515_write(0x31, 2 , message.id);  // 11 bits => 2 bytes
// to sep in two
    printf("after first write\n");

    //write the lenght in the associated register
    
    MCP2515_write(0x35, 1 , message.length); // 8 bits => 1 byte
    

    //write the data in the associated register 
    //with the good lenght and beeing carefull to consecutive registers
    for(int i=0; i<message.length;i++){
    MCP2515_write(0x36+i, 1 , message.data[i]);
    }

    printf("after last write\n");
    // Request to send
    MCP2515_request_send();
    printf("after request\n");
}

void CAN_receive(struct Message *message){



    
    //MCP2515_bit_modify(MCP_CANINTF,0b00000001,0b00000001); // set RX0IF to 1


    ////////////// read message//////////////////////////////    
    //read ID
    uint16_t id0=MCP2515_read(MCP_RXB0SIDH); // 0x61
    uint16_t id1=MCP2515_read(0x62);
    uint16_t id = (id1 << 8)|id0; 
    message->id=id; 
    //read data length
    message->length=MCP2515_read(0x65); //0x65
    //read data
    for(int i=0; i<message->length;i++){
        message->data[i]=MCP2515_read(0x66+i); //0x66
    }
    MCP2515_bit_modify(MCP_CANINTF,0b00000001,0b00000000); 
    flag=0;
}


ISR(INT0_vect){
    flag=1;
}

