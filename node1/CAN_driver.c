#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/CAN_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

//int flag=0;

void CAN_init(){
/*
    DDRD &= ~(1<<PD2);
    */
    MCP2515_init(); //MCP2515 Init
    _delay_ms(1000);
   // MCP2515_bit_modify(MCP_CANINTE,0b00000111,0b00000100); //set conf mod MCP2515_bit_modify(MCP_CANINTE,0b00000111,0b00000100); //set RX0IE to 1

     //tests/
    //MCP2515_write(MCP_CANINTE,1,0b00000011);
   /* MCP2515_bit_modify(MCP_CANINTE,0b00011111,0b00000011); */
    // disable tx interrupt TO DO
    

    //set the MCP2515 in loopback mode
    MCP2515_bit_modify(MCP_CANCTRL,MODE_MASK,MODE_LOOPBACK); //Set REQOP0=0, REQOP1=1, REQOP2=0
    uint8_t value = MCP2515_read ( MCP_CANSTAT);
       // printf("CANSTAT : %d \r\n",value);


        if (( value & MODE_MASK ) != MODE_LOOPBACK ) {
        printf (" MCP2515 is NOT in LoopBack mode after reset !\n");
                return 1;
        }
/*
     //////////////////////////////////////////:
    cli();
    MCUCR |= (1<<ISC01 ) ;
    MCUCR &= ~(1<<ISC00 );
    //MCUCR &= ~(0b11<<ISC00);
    SREG |= (1<<7);

    GICR |= (1<<INT0 ) ;
    
    sei();
    MCP2515_write(MCP_CANINTF,2,0x00);
    ///////////////////////////////////////////
    */

    //MCP2515_bit_modify(MCP_CANINTE,0b00000001,0b00000001); //set RX0IE to 1
   

}

void CAN_send(struct Message message){
    
    //write the id in the associated register
    //MCP2515_write(0x32, 1 , message.id);  // 11 bits => 2 bytes
    //MCP2515_write(0x31, 2 , 0b1111111111100000);
    MCP2515_write(0x31, 1 , 0xff);
    MCP2515_write(0x32, 1 , 0b11100000);
    printf("sent ID: %x\n",message.id);
    //uint8_t= message.id
   // MCP2515_write1(0x31,message.id);
// to sep in two
    //printf("after first write\n");

    //write the lenght in the associated register
    
    MCP2515_write(0x35, 1 , message.length); // 8 bits => 1 byte
    //MCP2515_write1(0x35, message.length);
    printf("sent length: %d\n",message.length);

    //write the data in the associated register 
    //with the good lenght and beeing carefull to consecutive registers
   // for(int i=0; i<message.length;i++){
  //  MCP2515_write(0x36+i, 1 , message.data[i]);
//}
    MCP2515_write(0x36, message.length, message.data);
    
    
    /*
    for (int i=0; i<message.length;i++){
    MCP2515_write1(0x36, message.data);
    }
    */
   // printf("after last write\n");
    // Request to send
    MCP2515_request_send();
    //("after request\n");

    printf("sent message: ");
    for(int i=0; i< message.length; i++){
                    printf("%c",message.data[i]);
                    
                }
    printf("\n\n");
}

void CAN_receive(struct Message *message,int bufferNb){



    //printf("In CAN receive\n");
    //MCP2515_bit_modify(MCP_CANINTF,0b00000001,0b00000001); // set RX0IF to 1

    if(bufferNb==0x1){
        ///////////// read message//////////////////////////////    
    //read ID
    uint16_t id0=MCP2515_read(MCP_RXB0SIDH); // 0x61
    uint16_t id1=MCP2515_read(0x62);
    printf("id0: %x | id1: %x\n",id0,id1);
    uint16_t id = (id1 << 8)|id0; 
    message->id=id; 
    //read data length
    message->length=MCP2515_read(0x65); //0x65
    printf("CAN receive 0 message length: %d\n",message->length);
    //read data
    for(int i=0; i<message->length;i++){
        message->data[i]=MCP2515_read(0x66+i); //0x66
    }
   // MCP2515_bit_modify(MCP_CANINTF,0b00000001,0b00000000); 
   // flag=0;
    }
    else if (bufferNb==0x2){
        ///////////// read message//////////////////////////////    
    //read ID
    uint16_t id0=MCP2515_read(MCP_RXB1SIDH); // 0x71
    uint16_t id1=MCP2515_read(0x72);
    printf("id0: %x | id1: %x\n",id0,id1);
    uint16_t id = (id1 << 8)|id0; 
    message->id=id; 
    //read data length
    message->length=MCP2515_read(0x75); //0x75
    printf("CAN receive 1 message length: %d\n",message->length);
    //read data
    for(int i=0; i<message->length;i++){
        message->data[i]=MCP2515_read(0x76+i); //0x76
    }
//MCP2515_bit_modify(MCP_CANINTF,0b00000010,0b00000000); 
//flag=0;
    }
    
    //printf("%d",MCP_CANINTF);
    //printf("\n");
    
    
    //printf("flag to 0\n");
    //printf("%d",MCP_CANINTF);
    //printf("\n");
}

/*
ISR(INT0_vect){
    flag=1;
}

ISR(BADISR_vect){}
*/