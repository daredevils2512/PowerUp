#ifndef ElevatorRunLift_H
#define ElevatorRunLift_H

#include <Commands/Command.h>
#include "../Robot.h"

class ElevatorRunLift : public frc::Command {
public:
	ElevatorRunLift(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_speed = 0.0;
};

#endif  // ElevatorRunLift_H
