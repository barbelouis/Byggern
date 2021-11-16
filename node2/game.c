#include "game.h"
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
/*
CAN_MESSAGE can_IR_msg; //or malloc
  //can_msg->data[0] = 0xFF;
  can__IR_msg.data[0] =41;
  can_IR_msg.id = 1;
  can_IR_msg.data_length = 1;
  */
static struct input_user
{
    int joystick_x;
    int joystick_y;
    int left_slider;
    int right_slider;
    int button;
} input;

void set_new_user_input(int joystick_x, int joystick_y, int left_slider, int right_slider, int button)
{
    input.joystick_x = joystick_x;
    input.joystick_y = joystick_y;
    input.left_slider = left_slider;
    input.right_slider = right_slider;
    input.button = button;
}

void game()
{
    printf("X: %d | Y: %d | L: %d | R: %d | button: %d\n\r", input.joystick_x, input.joystick_y,input.left_slider,input.right_slider, input.button);
    servo_map(input.joystick_y);
    if (input.button == 0x1)
    {
        solenoid_hit();
        printf("HIT\n\r");
    }
    motor_PID(input.left_slider, 0x21e7);
    if (ADC_boolean_read()){
        
    }
}