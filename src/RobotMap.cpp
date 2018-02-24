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
std::shared_ptr<frc::DoubleSolenoid> RobotMap::cubeIntakeGrabberSolenoid;
std::shared_ptr<frc::DigitalInput> RobotMap::cubeIntakeLimitSwitch;

std::shared_ptr<WPI_TalonSRX> RobotMap::climberLeftWingMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberLeftWingMotor2;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberRightWingMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::climberRightWingMotor2;

std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontRight;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearRight;

std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotor;
//std::shared_ptr<frc::DigitalInput> RobotMap::elevatorBottomSwitch;

void RobotMap::init() {
	drivetrainFrontLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_LEFT_MOTOR));
	drivetrainRearLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_LEFT_MOTOR));
	drivetrainFrontRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_RIGHT_MOTOR));
	drivetrainRearRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_RIGHT_MOTOR));

	drivetrainFrontLeftMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_LEFT_MOTOR);
#ifdef ARIES
	drivetrainRearLeftMotor->SetInverted(true);
#endif
	drivetrainFrontRightMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_RIGHT_MOTOR);
#ifdef ARIES
	drivetrainRearRightMotor->SetInverted(true);
#endif

	drivetrainChassis.reset (new frc::DifferentialDrive(*drivetrainRearLeftMotor.get(), *drivetrainRearRightMotor.get()));

	drivetrainChassis->SetSafetyEnabled(true);
		drivetrainChassis->SetExpiration(0.5);
		drivetrainChassis->SetMaxOutput(1.0);

	drivetrainLeftEncoder.reset (new frc::Encoder (0, 1, false, frc::Encoder::k4X));
		drivetrainLeftEncoder->SetDistancePerPulse(Util::LEFT_INCH_PER_PULSE);
#ifdef ARIES
		drivetrainLeftEncoder->SetReverseDirection(true);
#else
		drivetrainLeftEncoder->SetReverseDirection(false);
#endif
	drivetrainRightEncoder.reset (new frc::Encoder (2, 3, false, frc::Encoder::k4X));
		drivetrainRightEncoder->SetDistancePerPulse(Util::RIGHT_INCH_PER_PULSE);
#ifdef ARIES
		drivetrainRightEncoder->SetReverseDirection(false);
#else
		drivetrainRightEncoder->SetReverseDirection(true);
#endif
	drivetrainShifter.reset (new frc::DoubleSolenoid (0, 4 , 5));

	 navX.reset(new AHRS(SPI::Port::kMXP));

	 cubeIntakeLeftMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_LEFT_MOTOR));
	 cubeIntakeRightMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_RIGHT_MOTOR));
	 cubeIntakeSolenoid.reset (new frc::DoubleSolenoid (0, 6 ,7));
//	 cubeIntakeGrabberSolenoid.reset (new frc::DoubleSolenoid (0 , 7 , 8));
//	 cubeIntakeLimitSwitch.reset (new frc::DigitalInput(Util::CUBE_INTAKE_LIMIT_SWITCH));

//	climberLeftWingMotor1.reset (new WPI_TalonSRX (Util::CLIMBER_LEFT_WING_MOTOR_1));
//	climberLeftWingMotor2.reset (new WPI_TalonSRX (Util::CLIMBER_LEFT_WING_MOTOR_2));
//	climberRightWingMotor1.reset (new WPI_TalonSRX (Util::CLIMBER_RIGHT_WING_MOTOR_1));
//	climberRightWingMotor2.reset (new WPI_TalonSRX (Util::CLIMBER_RIGHT_WING_MOTOR_2));

	ultrasonicFrontLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_LEFT)));
	ultrasonicRearLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_LEFT)));
	ultrasonicFrontRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_RIGHT)));
	ultrasonicRearRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_RIGHT)));

	elevatorMotor.reset(new WPI_TalonSRX (Util::ELEVATOR_MOTOR));
		elevatorMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
//	elevatorBottomSwitch.reset(new frc::DigitalInput(Util::ELEVATOR_BOTTOM_LIMIT_SWITCH));

}
