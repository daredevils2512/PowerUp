#ifndef SRC_THROTTLEBUTTON_H_
#define SRC_THROTTLEBUTTON_H_

#pragma once
#include <Buttons\Button.h>
#include <Joystick.h>
#include <WPILib.h>


class ThrottleButton : public Button {
private:
	Joystick* stick; // controller
	int axis; // axis number of trigger
public:
	ThrottleButton(Joystick *joystick, int rawAxis):
		stick(joystick), axis(rawAxis){}
	bool Get();
};

#endif
