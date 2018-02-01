#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include "RobotMap.h"

class Elevator : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Elevator();
	void InitDefaultCommand();
	bool GetTopSwitch();
	bool GetBottomSwitch();
	double GetLiftEncoder();
	void ResetLiftEncoder();
	void RunLift(double speed);
};

#endif  // Elevator_H
