#include "RobotMap.h"
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <RobotDrive.h>

static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 0; //theoretical ports
static const int DRIVETRAIN_REAR_LEFT_MOTOR = 1;
static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 2;
static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 3;

std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<frc::RobotDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;

void RobotMap::init() {
	drivetrainFrontLeftMotor.reset (new WPI_TalonSRX (DRIVETRAIN_FRONT_LEFT_MOTOR));
	drivetrainRearLeftMotor.reset (new WPI_TalonSRX (DRIVETRAIN_REAR_LEFT_MOTOR));
	drivetrainFrontRightMotor.reset (new WPI_TalonSRX (DRIVETRAIN_FRONT_RIGHT_MOTOR));
	drivetrainRearRightMotor.reset (new WPI_TalonSRX (DRIVETRAIN_REAR_RIGHT_MOTOR));
	drivetrainChassis.reset (new frc::RobotDrive (drivetrainFrontLeftMotor , drivetrainRearLeftMotor , drivetrainFrontRightMotor , drivetrainRearRightMotor));

	drivetrainChassis->SetSafetyEnabled(false);
		drivetrainChassis->SetExpiration(0.5);
		drivetrainChassis->SetSensitivity(0.5);
		drivetrainChassis->SetMaxOutput(1.0);

	drivetrainShifter.reset (new frc::DoubleSolenoid (0,0,1));

}
