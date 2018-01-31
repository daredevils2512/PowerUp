#ifndef ClimberRightWingRun_H
#define ClimberRightWingRun_H

#include "Commands/Command.h"
#include "../Subsystems/Climber.h"
#include "../Robot.h"

class ClimberRightWingRun : public frc::Command {
public:
	ClimberRightWingRun(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
};

#endif  // ClimberRightWingRun_H
