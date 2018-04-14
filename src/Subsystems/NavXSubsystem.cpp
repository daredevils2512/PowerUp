#include "NavXSubsystem.h"
#include "../RobotMap.h"

//keep in mind for future if classdef error on constants, do this
const double NavXSubsystem::NAVX_P_VALUE = 0.03;
const double NavXSubsystem::NAVX_I_VALUE = 0.00;
const double NavXSubsystem::NAVX_D_VALUE = 0.00;
const double NavXSubsystem::NAVX_F_VALUE = 0.00;

NavXSubsystem::NavXSubsystem() : Subsystem("ExampleSubsystem") {
	xData.name = 'x';
	yData.name = 'y';
	zData.name = 'z';
	zData.collisionThreshold = 0.5;
}

void NavXSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void NavXSubsystem::UpdateAccelerations(char name) {
	if (name == xData.name) {
		xData.currentAccel = RobotMap::navX->GetWorldLinearAccelX();
	} else if (name == yData.name) {
		yData.currentAccel = RobotMap::navX->GetWorldLinearAccelY();
	} else if (name == zData.name) {
		zData.currentAccel = RobotMap::navX->GetWorldLinearAccelZ();
	}
}

void NavXSubsystem::UpdateCollisionCounters(CollisionData collisionData) {
	if (collisionData.collided) {
		collisionData.collisionCount += 1;
	}
}

void NavXSubsystem::UpdateCollisions(NavXSubsystem::CollisionData collisionData) {
	collisionData.collided = (fabs(collisionData.currentAccel) > collisionData.collisionThreshold) ? true : false;
}

void NavXSubsystem::UpdateTopTens(NavXSubsystem::CollisionData collisionData, int num) {
	collisionData.TopTen.push_back(num);
	std::sort(collisionData.TopTen.begin(), collisionData.TopTen.end());
	while (collisionData.TopTen.size() > 10) {
		collisionData.TopTen.erase(collisionData.TopTen.begin());
	}
}

void NavXSubsystem::UpdateCollisionData(NavXSubsystem::CollisionData collisionData, char name) {
	NavXSubsystem::UpdateCollisionCounters(collisionData);
	NavXSubsystem::UpdateCollisions(collisionData);
	NavXSubsystem::UpdateAccelerations(name);
//	NavXSubsystem::UpdateTopTens(collisionData, collisionData.currentAccel);
}
