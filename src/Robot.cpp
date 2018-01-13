#include "Robot.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;


void Robot::RobotInit() {
	RobotMap::init();
    drivetrain.reset(new Drivetrain());
	oi.reset(new OI());
	//compressor.reset(new frc::Compressor());
	lw = frc::LiveWindow::GetInstance();
	lw->Add(RobotMap::navXTurnController);

}
void Robot::RobotPeriodic() {
	SmartDashboard::PutNumber("Pitch", RobotMap::navX->GetPitch());
	SmartDashboard::PutNumber("Roll",RobotMap::navX->GetRoll());
	SmartDashboard::PutNumber("Yaw",RobotMap::navX->GetYaw());
	SmartDashboard::PutBoolean("Is Connected",RobotMap::navX->IsConnected());
	SmartDashboard::PutBoolean("Is Moving",RobotMap::navX->IsMoving());
	SmartDashboard::PutBoolean("Is Rotating",RobotMap::navX->IsRotating());

	SmartDashboard::PutNumber("Altitude", RobotMap::navX->GetAltitude());
	SmartDashboard::PutNumber("Compass", RobotMap::navX->GetCompassHeading());
	SmartDashboard::PutNumber("Angle", RobotMap::navX->GetAngle());
	SmartDashboard::PutNumber("X-Velocity", RobotMap::navX->GetVelocityX());
	SmartDashboard::PutNumber("Y-Velocity", RobotMap::navX->GetVelocityY());
	SmartDashboard::PutNumber("Z-Velocity", RobotMap::navX->GetVelocityZ());
	SmartDashboard::PutNumber("X-Velocity Num", RobotMap::navX->GetVelocityX());
	SmartDashboard::PutNumber("Y-Velocity Num", RobotMap::navX->GetVelocityY());
	SmartDashboard::PutNumber("Z-Velocity Num", RobotMap::navX->GetVelocityZ());

	SmartDashboard::PutNumber("P-Value", RobotMap::navXTurnController->GetP());
	SmartDashboard::PutNumber("I-Value", RobotMap::navXTurnController->GetI());
	SmartDashboard::PutNumber("D-Value", RobotMap::navXTurnController->GetD());
	SmartDashboard::PutNumber("F-Value", RobotMap::navXTurnController->GetF());

}
void Robot::DisabledInit(){
	//compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();

	//drivetrain->GetPIDOutput();

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
	//compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr)
			autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	}

void Robot::TestInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TestPeriodic() {
	Scheduler::GetInstance()->Run();
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
