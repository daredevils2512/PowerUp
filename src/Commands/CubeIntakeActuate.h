#ifndef CubeIntakeActuate_H
#define CubeIntakeActuate_H

#include "Commands/Command.h"
#include "../Subsystems/Cube.h"
#include "../Robot.h"

class CubeIntakeActuate : public frc::Command {
public:
	void Initialize(){};
	void Execute();
	bool IsFinished();
	void End(){};
	void Interrupted();

protected:
	CubeIntakeActuate();
	virtual ~CubeIntakeActuate(){};

	virtual frc::DoubleSolenoid::Value getDirection() = 0;
};

#endif  // CubeIntakeActuate_H
