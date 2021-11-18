#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H


#include <stdint.h>
int flag;

typedef struct Message
{
    uint16_t id;
    int length;
    //uint8_t data[8];
    uint8_t data[8];
} CAN_MESSAGE;

void CAN_init();
void CAN_send(struct Message message);
void CAN_receive(struct Message *message,int bufferNb);

#endif 