#ifndef UltrasonicSubsystem_H
#define UltrasonicSubsystem_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "../Util.h"

class UltrasonicSubsystem : public frc::Subsystem, public PIDOutput {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	double pidOutput = 0.0;

public:

	UltrasonicSubsystem();
	void InitDefaultCommand();
	virtual void PIDWrite(double output);
	double GetDistance(double voltageMeasured);
	void DriveStaight(Util::RobotSide robotSide, double driveSpeed);
	bool IsPIDEnabled();
	double GetPIDOutput();
	void SetPIDEnabled(bool enabled);
};

#endif  // UltrasonicSubsystem_H
