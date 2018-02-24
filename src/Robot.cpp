#include <fstream>
#include <algorithm>
#include <string>
#include <iostream>

#include "Robot.h"
#include "Commands/CMG_AutoGenerated.h"
#include "Commands/Drive.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/ElevatorRunToHeight.h"
#include "Commands/PIDTurn.h"
#include "Commands/PIDDriveStraight.h"
#include "Commands/UltrasonicStraightDrive.h"
#include "Commands/PrintCurrentFPGATime.h"
#include "Commands/Pause.h"
#include "Commands/AutoTimedDrive.h"
#include "Commands/AutoStraightDrive.h"

std::shared_ptr<Drivetrain> Robot::drivetrain;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<frc::Compressor> Robot::compressor;
std::shared_ptr<NavXSubsystem> Robot::navXSubsystem;
std::shared_ptr<UltrasonicSubsystem> Robot::ultrasonicSubsystem;
std::shared_ptr<Cube> Robot::cube;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<NavXPIDSource> Robot::navxPidSource;
std::shared_ptr<Elevator> Robot::elevator;

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
	SocketClient::Connect();
}
void Robot::RobotPeriodic() {
//	std::cout << "Robto Periodic" << std::endl;

//TODO comment printouts back in once robot is complete, only commented out because ICC will be sketchy

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
	SmartDashboard::PutNumber("Elevator Encoder" , Robot::elevator->GetLiftMagneticEncoder());

	SmartDashboard::PutNumber("Drivetrain Front Left Current" , RobotMap::drivetrainFrontLeftMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("Drivetrain Front Right Current" , RobotMap::drivetrainFrontRightMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("Drivetrain Rear Left Current" , RobotMap::drivetrainRearLeftMotor->GetOutputCurrent());
	SmartDashboard::PutNumber("Drivetrain Rear Right Current" , RobotMap::drivetrainRearRightMotor->GetOutputCurrent());

//	SmartDashboard::PutBoolean("Intake Limit Switch" , RobotMap::cubeIntakeLimitSwitch->Get());

	SmartDashboard::PutNumber("Front Left Ultrasonic distance", RobotMap::ultrasonicFrontLeft->GetDistance());
	SmartDashboard::PutNumber("Rear Left Ultrasonic distance", RobotMap::ultrasonicRearLeft->GetDistance());
	SmartDashboard::PutNumber("Front Right Ultrasonic distance", RobotMap::ultrasonicFrontRight->GetDistance());
	SmartDashboard::PutNumber("Rear Right Ultrasonic distance", RobotMap::ultrasonicRearRight->GetDistance());
	SmartDashboard::PutNumber("Average Distance Away", Robot::ultrasonicSubsystem->GetAverageDistance(Util::RobotSide::leftSide));
	SmartDashboard::PutNumber ("Voltage Returned Front", RobotMap::ultrasonicFrontLeft->GetAnalogInput()->GetAverageVoltage());
	SmartDashboard::PutNumber ("Voltage Returned Rear", RobotMap::ultrasonicRearLeft->GetAnalogInput()->GetAverageVoltage());
	SmartDashboard::PutNumber("Starting Distance", Robot::ultrasonicSubsystem->m_startingDistance);

//	SmartDashboard::PutBoolean("Bottom Limit Switch" , RobotMap::elevatorBottomSwitch->Get());
	SmartDashboard::PutNumber("Elevator Current" , RobotMap::elevatorMotor->GetOutputCurrent());

	}
void Robot::DisabledInit(){
	std::cout << "Let's start being disabled" << std::endl;
	compressor->SetClosedLoopControl(false);

//TODO comment back in after ICC

	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	drivetrain->SetPIDEnabled(false);
	drivetrain->GetPIDOutput();
	autonomousCommand.release(); // Make auto command null again.
}

void Robot::DisabledPeriodic() {
//	std::cout << "I'm Disabled!" << std::endl;
	Scheduler::GetInstance()->Run();
}

void Robot::PickAuto() {
	std::cout << "Picking Auto..." << std::endl;
	std::string gameMessage = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	if (gameMessage.length() == 0) return;
	char ourSwitch = gameMessage[0];
	char scale = gameMessage[1];
	//BalanceStates[2] = their switch

	StartLocation startingPosition = StartLocation::unknown;
	bool doSwitch = false;
	bool doScale = false;

	std::vector<frc::Command*> commands;

	std::ifstream ifs("/home/lvuser/Autonomous.txt");
	if (!ifs.good()) {
		std::cout << "ERROR: NO AUTO FILE FOUND. GO HUDDLE IN THE CORNER AND RESEARCH IT" << std::endl;
		std::cout << "So I'm gonna drive straight and get you some points anyway" << std::endl;
		ifs.close();
		startingPosition = StartLocation::unknown;
	}
	while (!ifs.eof()) { //TODO look into error handling for the cases in which the file is missing or empty
		std::string lastPart;
		std::string firstPart;
		std::getline(ifs, firstPart, ':');
		std::getline(ifs, lastPart);
		while (lastPart[0] == ' ') {
			lastPart = lastPart.substr(1);
		}
//		if (!ifs.eof()) {
//			lastPart = lastPart.substr(0, lastPart.size() - 1);
//		}
		std::cout << firstPart << " - " << lastPart << std::endl;
		//Lowering everything to lowercase to ignore case
		std::transform(firstPart.begin(), firstPart.end(), firstPart.begin(), ::tolower);
		std::transform(lastPart.begin(), lastPart.end(), lastPart.begin(), ::tolower);
		if (firstPart == "startposition") {
			if (lastPart == "left") {
				startingPosition = StartLocation::left;
			} else if (lastPart == "center") {
				startingPosition = StartLocation::center;
			} else if (lastPart == "right") {
				startingPosition = StartLocation::right;
			} else {
				std::cout << "That's not an option for starting positions. Don't feel like doing anything now" << std::endl;
				startingPosition = StartLocation::unknown;
			}
		} else if (firstPart == "doswitch") {
			if (lastPart == "true") {
				std::cout << "Doing the switch" << std::endl;
				doSwitch = true;
			} else if (lastPart == "false") {
				std::cout << "No switch for us" << std::endl;
				doSwitch = false;
			} else {
				std::cout << "That's not an option for doing the switch. Need more zip-ties to accomplish anything" << std::endl;
				doSwitch = false;
			}
		} else if (firstPart == "doscale") {
			if (lastPart == "true") {
				std::cout << "Doing the scale" << std::endl;
				doScale = true;
			} else if (lastPart == "false") {
				std::cout << "No scale for us" << std::endl;
				doScale = false;
			} else {
				std::cout << "That's not an option for doing the scale. Is everything plugged in?" << std::endl;
				doScale = false;
			}
		}
	}
	//USING THE TERTIARY CONVERTERS
	int directionSwitch = (ourSwitch == 'L') ? -1 : 1; 		//directionSwitch equal to 1 if turning right and -1 if left
	int directionScale = (scale == 'L') ? 1 : -1;			//switched values so that we turn the proper way towards the scale
	Util::RobotSide trackingSide = (startingPosition == StartLocation::left)
		? Util::RobotSide::leftSide
		: Util::RobotSide::rightSide;
	//Use commands.push_back() to add commands
	commands.push_back(new PrintCurrentFPGATime());
	if (startingPosition == StartLocation::center) {
		std::cout << "We're in the center!" << std::endl;
		if (doSwitch){
			//With 90 degree turns
//			std::cout << "Doing the easy peasy stuff" << std::endl;
//			commands.push_back(new PIDDriveStraight(50));			//drive straight to get away from the wall
//			commands.push_back(new PIDTurn(90 * directionSwitch));	//turning left or right based off of which side is ours
//			commands.push_back(new PIDDriveStraight(56));			//going places
//			commands.push_back(new PIDTurn(90 * -directionSwitch));	//turning back to be aimed at the switch
//			commands.push_back(new PIDDriveStraight(54));			//running to the switch
//			commands.push_back(new CubeRunIntake(-1.0));			//bye bye cube!
			//with 45 degree turns
			commands.push_back(new PIDDriveStraight(30));
			commands.push_back(new PIDTurn(45 * directionSwitch));
			commands.push_back(new PIDDriveStraight(71)); //68
			commands.push_back(new PIDTurn(45 * -directionSwitch));
			commands.push_back(new PIDDriveStraight(36));
		} else {
			std::cout << "Just going for a drive" << std::endl;
			commands.push_back(new PIDDriveStraight(90));		// drive forward and cross auto line
		}
	} else if (startingPosition == StartLocation::left || startingPosition == StartLocation::right) {
		std::cout << "On one of the sides!" << std::endl;
		char sideCheck = (startingPosition == StartLocation::right) ? 'R' : 'L'; //If starting pos. is right, sideCheck is right otherwise left
		if (doSwitch && ourSwitch == sideCheck) { // If going to switch and we can actually do the switch
			std::cout << "Doing our switch good" << std::endl;
			commands.push_back(new PIDDriveStraight(155.275));	//zooming out to the middle of the switch and determinging where to go from there
			if (doScale) {
				std::cout << "We're try hards and doing both" << std::endl;
				if (scale == sideCheck) {
					std::cout << "It's on our side thankfully" << std::endl;
					// command group for positioning from mid-zone to the closest side of the balance, then placing
					commands.push_back(new PIDDriveStraight(184));			//driving to the scale zone
					commands.push_back(new PIDTurn(90 * directionScale));	////turning towards it
					//commands.push_back(new ElevatorRunToHeight(0.0, 0.0));	// TODO put in actual height or whatever
					commands.push_back(new PIDDriveStraight(12));			//zoom into it
//					commands.push_back(new CubeRunIntake(-1.0));			//bye bye cube
				} else {
					std::cout << "Darn, it's all the way over there" << std::endl;
					// command group for moving across mid-zone to the farthest side of the balance, then placing
					commands.push_back(new PIDDriveStraight(64));			//driving a little farther than the switch
					commands.push_back(new PIDTurn(90 * directionScale));	//turning to go around
					commands.push_back(new PIDDriveStraight(190));			//going down past the switch
					commands.push_back(new PIDTurn(90 * -directionScale));	//turning the opposite way
					commands.push_back(new PIDDriveStraight(100));			//zooming to the middle of scale
					commands.push_back(new PIDTurn(90 * -directionScale));	//turning towards the scale
					//commands.push_back(new ElevatorRunToHeight(0.0, 0.0));//TODO Add in correct height
					commands.push_back(new PIDDriveStraight(17.5));			//zoom at scale
//					commands.push_back(new CubeRunIntake(-1.0));			//bye bye cube
				}
			} else {
				std::cout << "We're normal and just gonna do the easy stuff" << std::endl;
				commands.push_back(new PIDTurn(90 * -directionSwitch));		//turning towards the switch to drop cube
				commands.push_back(new PIDDriveStraight(24)); 				//TODO Add in correct distance
//				commands.push_back(new CubeRunIntake(-1.0));				//bye bye cube
			}
			//if we aren't doing the scale, just don't move since we technically crossed the auto line anyway
		} else if (doSwitch && ourSwitch != sideCheck) {
			std::cout << "Doing our switch good" << std::endl;
			commands.push_back(new PIDDriveStraight(220));			//driving out past the switch so we can go around
			commands.push_back(new PIDTurn(90 * directionSwitch));	//turning to go around
			commands.push_back(new PIDDriveStraight(230));			//zomming arround back
			commands.push_back(new PIDTurn(90 * directionSwitch));	//turning again
			commands.push_back(new PIDDriveStraight(66));			//zooming onto side
			commands.push_back(new Pause(0.2));
			commands.push_back(new PIDTurn(90 * directionSwitch));	//and again....
			commands.push_back(new PIDDriveStraight(34));			//zooming into it
		} else if (doScale) {
			std::cout << "Gonna go be tall cause we ate our veggies" << std::endl;
			//move to common baseline zone + move to mid-zone of alliance
			std::cout << "Scale Side: " << scale << "; Start Spot: " << sideCheck << std::endl;
			if (scale == sideCheck){
				std::cout << "Less work cause it's on our side" << std::endl;
				// command group for positioning from mid-zone to closest side of the balance, then placing
				commands.push_back(new PIDDriveStraight(24.0));
				commands.push_back(new UltrasonicStraightDrive(0.75, 290, trackingSide)); //294	//driving with sensros down da wall
				commands.push_back(new PIDTurn(90 * directionScale));						//turning towards the scale
				//commands.push_back(new ElevatorRunToHeight(0.0, 0.0)); 						// TODO put in actual height or whatever
				commands.push_back(new PIDDriveStraight(12));	//18							//zoom at scale
//				commands.push_back(new CubeRunIntake(-1.0));								//bye bye cube
			} else {
				std::cout << "It's all the way over there....Need more veggies" << std::endl;
				// command group for moving across mid-zone to farthest side of the balance, then placing
				commands.push_back(new UltrasonicStraightDrive(0.75, 222, trackingSide));	//drive with sensors down the wall
				commands.push_back(new PIDTurn(90 * directionScale));						//turn to go across the back of switch
				commands.push_back(new PIDDriveStraight(236));								//zoom to other side
				commands.push_back(new PIDTurn(90 * -directionScale));						//turn to face opposite end of field
				commands.push_back(new PIDDriveStraight(87));								//drive to null zone
				commands.push_back(new PIDTurn(90 * -directionScale));						//turn to the scale
				//commands.push_back(new ElevatorRunToHeight(0.0, 0.0));						// TODO put in actual height or whatever
				commands.push_back(new PIDDriveStraight(18));								//zoom at the scale
//				commands.push_back(new CubeRunIntake(-1.0));								//bye bye cube
			}
		} else {
			std::cout << "One too many cookies....Gonna just go straight" << std::endl;
			commands.push_back(new PIDDriveStraight(90)); 	//Or whatever the cross baseline distance is
		}
	} else {
		std::cout << "Something went wrong. Aborting logic checking and driving straight" << std::endl;
		commands.push_back(new PIDDriveStraight(90)); 	//Or whatever the cross baseline distance is
	}
	commands.push_back(new PrintCurrentFPGATime());
	autonomousCommand.reset(new CMG_AutoGenerated(commands));
}

void Robot::AutonomousInit() {
	std::cout << "Starting auto..." << std::endl;
	Robot::drivetrain->ResetEncoders();
	Robot::elevator->ResetMagneticEncoder();
	RobotMap::drivetrainRearLeftMotor->SetNeutralMode(NeutralMode::Brake);
	RobotMap::drivetrainRearRightMotor->SetNeutralMode(NeutralMode::Brake);
	this->PickAuto();
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
