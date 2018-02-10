#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include "TriggerButton.h"
#include "ThrottleButton.h"

//creates all of the inputs on the controllers
class OI {

private:
	//declares controllers
	Joystick driverController{0};
	Joystick coDriverController{1};
	Joystick coDriverBox{2};


		//xbox controls
		TriggerButton DRC_rightTrigger{&driverController, 3, 0.8};
		TriggerButton DRC_leftTrigger{&driverController, 2, 0.8};
		JoystickButton DRC_rightBumper{&driverController, 6};
		JoystickButton DRC_leftBumper{&driverController, 5};
		JoystickButton DRC_aButton{&driverController, 1};
		JoystickButton DRC_bButton{&driverController, 2};
		JoystickButton DRC_xButton{&driverController, 3};
		JoystickButton DRC_yButton{&driverController, 4};
		JoystickButton DRC_startButton{&driverController, 8};

		//co-driver logitech controls
		JoystickButton CDR_trigger{&coDriverController, 1};
		JoystickButton CDR_sideJoystickButton{&coDriverController, 2};
		JoystickButton CDR_bottomLeftJoystick{&coDriverController, 3};
		JoystickButton CDR_topLeftJoystick{&coDriverController, 5};
		JoystickButton CDR_bottomRightJoystick{&coDriverController, 4};
		JoystickButton CDR_topRightJoystick{&coDriverController, 6};
		JoystickButton CDR_bottomLeftBase{&coDriverController, 7};
		JoystickButton CDR_topLeftBase{&coDriverController, 8};
		JoystickButton CDR_bottomMiddleBase{&coDriverController, 9};
		JoystickButton CDR_topMiddleBase{&coDriverController, 10};
		JoystickButton CDR_bottomRightBase{&coDriverController, 11};
		JoystickButton CDR_topRightBase{&coDriverController, 12};
		TriggerButton CDR_zPositiveAxis{&coDriverController, 2, 0.2};
		TriggerButton CDR_zNegativeAxis{&coDriverController, 2, -0.2};
		ThrottleButton CDR_throttle{&coDriverController, 3};

		//co-driver button box controls
		JoystickButton CDB_topWhite{&coDriverBox, 2};
		JoystickButton CDB_topRed{&coDriverBox, 6};
		JoystickButton CDB_middleWhite{&coDriverBox, 8};
		JoystickButton CDB_middleRed{&coDriverBox, 4};
		JoystickButton CDB_bottomWhite{&coDriverBox, 5};
		JoystickButton CDB_bottomRed{&coDriverBox, 16};
		JoystickButton CDB_green{&coDriverBox, 7};
		JoystickButton CDB_yellow{&coDriverBox, 15};
		JoystickButton CDB_bigWhite{&coDriverBox, 3};
		JoystickButton CDB_bigRed{&coDriverBox, 14};


public:
	OI();
	double GetTurn();
	double GetMove();
	double Desensitize(double value);

};

#endif
