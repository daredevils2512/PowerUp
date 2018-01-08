#include "Robot.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;

void Robot::RobotInit() {
    drivetrain.reset(new Drivetrain());
	oi.reset(new OI());
	compressor.reset(new frc::Compressor());
  }
void Robot::RobotPeriodic() {

}
void Robot::DisabledInit(){
	compressor->SetClosedLoopControl(false);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

}

void Robot::TeleopInit() {
	compressor->SetClosedLoopControl(true);

	if (autonomousCommand.get() != nullptr)
			autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	}

void Robot::TestPeriodic() {
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
