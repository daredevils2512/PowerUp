#include "Robot.h"



std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;
std::shared_ptr<NavXPIDSource> Robot::pidSource;


void Robot::RobotInit() {

	RobotMap::init();
    drivetrain.reset(new Drivetrain());
    pidSource.reset(new NavXPIDSource());
    RobotMap::navXTurnController.reset(new frc::PIDController(
    		NavXSubsystem::NAVX_P_VALUE,
			NavXSubsystem::NAVX_I_VALUE,
			NavXSubsystem::NAVX_D_VALUE,
			NavXSubsystem::NAVX_F_VALUE,
			pidSource.get(),
			drivetrain.get()
		));
		RobotMap::navXTurnController->SetInputRange(-180.0f,  180.0f);
		RobotMap::navXTurnController->SetOutputRange(-1.0, 1.0);
		RobotMap::navXTurnController->SetAbsoluteTolerance(2.0f);
		RobotMap::navXTurnController->SetContinuous(true);

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
	SmartDashboard::PutNumber("Set- Point", RobotMap::navXTurnController->GetSetpoint());

}
void Robot::DisabledInit(){
	//compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	drivetrain->SetPIDEnabled(false);
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
	drivetrain->SetPIDEnabled(false);
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	drivetrain->SetPIDSetpoint(90);
}

void Robot::TestPeriodic() {
	Scheduler::GetInstance()->Run();

	if(drivetrain->IsPIDEnabled()){
		double output = drivetrain->GetPIDOutput();
		SmartDashboard::PutNumber("PID Input", pidSource->PIDGet());
		SmartDashboard::PutNumber("PID Output", output);
		drivetrain->DriveRobotArcade(0.0,output);
	}else{
		drivetrain->DriveRobotArcade(0,0);
	}
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
