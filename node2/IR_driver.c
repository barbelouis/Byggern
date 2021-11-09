#include "IR_driver.h"
#include "ADC_driver.h"


void IR_init(){
	ADC_init();
	//To complete
	//should init interrupt
	if(ADC_get_boolean){
		//send interrupt
		//send IR CAN message to node1
	}
}