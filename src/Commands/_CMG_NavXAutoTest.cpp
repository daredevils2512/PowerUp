#include "_CMG_NavXAutoTest.h"
#include "PIDDriveStraight.h"
#include "PIDTurn.h"
#include "Pause.h"

_CMG_NavXAutoTest::_CMG_NavXAutoTest() {
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
	AddSequential(new PIDDriveStraight(19));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-45));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(32));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(45));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(75.5));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(90));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(22));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-90));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(38));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-65));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(23));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(65));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(24));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(45));
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(34));
	AddSequential(new Pause(0.25));

}
