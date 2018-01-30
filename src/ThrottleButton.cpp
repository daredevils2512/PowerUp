#include "ThrottleButton.h"


bool ThrottleButton::Get() {
	float axisValue = stick->GetRawAxis(axis); //get trigger value
	bool pressed = false;

	if(axisValue < 0.7) {
		pressed = true;
	}else{
		pressed = false;
	}
	return pressed;
}
