#include "NavXSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/Pause.h"
#include "../Util.h"

//keep in mind for future if classdef error on constants, do this
const double NavXSubsystem::NAVX_P_VALUE = 0.03;
const double NavXSubsystem::NAVX_I_VALUE = 0.00;
const double NavXSubsystem::NAVX_D_VALUE = 0.00;
const double NavXSubsystem::NAVX_F_VALUE = 0.00;

NavXSubsystem::NavXSubsystem() : Subsystem("NavXSubsystem") {
	xData.name = 'x';
	yData.name = 'y';
	zData.name = 'z';
	zData.collisionThreshold = 0.5;
}

void NavXSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ::UpdateCollisionData());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void NavXSubsystem::UpdateAccelerations(char name) {
	if (name == xData.name) {
		xData.currentAccel = RobotMap::navX->GetWorldLinearAccelX();
		collisionData.currentAccel = xData.currentAccel;
	} else if (name == yData.name) {
		yData.currentAccel = RobotMap::navX->GetWorldLinearAccelY();
		collisionData.currentAccel = yData.currentAccel;
	} else if (name == zData.name) {
		zData.currentAccel = RobotMap::navX->GetWorldLinearAccelZ();
		collisionData.currentAccel = zData.currentAccel;
	}
}

void NavXSubsystem::UpdateCollisionCounters(char name) {
	if (name == xData.name) {
		if (xData.collided) {
			xData.collisionCount += 1;
		}
	} else if (name == yData.name) {
		if (yData.collided) {
			yData.collisionCount += 1;
		}
	} else if (name == zData.name) {
		if (zData.collided) {
			zData.collisionCount += 1;
		}
	}
}

void NavXSubsystem::UpdateCollisions(char name) {
	collisionData.collided = (fabs(collisionData.currentAccel) > collisionData.collisionThreshold) ? true : false;
	if (name == xData.name) {
		xData.collided = collisionData.collided;
	} else if (name == yData.name) {
		yData.collided = collisionData.collided;
	} else if (name == zData.name) {
		zData.collided = collisionData.collided;
	}
}

void NavXSubsystem::UpdateTopTens(char name) {
	if (name == xData.name) {
		xData.TopTenList = BuildTopTen(xData.TopTenList, xData.currentAccel);
		if (xData.LastTopTen != xData.TopTenList) {
			std::cout << "X-Values:" << std::endl;
			Util::PrintDoublesList(xData.TopTenList);
		}
		xData.LastTopTen = xData.TopTenList;
	} else if (name == yData.name) {
		yData.TopTenList = BuildTopTen(yData.TopTenList, yData.currentAccel);
		if (yData.LastTopTen != yData.TopTenList) {
			std::cout << "Y-Values:" << std::endl;
			Util::PrintDoublesList(yData.TopTenList);
		}
		yData.LastTopTen = yData.TopTenList;
	} else if (name == zData.name) {
		zData.TopTenList = BuildTopTen(zData.TopTenList, zData.currentAccel);
		if (zData.LastTopTen != zData.TopTenList) {
			std::cout << "Z-Values:" << std::endl;
			Util::PrintDoublesList(zData.TopTenList);
		}
		zData.LastTopTen = zData.TopTenList;
	}
}

std::list<double> NavXSubsystem::BuildTopTen(std::list<double> topTen, double num) {
	if (num > topTen.front()) {
		topTen.push_back(num);
		topTen.sort();
		topTen.unique();
		if (topTen.size() > 10) {
			topTen.pop_front();
		}
	}
	return topTen;
}

void NavXSubsystem::UpdateCollisionData(char name) {
	NavXSubsystem::UpdateAccelerations(name);
	NavXSubsystem::UpdateCollisions(name);
	NavXSubsystem::UpdateCollisionCounters(name);
	NavXSubsystem::UpdateTopTens(name);
}
