#ifndef NavXSubsystem_H
#define NavXSubsystem_H

#include <Commands/Subsystem.h>
#include <vector>

class NavXSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	struct CollisionData {
		char name;
		bool collided;
		int collisionCount;
		double currentAccel;
		std::vector<double> TopTen;
		double collisionThreshold;
	} xData, yData, zData;

	NavXSubsystem();
	void InitDefaultCommand();
	void UpdateAccelerations(char name);
	void UpdateCollisions(CollisionData collisionData);
	void UpdateCollisionCounters(CollisionData collisionData);
	void UpdateTopTens(CollisionData collisionData, int num);
	void UpdateCollisionData(CollisionData collisionData, char name);

	const static double NAVX_P_VALUE;
	const static double NAVX_I_VALUE;
	const static double NAVX_D_VALUE;
	const static double NAVX_F_VALUE;

};

#endif  // NavXSubsystem_H
