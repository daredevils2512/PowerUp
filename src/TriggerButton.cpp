 /*
 * TriggerButton.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: troym
 */

#include "TriggerButton.h"

bool TriggerButton::Get(){
	float axisValue = stick->GetRawAxis(axis); //get trigger value
	bool pressed = false;
	//determines if axis is -1 to 0 or 0 to 1
	if(threshold > 0){
		if(axisValue > threshold){ // check if trigger pulled past threshold
			pressed = true;
		}
	}
	else{
		if (axisValue < threshold){ // check if trigger pulled past threshold
			pressed = true;
		}
	}
	return pressed; // return true/false value of trigger
}





