#include "_CMG_UltrasonicAutoTest.h"
#include "UltrasonicStraightDrive.h"
#include "AutoStraightDrive.h"
#include "PIDTurn.h"
#include "Pause.h"

_CMG_UltrasonicAutoTest::_CMG_UltrasonicAutoTest() {
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
	AddSequential (new UltrasonicStraightDrive(0.65, 164, Util::RobotSide::leftSide)); //0.5 for all//276//MAX SPEED 70
	AddSequential (new Pause(0.25));
	AddSequential (new AutoStraightDrive (12, -0.65));//48.0
	AddSequential (new Pause(0.25));
	AddSequential (new PIDTurn(-180)); //180
	AddSequential (new Pause(0.25));
	AddSequential (new AutoStraightDrive (8.0, 0.65));
	AddSequential (new Pause(0.25));
	AddSequential (new UltrasonicStraightDrive(0.65, 110, Util::RobotSide::leftSide)); //196


}
