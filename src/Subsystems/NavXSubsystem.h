#ifndef NavXSubsystem_H
#define NavXSubsystem_H

#include <Commands/Subsystem.h>
#include <vector>
#include <list>

#include "../Commands/UpdateCollisionData.h"

class NavXSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	struct CollisionData {
		char name;
		bool collided = false;
		int collisionCount = 0;
		double currentAccel = 0.0;
		std::list<double> TopTenList;
		std::list<double> LastTopTen;
		double collisionThreshold = 0.75;
	} xData, yData, zData, collisionData;

	NavXSubsystem();
	void InitDefaultCommand();
	void UpdateAccelerations(char name);
	void UpdateCollisions(char name);
	void UpdateCollisionCounters(char name);
	void UpdateTopTens(char name);
	std::list<double> BuildTopTen(std::list<double> topTen, double num);
	void UpdateCollisionData(char name);

	const static double NAVX_P_VALUE;
	const static double NAVX_I_VALUE;
	const static double NAVX_D_VALUE;
	const static double NAVX_F_VALUE;

};

#endif  // NavXSubsystem_H
