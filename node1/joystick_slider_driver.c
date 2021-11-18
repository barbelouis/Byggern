/**
 * \file joystick_slider_driver.c
 * \brief Joystick and slider driver
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 8 november 2021
 *
 */
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/ADC_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include "/home/louis/Documents/NTNU/TTK4155/Byggern/node1/joystick_slider_driver.h"

/**
 * \fn get_joystick_vertical_analog_position()
 * \brief Get the joystick vertical analog position
 * \return int joystick_vertical_analog_position
 */
int get_joystick_vertical_analog_position()
{
    read_ADC_input();
    return ADC_MAX.input0;
}

/**
 * \fn get_joystick_horizontal_analog_position()
 * \brief Get the joystick horizontal analog position
 * \return int joystick_horizontal_analog_position
 */
int get_joystick_horizontal_analog_position()
{
    read_ADC_input();
    return ADC_MAX.input1;
}

/**
 * \fn char get_joystick_direction()
 * \brief Get the joystick direction
 * \return Return char with the joystick direction | T: Top; B: Bottom; R: Right; L: Left
 */
char get_joystick_direction()
{
    int vertical = get_joystick_vertical_analog_position();
    int horizontal = get_joystick_horizontal_analog_position();

    if (vertical > 225)
    {
        return 'T';
    }
    else if (vertical < 25)
    {
        return 'B';
    }
    else if (horizontal > 230)
    {
        return 'R';
    }
    else if (horizontal < 25)
    {
        return 'L';
    }
    else
    {
        return 'C';
    }
}

/**
 * \fn int get_left_slider_analog_position()
 * \brief Get left slider position
 * \return analog left slider output
 */
int get_left_slider_analog_position()
{
    read_ADC_input();
    return ADC_MAX.input2;
}

/**
 * \fn int get_right_slider_analog_position()
 * \brief Get right slider position
 * \return analog right slider output
 */
int get_right_slider_analog_position()
{
    read_ADC_input();
    return ADC_MAX.input3;
}

/**
 * \fn int get_left_slider_percentage()
 * \brief Get left slider percentage
 * \return Left slider percentage
 */
int get_left_slider_percentage()
{
    return get_left_slider_analog_position() * 100 / 255;
}

/**
 * \fn int get_right_slider_percentage()
 * \brief Get right slider percentage
 * \return Right slider percentage
 */
int get_right_slider_percentage()
{
    return get_right_slider_analog_position() * 100 / 255;
}

/**
 * \fn void print_sensors()
 * \brief Print sensors values
 */
void print_sensors()
{
    printf("========= SENSORS ==========\n");
    printf("JOYSTICK:   %c \n", get_joystick_direction());
    printf("Left slider:     %4d \n", get_left_slider_percentage());
    printf("Right slider:    %4d \n", get_right_slider_percentage());
}

/**
 * \fn int get_joystick_press()
 * \brief Check for joystick press
 */
int get_joystick_press()
{
    return !(PINB & 0x02);
}