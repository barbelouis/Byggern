#include </home/louis/Documents/NTNU/TTK4155/Byggern/ADC_driver.h>
#include <stdio.h>
#include </home/louis/Documents/NTNU/TTK4155/Byggern/joystick_slider_driver.h>


int get_joystick_vertical_analog_position(){
    read_ADC_input();
    return ADC_MAX.input0;
}

int get_joystick_horizontal_analog_position(){
    read_ADC_input();
    return ADC_MAX.input1;
}
char get_joystick_direction(){
    int vertical = get_joystick_vertical_analog_position();
    int horizontal = get_joystick_horizontal_analog_position();
    
    if (vertical > 230){
        return 'T';
    }
    else if (vertical <25){
        return 'B';
    }
    else if (horizontal > 230){
        return 'R';
    }
    else if (horizontal <25){
        return 'L';
    }
    else{
        return 'C';
    }


}
int get_left_slider_analog_position(){
    read_ADC_input();
    return ADC_MAX.input2;
}
int get_right_slider_analog_position(){
    read_ADC_input();
    return ADC_MAX.input3;
}

int get_left_slider_percentage(){
    return get_left_slider_analog_position()*100/255;
}
int get_right_slider_percentage(){
    return get_right_slider_analog_position()*100/255;
}

void print_sensors(){
    printf("========= SENSORS ==========\n");
    printf("JOYSTICK:   %c \n", get_joystick_direction());
    printf("Left slider:     %4d \n", get_left_slider_percentage());
    printf("Right slider:    %4d \n", get_right_slider_percentage());
}