#ifndef SetPIDSetpoint_H
#define SetPIDSetpoint_H

#include <WPILib.h>

class SetPIDSetpoint : public frc::Command {
public:
	SetPIDSetpoint(double setpoint);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double m_setpoint;
};

#endif  // SetPIDSetpoint_H
