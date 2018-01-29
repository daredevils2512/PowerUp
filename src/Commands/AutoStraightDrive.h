#ifndef AutoStraightDrive_H
#define AutoStraightDrive_H

#include <Commands/Command.h>

class AutoStraightDrive : public frc::Command {
public:
	AutoStraightDrive(double targetFeet, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_targetFeet;
	double m_speed;
};

#endif  // AutoStraightDrive_H
