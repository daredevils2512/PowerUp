#ifndef ElevatorManualRun_H
#define ElevatorManualRun_H

#include <Commands/Command.h>

class ElevatorManualRun : public frc::Command {
public:
	ElevatorManualRun();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorManualRun_H
