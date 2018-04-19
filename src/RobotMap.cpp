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
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainChassisFront;
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainChassisRear;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainLeftEncoder;
std::shared_ptr<frc::Encoder> RobotMap::drivetrainRightEncoder;

std::shared_ptr<AHRS> RobotMap::navX;
std::shared_ptr<frc::PIDController> RobotMap::navXTurnController;

std::shared_ptr<WPI_TalonSRX> RobotMap::cubeIntakeLeftMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::cubeIntakeRightMotor;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::cubeIntakeSolenoid;
std::shared_ptr<frc::DigitalInput> RobotMap::cubeIntakeLimitSwitch;

std::shared_ptr<WPI_TalonSRX> RobotMap::climber;
std::shared_ptr<Victor> RobotMap::climberDeploy;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::climberFork;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::climberClaws;

std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearLeft;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicFrontRight;
std::shared_ptr<UltrasonicSensor> RobotMap::ultrasonicRearRight;

std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotor;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorBackMotor;
std::shared_ptr<frc::DigitalInput> RobotMap::elevatorBottomSwitch;

void RobotMap::init() {
	//TODO PCM ID is 60 on Atlas, change this on Alea when you can
	drivetrainFrontLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_LEFT_MOTOR));
//		Robot::dashboard->RegisterTalonSRX("drivetrain.motorControllers.frontLeft",drivetrainFrontLeftMotor.get());
//
	drivetrainRearLeftMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_LEFT_MOTOR));
//		Robot::dashboard->RegisterTalonSRX("drivetrain.motorControllers.rearLeft",drivetrainRearLeftMotor.get());
//
	drivetrainFrontRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_FRONT_RIGHT_MOTOR));
//		Robot::dashboard->RegisterTalonSRX("drivetrain.motorControllers.frontRight",drivetrainFrontRightMotor.get());
//
	drivetrainRearRightMotor.reset (new WPI_TalonSRX (Util::DRIVETRAIN_REAR_RIGHT_MOTOR));
//		Robot::dashboard->RegisterTalonSRX("drivetrain.motorControllers.rearRight",drivetrainRearRightMotor.get());
//
//	drivetrainFrontLeftMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_LEFT_MOTOR);
//	drivetrainFrontRightMotor->Set(ControlMode::Follower, Util::DRIVETRAIN_REAR_RIGHT_MOTOR);
	drivetrainChassisRear.reset (new frc::DifferentialDrive(*drivetrainRearLeftMotor.get(), *drivetrainRearRightMotor.get()));
	drivetrainChassisFront.reset (new frc::DifferentialDrive(*drivetrainFrontLeftMotor.get(), *drivetrainFrontRightMotor.get()));

	drivetrainChassisFront->SetSafetyEnabled(false);
		drivetrainChassisFront->SetExpiration(0.5);
		drivetrainChassisFront->SetMaxOutput(1.0);

	drivetrainChassisRear->SetSafetyEnabled(false);
		drivetrainChassisRear->SetExpiration(0.5);
		drivetrainChassisRear->SetMaxOutput(1.0);
//
//	drivetrainLeftEncoder.reset (new frc::Encoder (0, 1, false, frc::Encoder::k4X));//TODO: util.h constants
//		drivetrainLeftEncoder->SetDistancePerPulse(Util::LEFT_INCH_PER_PULSE);
//		drivetrainLeftEncoder->SetReverseDirection(false);
//
//		Robot::dashboard->RegisterEncoder("drivetrain.encoders.left",drivetrainLeftEncoder.get(),0,1);
//
//		drivetrainRightEncoder.reset (new frc::Encoder (2, 3, false, frc::Encoder::k4X));//TODO: ulti.h constants
//		drivetrainRightEncoder->SetDistancePerPulse(Util::RIGHT_INCH_PER_PULSE);
//		drivetrainRightEncoder->SetReverseDirection(true);
//
//		Robot::dashboard->RegisterEncoder("drivetrain.encoders.right",drivetrainRightEncoder.get(),2,3);
//
	drivetrainShifter.reset (new frc::DoubleSolenoid (0,4,5)); //TODO change back to 4,5 for Alea & USE UTIL CONSTANTS!!!
//		Robot::dashboard->RegisterDoubleSolenoid("drivetrain.shifter",drivetrainShifter.get(),4,5);

	 navX.reset(new AHRS(SPI::Port::kMXP));

//	 cubeIntakeLeftMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_LEFT_MOTOR));
//	 	 Robot::dashboard->RegisterTalonSRX("cube.intake.leftMotor",cubeIntakeLeftMotor.get());
//
//	 cubeIntakeRightMotor.reset (new WPI_TalonSRX (Util::CUBE_INTAKE_RIGHT_MOTOR));
//	 	 Robot::dashboard->RegisterTalonSRX("cube.intake.rightMotor",cubeIntakeRightMotor.get());
//
//	 cubeIntakeSolenoid.reset (new frc::DoubleSolenoid (0,6,7)); //TODO change back to 6,7 for Alea
//	 	 Robot::dashboard->RegisterDoubleSolenoid("cube.intake.grabberSolenoid",cubeIntakeSolenoid.get(),6,7);

	 	 //TODO: implement dashboard registers for commented methods
//	 cubeIntakeGrabberSolenoid.reset (new frc::DoubleSolenoid (0 , 7 , 8));
//	 cubeIntakeLimitSwitch.reset (new frc::DigitalInput(Util::CUBE_INTAKE_LIMIT_SWITCH));
//	 	 Robot::dashboard->RegisterLimitSwitch("cube.intake.cubeSwitch",cubeIntakeLimitSwitch.get());
//
//	climber.reset (new WPI_TalonSRX (Util::CLIMBER));
//	climberFork.reset(new frc::DoubleSolenoid(0, 8, 9));
//	climberClaws.reset(new frc::DoubleSolenoid(0, 10, 11));
//	climberDeploy.reset(new Victor (Util::CLIMBER_DEPLOY));
//	climber.reset (new WPI_TalonSRX (Util::CLIMBER));

//	climberClaws.reset(new frc::DoubleSolenoid(0, 10, 11));
//	climberFork.reset(new frc::DoubleSolenoid(0, 8, 9));

//	ultrasonicFrontLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_LEFT)));
//	ultrasonicRearLeft.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_LEFT)));
//	ultrasonicFrontRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_FRONT_RIGHT)));
//	ultrasonicRearRight.reset(new UltrasonicSensor(new frc::AnalogInput(Util::ULTRASONIC_REAR_RIGHT)));

//	elevatorMotor.reset(new WPI_TalonSRX (Util::ELEVATOR_MOTOR));
//		elevatorMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
//		Robot::dashboard->RegisterTalonSRX("cube.elevatorMotor",elevatorMotor.get());
//	elevatorBackMotor.reset(new WPI_TalonSRX (Util::ELEVATOR_BACK_MOTOR));
//		elevatorBackMotor->Set(ControlMode::Follower , Util::ELEVATOR_MOTOR);
//		elevatorBackMotor->SetInverted(true);
//	elevatorBottomSwitch.reset(new frc::DigitalInput(Util::ELEVATOR_BOTTOM_LIMIT_SWITCH));
//		Robot::dashboard->RegisterLimitSwitch("cube.elevatorBottomSwitch", elevatorBottomSwitch.get());
}
