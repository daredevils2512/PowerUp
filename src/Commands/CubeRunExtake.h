#ifndef CubeRunExtake_H
#define CubeRunExtake_H

#include "Commands/Command.h"
#include "../Subsystems/Cube.h"
#include "../Robot.h"


class CubeRunExtake : public frc::Command {
public:
	CubeRunExtake(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_speed;
};

#endif  // CubeRunExtake_H
