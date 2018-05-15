#ifndef Drive_H
#define Drive_H

#include "../Robot.h"
#include <Commands/Command.h>
#include "Subsystems/Elevator.h"


class Drive : public frc::Command {
public:
	Drive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_shiftThreshold = 0.6;
	double m_lowGearRate = 100;
	double m_highGearRate = 200;
	double m_encoderShiftThreshold = 0.8;
};

#endif  // Drive_H
