#ifndef Drive_H
#define Drive_H

#include "../Robot.h"
#include <Commands/Command.h>


class Drive : public frc::Command {
public:
	Drive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Drive_H
