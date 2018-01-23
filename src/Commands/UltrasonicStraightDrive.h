#ifndef UltrasonicStraightDrive_H
#define UltrasonicStraightDrive_H

#include <Commands/Command.h>
#include "../Robot.h"
#include "Util.h"

class UltrasonicStraightDrive : public frc::Command {
public:
	UltrasonicStraightDrive(double driveSpeed, double driveDistance, Util::RobotSide robotSide);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_driveSpeed = 0.0;
	double m_driveDistance = 0.0;
	Util::RobotSide m_robotSide = Util::RobotSide::leftSide;
};

#endif  // UltrasonicStraightDrive_H
