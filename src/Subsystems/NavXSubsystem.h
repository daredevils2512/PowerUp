#ifndef NavXSubsystem_H
#define NavXSubsystem_H

#include <Commands/Subsystem.h>

class NavXSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities


public:
	NavXSubsystem();
	void InitDefaultCommand();
	void RotateToAngle(double angle);

	const static double NAVX_P_VALUE;
	const static double NAVX_I_VALUE;
	const static double NAVX_D_VALUE;
	const static double NAVX_F_VALUE;
};

#endif  // NavXSubsystem_H
