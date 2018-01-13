#include "RobotMap.h"
#include "Robot.h"
#include "Subsystems/NavXSubsystem.h"
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <RobotDrive.h>
#include <LiveWindow/LiveWindow.h>

static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 2; //theoretical ports
static const int DRIVETRAIN_REAR_LEFT_MOTOR = 1;
static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 10;
static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 6;

double PIDOutput = 0.0;

std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;

std::shared_ptr<AHRS> RobotMap::navX;
std::shared_ptr<frc::PIDController> RobotMap::navXTurnController;

void RobotMap::init() {


	drivetrainFrontLeftMotor.reset (new WPI_TalonSRX (DRIVETRAIN_FRONT_LEFT_MOTOR));
	drivetrainRearLeftMotor.reset (new WPI_TalonSRX (DRIVETRAIN_REAR_LEFT_MOTOR));
	drivetrainFrontRightMotor.reset (new WPI_TalonSRX (DRIVETRAIN_FRONT_RIGHT_MOTOR));
	drivetrainRearRightMotor.reset (new WPI_TalonSRX (DRIVETRAIN_REAR_RIGHT_MOTOR));

	drivetrainFrontLeftMotor->Set(ControlMode::Follower,DRIVETRAIN_REAR_LEFT_MOTOR);
	drivetrainRearLeftMotor->SetInverted(true);

	drivetrainFrontRightMotor->Set(ControlMode::Follower,DRIVETRAIN_REAR_RIGHT_MOTOR);
	drivetrainRearRightMotor->SetInverted(true);

	drivetrainChassis.reset (new frc::DifferentialDrive(*drivetrainRearLeftMotor.get(), *drivetrainRearRightMotor.get()));

	drivetrainChassis->SetSafetyEnabled(true);
		drivetrainChassis->SetExpiration(0.5);
		drivetrainChassis->SetMaxOutput(1.0);

	//drivetrainShifter.reset (new frc::DoubleSolenoid (0,0,1));

	navX.reset(new AHRS(SPI::Port::kMXP));


}
