#ifndef Pause_H
#define Pause_H

#include "../Robot.h"

class Pause : public frc::Command {
public:
	Pause(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Pause_H
