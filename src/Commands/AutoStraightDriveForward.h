#ifndef AutoStraightDriveForward_H
#define AutoStraightDriveForward_H

#include <Commands/Command.h>

class AutoStraightDriveForward : public frc::Command {
public:
	AutoStraightDriveForward(double targetFeet, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

protected:
	double m_targetFeet;
	double m_speed;
	
};

#endif  // AutoStraightDrive_H
