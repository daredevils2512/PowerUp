#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <WPILib.h>
#include "RobotMap.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/NavXSubsystem.h"
#include "Subsystems/UltrasonicSubsystem.h"
#include "Subsystems/Cube.h"
#include "Subsystems/Climber.h"
#include "Subsystems/DareDashboard.h"
#include "NavXPIDSource.h"
#include "Subsystems/Elevator.h"

#include "OI.h"


class Robot : public IterativeRobot {

public:
	frc::LiveWindow *lw;
	std::unique_ptr<frc::CommandGroup> autonomousCommand;

	static std::unique_ptr<OI> oi;
	static std::shared_ptr<Drivetrain> drivetrain;
	static std::shared_ptr<frc::Compressor> compressor;

	static std::shared_ptr<NavXSubsystem> navXSubsystem;
	static std::shared_ptr<UltrasonicSubsystem> ultrasonicSubsystem;
	static std::shared_ptr<Cube> cube;
	static std::shared_ptr<Climber> climber;

	static std::shared_ptr<DareDashboard> dashboard;

	static std::shared_ptr<NavXPIDSource> navxPidSource;

	static std::shared_ptr<Elevator> elevator;


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

	enum class StartLocation {
		left, center, right, unknown
	};

private:
	void PickAuto();

	double autoEndTime = 0.0;
};
#endif
