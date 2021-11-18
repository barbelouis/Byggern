/**
 * \file game.c
 * \brief Game implementation
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */
#include "game.h"
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
#include "motor_driver.h"

static struct input_user
{
    int joystick_x;
    int joystick_y;
    int left_slider;
    int right_slider;
    int button;
} input;

/**
 * \fn void set_new_user_input(int joystick_x, int joystick_y, int left_slider, int right_slider, int button)
 * \brief Set the new user input
 * \param joystick_x
 * \param joystick_y
 * \param left_slider
 * \param right_slider
 * \param button
 */
void set_new_user_input(int joystick_x, int joystick_y, int left_slider, int right_slider, int button)
{
    input.joystick_x = joystick_x;
    input.joystick_y = joystick_y;
    input.left_slider = left_slider;
    input.right_slider = right_slider;
    input.button = button;
}

/**
 * \fn void game()
 * \brief Game: mapping sensors and actuators
 */
void game()
{
    printf("X: %d | Y: %d | L: %d | R: %d | button: %d\n\r", input.joystick_x, input.joystick_y, input.left_slider, input.right_slider, input.button);
    servo_map(input.joystick_x);
    if (input.button == 0x1)
    {
        solenoid_hit();
        printf("HIT\n\r");
    }
    int speed = 0;
    motor_PID(input.left_slider, get_range()); //0x21e7
                                               /*
   if (input.joystick_x>170){
       speed = map(input.joystick_x,170,255,0,1200);
   }
   else{
       speed = map(input.joystick_x,0,170,-1200,0);
   }
   //int speed = map(input.joystick_x,0,255,-1800,1800);
   motor_drive(speed);*/
    if (ADC_boolean_read())
    {
        //printf("GOAL!\n\r");
        //can_send(&can_msg, 0);
    }
}