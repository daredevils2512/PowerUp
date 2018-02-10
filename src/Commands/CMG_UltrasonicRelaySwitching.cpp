#include <WPILib.h>

#include "CMG_UltrasonicRelaySwitching.h"
#include "Commands/UltrasonicRelayOnOff.h"
#include "Commands/UltrasonicRelaysOff.h"
#include "Commands/UltrasonicStoreLastValue.h"
#include "../Robot.h"


CMG_UltrasonicRelaySwitching::CMG_UltrasonicRelaySwitching() {
	Requires(Robot::ultrasonicSubsystem.get());

	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	std::cout << "Running CMG" << std::endl;
	AddSequential(new UltrasonicRelaysOff());
	AddSequential(new UltrasonicRelayOnOff(1));
	AddSequential(new frc::WaitCommand(0.15)); //0.15, 0.25
	std::cout <<"Saving Value 1" << std::endl;
	AddSequential(new UltrasonicStoreLastValue(Util::RobotSide::leftSide, UltrasonicSubsystem::SensorSide::frontSensor, 0));
	AddSequential(new UltrasonicStoreLastValue(Util::RobotSide::leftSide, UltrasonicSubsystem::SensorSide::rearSensor, 1));
	AddSequential(new UltrasonicRelayOnOff(1)); //save value from 1
	AddSequential(new UltrasonicRelayOnOff(2)); //save value from 2
	AddSequential(new frc::WaitCommand(0.15)); //.15
	std::cout <<"Saving Value 2" << std::endl;
	AddSequential(new UltrasonicStoreLastValue(Util::RobotSide::leftSide, UltrasonicSubsystem::SensorSide::frontSensor, 2));
	AddSequential(new UltrasonicStoreLastValue(Util::RobotSide::leftSide, UltrasonicSubsystem::SensorSide::rearSensor, 3));

}
