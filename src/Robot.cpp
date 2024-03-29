#include <fstream>
#include <algorithm>
#include <string>
#include <iostream>

#include "Robot.h"
#include "Commands/AutoSelector.h"
#include "FileAutonomousSource.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;
std::shared_ptr<UltrasonicSubsystem> Robot::ultrasonicSubsystem;
std::shared_ptr<Cube> Robot::cube;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<NavXPIDSource> Robot::navxPidSource;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<DareDashboard> Robot::dashboard;

void Robot::PrintFaults(WPI_TalonSRX * talonPtr, std::string name) {
	Faults faults;
	ErrorCode errorCode;

	errorCode = talonPtr->GetFaults(faults);
	if (faults.HasAnyFault()) {
		std::cout << name << ": " << faults.ToString() << std::endl;
	}
	if (errorCode != OKAY) {
		std::cout << name << " error code: " << errorCode << std::endl;
	}
}

void Robot::RobotInit() {
	std::cout << "Robot Init" << std::endl;
	dashboard.reset(new DareDashboard());
	RobotMap::init();
    drivetrain.reset(new Drivetrain());
    ultrasonicSubsystem.reset(new UltrasonicSubsystem());
    navxPidSource.reset(new NavXPIDSource());
    elevator.reset(new Elevator());
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
	compressor.reset(new frc::Compressor());
	cube.reset(new Cube());
	climber.reset (new Climber());
	oi.reset(new OI());
	lw = frc::LiveWindow::GetInstance();
	lw->Add(RobotMap::navXTurnController);
	lw->Add(RobotMap::drivetrainChassisFront);
	lw->Add(RobotMap::drivetrainChassisRear);
//	std::thread(SocketClient::recv).detach();
//	SocketClient::Connect();
}
void Robot::RobotPeriodic() {
//	SmartDashboard::PutNumber("GetYaw",RobotMap::navX->GetYaw());
//	SmartDashboard::PutNumber("GetRoll",RobotMap::navX->GetRoll());
//	SmartDashboard::PutNumber("GetPitch",RobotMap::navX->GetPitch());
//	SmartDashboard::PutBoolean("connected?" , RobotMap::navX->IsConnected());
//	SmartDashboard::PutBoolean("moving?" , RobotMap::navX->IsMoving());
//	SmartDashboard::PutBoolean("rotating?" , RobotMap::navX->IsRotating());

	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("Raw Left Encoder", RobotMap::drivetrainLeftEncoder->Get());
	SmartDashboard::PutNumber("Left Encoder Rate" , RobotMap::drivetrainLeftEncoder->GetRate());
	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("Raw Right Encoder", RobotMap::drivetrainRightEncoder->Get());
	SmartDashboard::PutNumber("Right Encoder Rate" , RobotMap::drivetrainRightEncoder->GetRate());
	SmartDashboard::PutNumber("Elevator Encoder" , Robot::elevator->GetLiftMagneticEncoder());
	SmartDashboard::PutBoolean("Bottom Limit Switch" , RobotMap::elevatorBottomSwitch->Get());
	SmartDashboard::PutBoolean("Intake Limit Switch" , RobotMap::cubeIntakeLimitSwitch->Get());

//	SmartDashboard::PutNumber("Drivetrain Front Left Current" , RobotMap::drivetrainFrontLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Front Right Current" , RobotMap::drivetrainFrontRightMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Left Current" , RobotMap::drivetrainRearLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Right Current" , RobotMap::drivetrainRearRightMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Elevator Current" , RobotMap::elevatorMotor->GetOutputCurrent());
	}
void Robot::DisabledInit(){
	std::cout << "Let's start being disabled" << std::endl;
	compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	drivetrain->SetPIDEnabled(false);
	drivetrain->GetPIDOutput();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::PickAuto() {
	std::cout << "Picking Auto..." << std::endl;
	FileAutonomousSource fileAutonomousSource("/home/lvuser/Autonomous.txt");
	autonomousCommand.reset(new AutoSelector(&fileAutonomousSource));
}
void Robot::AutonomousInit() {
	std::cout << "Starting auto..." << std::endl;
	Robot::drivetrain->ResetEncoders();
	Robot::elevator->ResetMagneticEncoder();
	this->PickAuto();
//	Robot::drivetrain->Shifter(frc::DoubleSolenoid::kForward); //high gear
	RobotMap::drivetrainFrontLeftMotor->SetNeutralMode(NeutralMode::Brake);
	RobotMap::drivetrainFrontRightMotor->SetNeutralMode(NeutralMode::Brake);
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Brake);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Brake);
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	std::cout << "Let's start teleop" << std::endl;
	Robot::drivetrain->ResetEncoders();
	Robot::elevator->ResetMagneticEncoder();
	cube->SetIntakeSpeed(0.0);
	Robot::drivetrain->Shifter(frc::DoubleSolenoid::kReverse); //low gear
	Robot::cube->ActuateDeploy(frc::DoubleSolenoid::kReverse);
	RobotMap::drivetrainFrontLeftMotor->SetNeutralMode(NeutralMode::Coast);
	RobotMap::drivetrainFrontRightMotor->SetNeutralMode(NeutralMode::Coast);
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Coast);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Coast);
	compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	}

void Robot::TestInit() {
	Robot::drivetrain->ResetEncoders();
	drivetrain->SetPIDEnabled(false);
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Cancel();
	}
	drivetrain->SetPIDSetpoint(90);
}

void Robot::TestPeriodic() {
	Scheduler::GetInstance()->Run();

	if (drivetrain->IsPIDEnabled()) {
		double output = drivetrain->GetPIDOutput();
		SmartDashboard::PutNumber("PID Input", navxPidSource->PIDGet());
		SmartDashboard::PutNumber("PID Output", output);
		drivetrain->DriveRobotTank(-output,output);
	} else {
		drivetrain->DriveRobotTank(0,0);
	}
	//lw->Run();
}

START_ROBOT_CLASS(Robot)
