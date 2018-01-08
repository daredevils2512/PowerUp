#ifndef DrivetrainShift_H
#define DrivetrainShift_H

#include "../Robot.h"
#include <Commands/Command.h>

class DrivetrainShift : public frc::Command {
public:
	DrivetrainShift(bool Direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_Direction;
};

#endif  // DrivetrainShift_H
