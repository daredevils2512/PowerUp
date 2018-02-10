#ifndef ClimberLeftWingRun_H
#define ClimberLeftWingRun_H

#include "Commands/Command.h"
#include "../Subsystems/Climber.h"
#include "../Robot.h"

class ClimberLeftWingRun : public frc::Command {
public:
	ClimberLeftWingRun(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
};

#endif  // ClimberLeftWingRun_H
