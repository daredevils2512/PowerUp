#ifndef ElavatorRunToHeight_H
#define ElavatorRunToHeight_H

#include <Commands/Command.h>

class ElevatorRunToHeight : public frc::Command {
public:
	ElevatorRunToHeight(double speed, double encPos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_speed = 0.0;
	double m_encPos = 0.0;
	bool m_runDown;
};

#endif  // ElavatorRunToHeight_H
