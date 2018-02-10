/*
 * POVButton.h
 *
 *  Created on: Feb 23, 2016
 *      Author: troym
 */

//this class is utilized to convert the POV hat on a logitech joystick (or any joystick with a
//POV) from a degree input (0-360) to a boolean input (center == false, anything else == true)
#ifndef SRC_POVBUTTON_H_
#define SRC_POVBUTTON_H_

#pragma once
#include <Buttons/Button.h>
#include <Joystick.h>
#include <WPILib.h>

class POVButton : public Button
{
private:
	Joystick* stick;
	int axis;

public:
	POVButton(Joystick *joystick, int rawAxis) ://stick port and axis number of the POV
		stick(joystick), axis(rawAxis) {}

	bool Get();
};


#endif /* SRC_POVBUTTON_H_ */
