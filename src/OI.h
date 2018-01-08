#ifndef OI_H
#define OI_H

#include <WPILib.h>

//creates all of the inputs on the controllers
class OI {

private:
	//declares controllers
	Joystick driverController{0};

	//xbox controls
	JoystickButton DRC_rightBumper{&driverController, 6};
	JoystickButton DRC_leftBumper{&driverController, 5};
	JoystickButton DRC_aButton{&driverController, 1};
	JoystickButton DRC_bButton{&driverController, 2};
	JoystickButton DRC_xButton{&driverController, 3};
	JoystickButton DRC_yButton{&driverController, 4};
	JoystickButton DRC_startButton{&driverController, 8};



public:
	OI();
	double GetTurn();
	double GetMove();
	double Desensitize(double value);

};

#endif
