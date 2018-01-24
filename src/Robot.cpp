#include "Robot.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;
std::shared_ptr<UltrasonicSubsystem> Robot::ultrasonicSubsystem;
std::shared_ptr<NavXPIDSource> Robot::navxPidSource;
std::shared_ptr<UltrasonicPIDSource> Robot::ultrasonicPidSource;


void Robot::RobotInit() {
	std::cout << "Robot Init" << std::endl;
	RobotMap::init();
    drivetrain.reset(new Drivetrain());
    ultrasonicSubsystem.reset(new UltrasonicSubsystem());
    navxPidSource.reset(new NavXPIDSource());
    ultrasonicPidSource.reset(new UltrasonicPIDSource());
    RobotMap::navXTurnController.reset(new frc::PIDController(
    		NavXSubsystem::NAVX_P_VALUE,
			NavXSubsystem::NAVX_I_VALUE,
			NavXSubsystem::NAVX_D_VALUE,
			NavXSubsystem::NAVX_F_VALUE,
			navxPidSource.get(),
			drivetrain.get()
		));
		RobotMap::navXTurnController->SetInputRange(-180.0f,  180.0f);
		RobotMap::navXTurnController->SetOutputRange(-1.0, 1.0);
		RobotMap::navXTurnController->SetAbsoluteTolerance(0.5f);
		RobotMap::navXTurnController->SetContinuous(true);
	RobotMap::ultrasonicTurnController.reset(new frc::PIDController(
			Util::ULTRASONIC_P_VALUE,
			Util::ULTRASONIC_I_VALUE,
			Util::ULTRASONIC_D_VALUE,
			Util::ULTRASONIC_F_VALUE,
			Robot::ultrasonicPidSource.get(),
			Robot::ultrasonicSubsystem.get()
		));
		RobotMap::ultrasonicTurnController->SetInputRange(-4.5f, 4.5f);
		RobotMap::ultrasonicTurnController->SetOutputRange(0.0, 0.5);
		RobotMap::ultrasonicTurnController->SetAbsoluteTolerance(0.5f);
		RobotMap::ultrasonicTurnController->SetContinuous(false);
	oi.reset(new OI());
	//compressor.reset(new frc::Compressor());
	lw = frc::LiveWindow::GetInstance();
//	lw->Add(RobotMap::navXTurnController);
	lw->Add(RobotMap::ultrasonicTurnController);
}
void Robot::RobotPeriodic() {
//	std::cout << "Robto Periodic" << std::endl;
	SmartDashboard::PutNumber("Pitch", RobotMap::navX->GetPitch());
	SmartDashboard::PutNumber("Roll",RobotMap::navX->GetRoll());
	SmartDashboard::PutNumber("Yaw",RobotMap::navX->GetYaw());
	SmartDashboard::PutBoolean("Is Connected",RobotMap::navX->IsConnected());
	SmartDashboard::PutBoolean("Is Moving",RobotMap::navX->IsMoving());
	SmartDashboard::PutBoolean("Is Rotating",RobotMap::navX->IsRotating());

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

	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());

	SmartDashboard::PutNumber("Front  Ultrasonic distance", Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicFrontLeft->GetAverageVoltage()));
	SmartDashboard::PutNumber("Rear Ultrasonic distance", Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicRearLeft->GetAverageVoltage()));
	SmartDashboard::PutNumber("Ultrasonic PID Input", Robot::ultrasonicPidSource->PIDGet());
	SmartDashboard::PutNumber("Ultrasonic PID Output", Robot::ultrasonicSubsystem->GetPIDOutput());
}
void Robot::DisabledInit(){
	//compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	drivetrain->SetPIDEnabled(false);
	ultrasonicSubsystem->SetPIDEnabled(false);
	//drivetrain->GetPIDOutput();

}

void Robot::DisabledPeriodic() {
//	std::cout << "I'm Disabled!" << std::endl;
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	Robot::drivetrain->ResetEncoders();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

}

void Robot::TeleopInit() {
	Robot::drivetrain->ResetEncoders();
	//compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr)
			autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	}

void Robot::TestInit() {
	Robot::drivetrain->ResetEncoders();
	drivetrain->SetPIDEnabled(false);
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	drivetrain->SetPIDSetpoint(90);
}

void Robot::TestPeriodic() {
	Scheduler::GetInstance()->Run();

	if(drivetrain->IsPIDEnabled()){
		double output = drivetrain->GetPIDOutput();
		SmartDashboard::PutNumber("PID Input", navxPidSource->PIDGet());
		SmartDashboard::PutNumber("PID Output", output);
		drivetrain->DriveRobotTank(-output,output);
	}else{
		drivetrain->DriveRobotTank(0,0);
	}
	//lw->Run();
}

START_ROBOT_CLASS(Robot);
