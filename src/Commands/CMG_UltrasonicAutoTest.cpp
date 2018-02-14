#include <Commands/CMG_UltrasonicAutoTest.h>
#include "UltrasonicStraightDrive.h"
#include "AutoStraightDrive.h"
#include "PIDTurn.h"
#include "Pause.h"

CMG_UltrasonicAutoTest::CMG_UltrasonicAutoTest() {
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
	AddSequential (new UltrasonicStraightDrive(0.65, 150, Util::RobotSide::leftSide)); //0.5 for all//276//MAX SPEED 70
	AddSequential (new Pause(0.20));
	AddSequential (new PIDTurn(180));
	AddSequential (new Pause(0.20));
	AddSequential (new UltrasonicStraightDrive(0.65, 150, Util::RobotSide::rightSide));


}
