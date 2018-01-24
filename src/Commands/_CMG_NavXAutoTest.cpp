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
	AddSequential(new PIDDriveStraight(19));//Straight 1
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-45));//Turn1
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(32));//Straight2
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(45));//Turn 2
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(68));//S 3
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(45)); //T 3 ,90
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(33));//S 4
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-45));//T 4
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(38+6));// S 5
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-70)); //T 5
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(23));// S 6
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(65));//T 6
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(24));//S 7
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(35));//T 7
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(36)); //S 8
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-35)); //T8
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(145));//S 9
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(-90));//T 9
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(16));//S 10
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(90));// T10
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(65));// S 11
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(90)); // T 11
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(84)); // S 12
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(90));// T 12
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(60)); // S 13
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(90));//T 13
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(53));// S14
	AddSequential(new Pause(0.25));
	AddSequential(new PIDTurn(190));// T 14
	AddSequential(new Pause(0.25));
	AddSequential(new PIDDriveStraight(58)); // S15
	AddSequential(new Pause(0.25));

}
