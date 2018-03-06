#ifndef SRC_THROTTLEBUTTON_H_
#define SRC_THROTTLEBUTTON_H_

#pragma once
#ifndef __GNUC__
#include <Buttons\Button.h>
#else
#include <Buttons/Button.h>
#endif
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
