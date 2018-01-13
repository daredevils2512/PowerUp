#ifndef AutoTimedDrive_H
#define AutoTimedDrive_H

#include <Commands/Command.h>

class AutoTimedDrive : public frc::Command {
public:
	AutoTimedDrive(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoTimedDrive_H
