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
	lw->Add(RobotMap::drivetrainChassis);
	std::thread(RobotClient::recv).detach();
	RobotClient::Connect();
}
void Robot::RobotPeriodic() {
//	std::cout << "Robto Periodic" << std::endl;

//TODO comment printouts back in once robot is complete, only commented out because ICC will be sketchy
	SmartDashboard::PutNumber("GetYaw",RobotMap::navX->GetYaw());
	SmartDashboard::PutNumber("GetRoll",RobotMap::navX->GetRoll());
	SmartDashboard::PutNumber("GetPitch",RobotMap::navX->GetPitch());

	SmartDashboard::PutNumber("Subsystem Get Left Encoder", Robot::drivetrain->GetLeftEncoder());
	SmartDashboard::PutNumber("Raw Left Encoder", RobotMap::drivetrainLeftEncoder->Get());
	SmartDashboard::PutNumber("Subsystem Get Right Encoder", Robot::drivetrain->GetRightEncoder());
	SmartDashboard::PutNumber("Raw Right Encoder", RobotMap::drivetrainRightEncoder->Get());
	SmartDashboard::PutNumber("Elevator Encoder" , Robot::elevator->GetLiftMagneticEncoder());

//	SmartDashboard::PutNumber("Drivetrain Front Left Current" , RobotMap::drivetrainFrontLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Front Right Current" , RobotMap::drivetrainFrontRightMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Left Current" , RobotMap::drivetrainRearLeftMotor->GetOutputCurrent());
//	SmartDashboard::PutNumber("Drivetrain Rear Right Current" , RobotMap::drivetrainRearRightMotor->GetOutputCurrent());

	SmartDashboard::PutBoolean("Intake Limit Switch" , RobotMap::cubeIntakeLimitSwitch->Get());

//	SmartDashboard::PutNumber("Front Left Ultrasonic distance", RobotMap::ultrasonicFrontLeft->GetDistance());
//	SmartDashboard::PutNumber("Rear Left Ultrasonic distance", RobotMap::ultrasonicRearLeft->GetDistance());
//	SmartDashboard::PutNumber("Front Right Ultrasonic distance", RobotMap::ultrasonicFrontRight->GetDistance());
//	SmartDashboard::PutNumber("Rear Right Ultrasonic distance", RobotMap::ultrasonicRearRight->GetDistance());
//	SmartDashboard::PutNumber("Average Distance Away", Robot::ultrasonicSubsystem->GetAverageDistance(Util::RobotSide::leftSide));
//	SmartDashboard::PutNumber ("Voltage Returned Front", RobotMap::ultrasonicFrontLeft->GetAnalogInput()->GetAverageVoltage());
//	SmartDashboard::PutNumber ("Voltage Returned Rear", RobotMap::ultrasonicRearLeft->GetAnalogInput()->GetAverageVoltage());
//	SmartDashboard::PutNumber("Starting Distance", Robot::ultrasonicSubsystem->m_startingDistance);

	SmartDashboard::PutBoolean("Bottom Limit Switch" , RobotMap::elevatorBottomSwitch->Get());
//	SmartDashboard::PutNumber("Elevator Current" , RobotMap::elevatorMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("Drivetrain PID", Robot::drivetrain->GetPIDOutput());

	SmartDashboard::PutNumber("Y-Axis", Robot::oi->GetMove());
	SmartDashboard::PutNumber("X-Axis", Robot::oi->GetTurn());
	}
void Robot::DisabledInit(){
	std::cout << "Let's start being disabled" << std::endl;
	compressor->SetClosedLoopControl(false);
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	elevator->RunLift(0.1);
	drivetrain->SetPIDEnabled(false);
	drivetrain->GetPIDOutput();
}

void Robot::DisabledPeriodic() {
//	std::cout << "I'm Disabled!" << std::endl;
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
	Robot::elevator->GetBottomSwitch();
	this->PickAuto();
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Brake);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Brake);
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
//	std::cout << "I'm in auto!" << std::endl;
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	std::cout << "Let's start teleop" << std::endl;
	Robot::drivetrain->ResetEncoders();
	Robot::elevator->ResetMagneticEncoder();
	cube->SetIntakeSpeed(0.0);
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Coast);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Coast);
	compressor->SetClosedLoopControl(true);
	if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() {
//	std::cout << "I'm telopeed!" << std::endl;
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

START_ROBOT_CLASS(Robot);
