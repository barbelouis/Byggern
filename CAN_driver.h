#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H



struct Message
{
    char* id;
    int length;
    char* data;
};

void CAN_init();
void CAN_send(struct Message message);
struct Message CAN_receive();

#endif 