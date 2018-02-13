/*
 * POVButton.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: troym
 */
#include "POVButton.h"

//if the POV is not on the center (-1), return as a button is pressed (true)
bool POVButton::Get() {
	if(stick->GetPOV(axis) == -1) {
		return false;
	}else{
		return true;
	}
}
