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

std::shared_ptr<WPI_TalonSRX> RobotMap::cubeIntakeLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::cubeIntakeRightMotor;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::cubeIntakeSolenoid;

std::shared_ptr<WPI_TalonSRX> RobotMap::climberLeftWingMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberLeftWingMotor2;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberRightWingMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberRightWingMotor2;

std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontRight;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearRight;

std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorRightMotor;
std::shared_ptr<frc::Encoder> RobotMap::elevatorEncoder;
std::shared_ptr<frc::DigitalInput> RobotMap::elevatorTopSwitch;
std::shared_ptr<frc::DigitalInput> RobotMap::elevatorBottomSwitch;

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

//	 cubeIntakeLeftMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_LEFT_MOTOR));
//	 cubeIntakeRightMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_RIGHT_MOTOR));
//	 cubeIntakeSolenoid.reset (new frc::DoubleSolenoid (0, 4 ,5));

//	climberLeftWingMotor1.reset (new WPI_TalonSRX (Util::CLIMBER_LEFT_WING_MOTOR_1));
//	climberLeftWingMotor2.reset (new WPI_TalonSRX (Util::CLIMBER_LEFT_WING_MOTOR_2));
//	climberRightWingMotor1.reset (new WPI_TalonSRX (Util::CLIMBER_RIGHT_WING_MOTOR_1));
//	climberRightWingMotor2.reset (new WPI_TalonSRX (Util::CLIMBER_RIGHT_WING_MOTOR_2));

	ultrasonicFrontLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_LEFT)));
	ultrasonicRearLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_LEFT)));
	ultrasonicFrontRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_RIGHT)));
	ultrasonicRearRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_RIGHT)));

//	elevatorLeftMotor.reset(new WPI_TalonSRX(Util::ELEVATOR_LEFT_MOTOR));
//	elevatorRightMotor.reset(new WPI_TalonSRX(Util::ELEVATOR_RIGHT_MOTOR));
	elevatorTopSwitch.reset(new frc::DigitalInput(Util::ELEVATOR_TOP_LIMIT_SWITCH));
	elevatorBottomSwitch.reset(new frc::DigitalInput(Util::ELEVATOR_BOTTOM_LIMIT_SWITCH));
	elevatorEncoder.reset(new frc::Encoder(6, 7, false, frc::Encoder::k4X));
}
