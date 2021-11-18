/**
 * \file main.c
 * \brief main of node2
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include <stdio.h>
#include <stdarg.h>
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf-stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "motor_driver.h"
#include "ADC_driver.h"
#include "encoder_driver.h"
#include "delay.h"
#include "pid_controller.h"
#include "solenoid_driver.h"
#include "servo_driver.h"
#include "game.h"
//#include <time.h>

/**
 * \fn main()
 * \brief main of the project
 */
int main()
{

  WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

  SystemInit();

  configure_uart();
  printf("=====RESET=====\n\r");

  uint32_t baud_rate = 0x00290165;
  can_init_def_tx_rx_mb(baud_rate);

  CAN_MESSAGE can_msg; //or malloc
  //can_msg->data[0] = 0xFF;
  can_msg.data[0] = 0x01;
  can_msg.id = 0x41;
  can_msg.data_length = 1;

  soleonid_init();
  motor_init();
  encoder_init();
  timer_init();
  servo_init();
  //motor_calibration();
  timer_enable();
  ADC_init();

  //uint32_t range = motor_calibration();
  //encoder_reset();
  //printf("Range: %x\n\r", range);
  //delayms(1500);
  //motor_go_to(0x1200,0x2200,0xff);
  //motor_drive_left();
  //time_t now = time(0); // Get the system time
  while (1)
  {
   
    if (ADC_boolean_read())
    {
        printf("GOAL!\n\r");
        can_send(&can_msg, 0);
    }
      //delayms(1000);
      //solenoid_hit();
      //printf("HIT\n\r");
      //printf("message sent\n\r");

      //can_send(&can_msg, 0);
      //printf("Message sent\n\r");
      //printf("Range: %x\n\r", range);
      //motor_PID(30, range);
      //PID_controller(30, range);
      //delayms(500);
      // now = time(0);
      //printf("time %d\n\r", now);

      //ADC_get_value();
  }
}