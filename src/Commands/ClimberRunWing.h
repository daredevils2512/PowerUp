#ifndef ClimberRunWing_H
#define ClimberRunWing_H

#include "Commands/Command.h"
#include "../Subsystems/Climber.h"
#include "../Robot.h"

class ClimberRunWing : public frc::Command {
public:
	ClimberRunWing(Climber::ClimberWing wing, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
	Climber::ClimberWing m_wing;
};

#endif  // ClimberRightWingRun_H
