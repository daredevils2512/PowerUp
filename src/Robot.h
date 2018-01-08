#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <WPILib.h>
#include "RobotMap.h"
#include "Commands/Command.h"
#include "Subsystems/Drivetrain.h"
#include "OI.h"


class Robot : public IterativeRobot {

public:
	std::unique_ptr<frc::CommandGroup> autonomousCommand;

	static std::unique_ptr<OI> oi;
	static std::shared_ptr<Drivetrain> drivetrain;
	static std::shared_ptr<frc::Compressor> compressor;

	virtual void RobotInit();
	virtual void RobotPeriodic();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};
#endif
