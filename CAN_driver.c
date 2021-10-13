#include "/home/louis/Documents/NTNU/TTK4155/Byggern/MCP2515_driver.h"
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/CAN_driver.h"
#include <util/delay.h>  
#include <avr/io.h>
#include <stdio.h>

void CAN_init(){

    //set the MCP2515 in loopback mode
    MCP2515_bit_modify(MCP_CANCTRL,0b11100000,0b01000000); //Set REQOP0=0, REQOP1=1, REQOP2=0 
}

void CAN_send(struct Message message){
    //MCP2515_write(uint8_t address, int lenght, char* data )
}

struct Message CAN_receive(){

}