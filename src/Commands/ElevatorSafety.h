#ifndef ElevatorSafety_H
#define ElevatorSafety_H

#include <WPILib.h>


class ElevatorSafety : public frc::Command {
public:
	ElevatorSafety();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool shouldFix;
	bool done;
	bool checked;
};

#endif  // ElevatorSafety_H
