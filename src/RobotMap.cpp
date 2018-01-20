#include "RobotMap.h"
#include "Robot.h"
#include "Subsystems/NavXSubsystem.h"
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <RobotDrive.h>
#include <LiveWindow/LiveWindow.h>
#include "Util.h"

double PIDOutput = 0.0;

std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainFrontRightMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainRearRightMotor;
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainChassis;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainRightEncoder;

std::shared_ptr<AHRS> RobotMap::navX;
std::shared_ptr<frc::PIDController> RobotMap::navXTurnController;

std::shared_ptr<frc::Spark> RobotMap::motor1;
std::shared_ptr<frc::Spark> RobotMap::motor2;
std::shared_ptr<frc::Spark> RobotMap::motor3;
std::shared_ptr<frc::Spark> RobotMap::motor4;

std::shared_ptr<frc::AnalogInput> RobotMap::ultrasonicFrontLeft;
std::shared_ptr<frc::AnalogInput> RobotMap::ultrasonicRearLeft;
std::shared_ptr<frc::PIDController> RobotMap::ultrasonicTurnController;


void RobotMap::init() {


	drivetrainFrontLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_LEFT_MOTOR));
	drivetrainRearLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_LEFT_MOTOR));
	drivetrainFrontRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_RIGHT_MOTOR));
	drivetrainRearRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_RIGHT_MOTOR));

	drivetrainFrontLeftMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_LEFT_MOTOR);
	drivetrainRearLeftMotor->SetInverted(true);

	drivetrainFrontRightMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_RIGHT_MOTOR);
	drivetrainRearRightMotor->SetInverted(true);

	drivetrainChassis.reset (new frc::DifferentialDrive(*drivetrainRearLeftMotor.get(), *drivetrainRearRightMotor.get()));

	drivetrainChassis->SetSafetyEnabled(true);
		drivetrainChassis->SetExpiration(0.5);
		drivetrainChassis->SetMaxOutput(1.0);
	drivetrainLeftEncoder.reset (new frc::Encoder (0, 1, false, frc::Encoder::k4X)); //theoretical a and b channels
		drivetrainLeftEncoder->SetDistancePerPulse(Util::LEFT_INCH_PER_PULSE); //took the circumference of 12.5663 and divided by the 128 internal encoder clicks
		drivetrainLeftEncoder->SetReverseDirection(true);

	drivetrainRightEncoder.reset (new frc::Encoder (2, 3, false, frc::Encoder::k4X));
		drivetrainRightEncoder->SetDistancePerPulse(Util::RIGHT_INCH_PER_PULSE);

	//drivetrainShifter.reset (new frc::DoubleSolenoid (0,0,1));

	navX.reset(new AHRS(SPI::Port::kMXP));

	// motor1.reset(new frc::Spark(1));
	// motor2.reset(new frc::Spark(2));
	// motor3.reset(new frc::Spark(3));
	// motor4.reset(new frc::Spark(4));

	ultrasonicFrontLeft.reset(new frc::AnalogInput(Util::ULTRASONIC_FRONT_LEFT));
		ultrasonicFrontLeft->SetAverageBits(50);
		ultrasonicFrontLeft->SetOversampleBits(2);
	ultrasonicRearLeft.reset(new frc::AnalogInput(Util::ULTRASONIC_REAR_LEFT));
		ultrasonicRearLeft->SetAverageBits(50);
		ultrasonicRearLeft->SetOversampleBits(2);
	ultrasonicTurnController.reset(new frc::PIDController(Util::ULTRASONIC_P_VALUE, Util::ULTRASONIC_I_VALUE, Util::ULTRASONIC_D_VALUE, Util::ULTRASONIC_F_VALUE, ultrasonicPIDSource))
}
