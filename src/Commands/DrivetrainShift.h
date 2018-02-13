#ifndef DrivetrainShift_H
#define DrivetrainShift_H

#include "../Robot.h"
#include <Commands/Command.h>

class DrivetrainShift : public frc::Command {
public:
	DrivetrainShift();
	void Initialize();
	virtual void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
protected:
	DoubleSolenoid::Value currentStatus = DoubleSolenoid::kOff;
};

#endif  // DrivetrainShift_H
