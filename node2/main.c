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
//#include <time.h>

//extract https://stackoverflow.com/questions/7004743/unable-to-link-to-gettimeofday-on-embedded-system-elapsed-time-suggestions

// en extract

int main()
{

  SystemInit();

  WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

  configure_uart();
  printf("=====RESET=====\n\r");

  uint32_t baud_rate = 0x00290165;
  can_init_def_tx_rx_mb(baud_rate);

  //char x = 'T';

  /*uint16_t id =0x0003;
	char data_length = '1';
	char data[0] = {'Z'};
	*/

  CAN_MESSAGE can_msg; //or malloc
  //can_msg->data[0] = 0xFF;
  can_msg.data[0] = 'Z';
  can_msg.id = 3;
  can_msg.data_length = 1;

  motor_init();
  encoder_init();
  uint32_t range = motor_calibration();
  //encoder_reset();
  printf("Range: %x\n\r", range);
  delayms(1500);
  //motor_go_to(0x1200,0x2200,0xff);
  //motor_drive_left();
  //time_t now = time(0); // Get the system time
  while (1)
  {
    //printf("message sent\n\r");

    //can_send(&can_msg, 0);
    //printf("Message sent\n\r");
    motor_PID(30, range);
    //PID_controller(30, range);
    delayms(500);
   // now = time(0);
    //printf("time %d\n\r", now);

    //ADC_get_value();
  }
}

/* SERVO RELATED

 

  //double current_pulsewidth = servo_init();

  //servo_angle(45);
  //servo_drive(0.1);
  //float test=mapf(45.0,0.0,180.0,0.05,0.10);
  //long test=mapf(90,0,180,5,10);
  //servo_drive(test);
  //printf("%f\n\r",test);
  //servo_angle(90);
  /*servo_angle(0);*/
//servo_set(0.002);

/// in while:

//servo_drive(0.001);

//servo_angle(180);
//servo_angle(x, current_pulsewidth);

//     		for(double i = 0.002; i >= 0.0009;i -=0.0001){
//    			 servo_set(i);
//    			 delay(300000);
//    		 }

//
// 		duty=0.5;
// 		servo_drive(duty);

/*
		servo_drive(0.5);
		delay(300000);
		servo_drive(0.1);
		delay(300000);
		servo_drive(0.9);
		delay(300000);
		*/

