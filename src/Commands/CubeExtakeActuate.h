#ifndef CubeExtakeActuate_H
#define CubeExtakeActuate_H

#include "Commands/Command.h"
#include "../Subsystems/Cube.h"
#include "../Robot.h"


class CubeExtakeActuate : public frc::Command {
public:
	CubeExtakeActuate(bool direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool m_direction;
};

#endif  // CubeExtakeActuate_H
