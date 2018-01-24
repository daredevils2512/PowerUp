#ifndef CubeIntakeActuate_H
#define CubeIntakeActuate_H

#include "Commands/Command.h"
#include "../Subsystems/Cube.h"
#include "../Robot.h"

class CubeIntakeActuate : public frc::Command {
public:
	CubeIntakeActuate(bool direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool m_direction;
};

#endif  // CubeIntakeActuate_H
