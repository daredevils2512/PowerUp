#ifndef CubeRunIntake_H
#define CubeRunIntake_H

#include "Commands/Command.h"
#include "../Subsystems/Cube.h"
#include "../Robot.h"


class CubeRunIntake : public frc::Command {
public:
	CubeRunIntake(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_speed;
};

#endif  // CubeRunIntake_H
