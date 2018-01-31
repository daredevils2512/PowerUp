#include "Robot.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;
std::shared_ptr<UltrasonicSubsystem> Robot::ultrasonicSubsystem;
std::shared_ptr<Cube> Robot::cube;
std::shared_ptr<NavXPIDSource> Robot::navxPidSource;


void Robot::RobotInit() {
	std::cout << "Robot Init" << std::endl;
	RobotMap::init();
    drivetrain.reset(new Drivetrain());
    ultrasonicSubsystem.reset(new UltrasonicSubsystem());
    navxPidSource.reset(new NavXPIDSource());
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
	oi.reset(new OI());
	compressor.reset(new frc::Compressor());
	cube.reset (new Cube());
	lw = frc::LiveWindow::GetInstance();
//	lw->Add(RobotMap::navXTurnController);
	lw->Add(RobotMap::drivetrainChassis);
}
void Robot::RobotPeriodic() {
//	std::cout << "Robto Periodic" << std::endl;
	SmartDashboard::PutBoolean("Is Connected",RobotMap::navX->IsConnected());
	SmartDashboard::PutBoolean("Is Moving",RobotMap::navX->IsMoving());
	SmartDashboard::PutBoolean("Is Rotating",RobotMap::navX->IsRotating());
	SmartDashboard::PutNumber("GetYaw",RobotMap::navX->GetYaw());
	SmartDashboard::PutNumber("GetRoll",RobotMap::navX->GetRoll());
	SmartDashboard::PutNumber("GetPitch",RobotMap::navX->GetPitch());



	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("Raw Left Encoder", RobotMap::drivetrainLeftEncoder->Get());
	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("Raw Right Encoder", RobotMap::drivetrainRightEncoder->Get());

	SmartDashboard::PutNumber("Front Ultrasonic distance", Robot::ultrasonicSubsystem->ConvertToDistance(RobotMap::ultrasonicFrontLeft->GetAverageVoltage()));
	SmartDashboard::PutNumber("Rear Ultrasonic distance", Robot::ultrasonicSubsystem->ConvertToDistance(RobotMap::ultrasonicRearLeft->GetAverageVoltage()));
	SmartDashboard::PutNumber("Average Distance Away", Robot::ultrasonicSubsystem->GetAverageDistance(Util::RobotSide::leftSide));
	SmartDashboard::PutNumber ("Voltage Returned Front", RobotMap::ultrasonicFrontLeft->GetAverageVoltage());
	SmartDashboard::PutNumber ("Voltage Returned Rear", RobotMap::ultrasonicRearLeft->GetAverageVoltage());
	SmartDashboard::PutNumber("Starting Distance", Robot::ultrasonicSubsystem->m_startingDistance);

}
void Robot::DisabledInit(){
	RobotMap::ultrasonicRelay1->Set(false);
	RobotMap::ultrasonicRelay2->Set(false);
	RobotMap::ultrasonicRelay3->Set(false);
	RobotMap::ultrasonicRelay4->Set(false);
	compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	drivetrain->SetPIDEnabled(false);
	//drivetrain->GetPIDOutput();

}

void Robot::DisabledPeriodic() {
//	std::cout << "I'm Disabled!" << std::endl;
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	RobotMap::ultrasonicRelay1->Set(false);
	RobotMap::ultrasonicRelay2->Set(false);
	RobotMap::ultrasonicRelay3->Set(false);
	RobotMap::ultrasonicRelay4->Set(false);
	Robot::drivetrain->ResetEncoders();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

}

void Robot::TeleopInit() {
	RobotMap::ultrasonicRelay1->Set(false);
	RobotMap::ultrasonicRelay2->Set(false);
	RobotMap::ultrasonicRelay3->Set(false);
	RobotMap::ultrasonicRelay4->Set(false);
	Robot::drivetrain->ResetEncoders();
	compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr)
			autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	}

void Robot::TestInit() {
	RobotMap::ultrasonicRelay1->Set(false);
	RobotMap::ultrasonicRelay2->Set(false);
	RobotMap::ultrasonicRelay3->Set(false);
	RobotMap::ultrasonicRelay4->Set(false);
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
