#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <WPILib.h>
#include "RobotMap.h"
#include "Commands/Command.h"
#include "Subsystems/Drivetrain.h"
#include "OI.h"
#include "Subsystems/NavXSubsystem.h"
#include "LiveWindow/LiveWindow.h"


class Robot : public IterativeRobot {

public:
	frc::LiveWindow *lw;
	std::unique_ptr<frc::CommandGroup> autonomousCommand;

	static std::unique_ptr<OI> oi;
	static std::shared_ptr<Drivetrain> drivetrain;
	static std::shared_ptr<frc::Compressor> compressor;
	static std::shared_ptr<NavXSubsystem> navXSubsystem;


	virtual void RobotInit();
	virtual void RobotPeriodic();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestInit();
	virtual void TestPeriodic();
};
#endif
