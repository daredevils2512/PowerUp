#ifndef PIDDriveStraight_H
#define PIDDriveStraight_H

#include "WPILib.h"

class PIDDriveStraight : public frc::Command {
public:
	 enum class PIDSettings {
		CARPET90
	};

	PIDDriveStraight(double goalDistance , PIDSettings settings = PIDSettings::CARPET90);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDSettings m_settings;
	double m_distance;
	double navXDistance;
	long lastTime;
	double lastVelX;
	double lastVelY;
	long lastTimeDiff;
	long cumlTime;
};

#endif  // PIDDriveStraight_H
