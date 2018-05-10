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
	double m_lastShiftTime = 0.0;
	double m_shiftThreshold = 0.6;
	double m_shiftTimeThreshold = 2.0;
	double m_currentTime = frc::RobotController::GetFPGATime()/1000000.0;
};

#endif  // Drive_H
