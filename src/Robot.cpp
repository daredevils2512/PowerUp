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
//	lw->Add(RobotMap::drivetrainChassisFront);
//	lw->Add(RobotMap::drivetrainChassisRear);
//	std::thread(SocketClient::recv).detach();
//	SocketClient::Connect();
}
void Robot::RobotPeriodic() {
//	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->xData, Robot::navXSubsystem->xData.name);
//	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->yData, Robot::navXSubsystem->yData.name);
//	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->zData, Robot::navXSubsystem->zData.name);

//	SmartDashboard::PutNumber("GetYaw",RobotMap::navX->GetYaw());
//	SmartDashboard::PutNumber("GetRoll",RobotMap::navX->GetRoll());
//	SmartDashboard::PutNumber("GetPitch",RobotMap::navX->GetPitch());
	SmartDashboard::PutBoolean("Connected?", RobotMap::navX->IsConnected());
	SmartDashboard::PutString("firmware" , RobotMap::navX->GetFirmwareVersion());
	SmartDashboard::PutNumber("X Velocity", RobotMap::navX->GetVelocityX());
	SmartDashboard::PutNumber("Y Velocity", RobotMap::navX->GetVelocityY());
	SmartDashboard::PutNumber("Z Velocity", RobotMap::navX->GetVelocityZ());
	SmartDashboard::PutNumber("X Acceleration", Robot::navXSubsystem->xData.currentAccel);
	SmartDashboard::PutNumber("Y Acceleration", Robot::navXSubsystem->yData.currentAccel);
	SmartDashboard::PutNumber("Z Acceleration", Robot::navXSubsystem->zData.currentAccel);
	SmartDashboard::PutBoolean("X Collided?", Robot::navXSubsystem->xData.collided);
    SmartDashboard::PutBoolean("Y Collided?", Robot::navXSubsystem->yData.collided);
    SmartDashboard::PutBoolean("Z Collided?", Robot::navXSubsystem->zData.collided);
    SmartDashboard::PutNumber("X Counter", Robot::navXSubsystem->xData.collisionCount);
    SmartDashboard::PutNumber("Y Counter", Robot::navXSubsystem->yData.collisionCount);
    SmartDashboard::PutNumber("Z Counter", Robot::navXSubsystem->zData.collisionCount);
    SmartDashboard::PutNumberArray("X Top Ten", Robot::navXSubsystem->xData.TopTen);

//	SmartDashboard::PutNumberArray("X-Top Ten", Robot::drivetrain->m_xTopTen);

//	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
//	SmartDashboard::PutNumber("Raw Left Encoder", RobotMap::drivetrainLeftEncoder->Get());
//	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());
//	SmartDashboard::PutNumber("Raw Right Encoder", RobotMap::drivetrainRightEncoder->Get());
//	SmartDashboard::PutNumber("Elevator Encoder" , Robot::elevator->GetLiftMagneticEncoder());

//	SmartDashboard::PutNumber("Drivetrain PID", Robot::drivetrain->GetPIDOutput());
//	SmartDashboard::PutNumber("Drivetrain Front Left Current" , RobotMap::drivetrainFrontLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Front Right Current" , RobotMap::drivetrainFrontRightMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Left Current" , RobotMap::drivetrainRearLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Right Current" , RobotMap::drivetrainRearRightMotor->GetOutputCurrent());

//	PrintFaults(RobotMap::drivetrainFrontLeftMotor.get(), "FL");
//	PrintFaults(RobotMap::drivetrainFrontRightMotor.get(), "FR");
//	PrintFaults(RobotMap::drivetrainRearLeftMotor.get(), "RL");
//	PrintFaults(RobotMap::drivetrainRearRightMotor.get(), "RR");
//	PrintFaults(RobotMap::elevatorMotor.get(), "elevator");
//	PrintFaults(RobotMap::cubeIntakeLeftMotor.get(), "IL");
//	PrintFaults(RobotMap::cubeIntakeRightMotor.get(), "IR");

//	SmartDashboard::PutNumber("Front Left Ultrasonic distance", RobotMap::ultrasonicFrontLeft->GetDistance());
//	SmartDashboard::PutNumber("Rear Left Ultrasonic distance", RobotMap::ultrasonicRearLeft->GetDistance());
//	SmartDashboard::PutNumber("Front Right Ultrasonic distance", RobotMap::ultrasonicFrontRight->GetDistance());
//	SmartDashboard::PutNumber("Rear Right Ultrasonic distance", RobotMap::ultrasonicRearRight->GetDistance());
//	SmartDashboard::PutNumber("Average Distance Away", Robot::ultrasonicSubsystem->GetAverageDistance(Util::RobotSide::leftSide));
//	SmartDashboard::PutNumber ("Voltage Returned Front", RobotMap::ultrasonicFrontLeft->GetAnalogInput()->GetAverageVoltage());
//	SmartDashboard::PutNumber ("Voltage Returned Rear", RobotMap::ultrasonicRearLeft->GetAnalogInput()->GetAverageVoltage());
//	SmartDashboard::PutNumber("Starting Distance", Robot::ultrasonicSubsystem->m_startingDistance);

//	SmartDashboard::PutBoolean("Bottom Limit Switch" , RobotMap::elevatorBottomSwitch->Get());
//	SmartDashboard::PutNumber("Elevator Current" , RobotMap::elevatorMotor->GetOutputCurrent());
//
//	SmartDashboard::PutBoolean("Intake Limit Switch" , RobotMap::cubeIntakeLimitSwitch->Get());
//
//	SmartDashboard::PutNumber("Y-Axis", Robot::oi->GetMove());
//	SmartDashboard::PutNumber("X-Axis", Robot::oi->GetTurn());
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

//	Robot::drivetrain->Shifter(frc::DoubleSolenoid::Value::kForward);

	Robot::elevator->GetBottomSwitch();
	this->PickAuto();
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

//	Robot::drivetrain->Shifter(frc::DoubleSolenoid::Value::kReverse);

	cube->SetIntakeSpeed(0.0);
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Coast);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Coast);
	compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
//	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
//	SmartDashboard::PutNumber("Raw Left Encoder", RobotMap::drivetrainLeftEncoder->Get());
//	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());
//	SmartDashboard::PutNumber("Raw Right Encoder", RobotMap::drivetrainRightEncoder->Get());
//	SmartDashboard::PutNumber("Elevator Encoder" , Robot::elevator->GetLiftMagneticEncoder());
//	SmartDashboard::PutBoolean("Intake Limit Switch" , RobotMap::cubeIntakeLimitSwitch->Get());
//	SmartDashboard::PutBoolean("Bottom Limit Switch" , RobotMap::elevatorBottomSwitch->Get());
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
