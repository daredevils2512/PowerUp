#ifndef PIDDriveStraight_H
#define PIDDriveStraight_H

#include "WPILib.h"

class PIDDriveStraight : public frc::Command {
public:
	 enum PIDSettings {
		CARPET90
	};

	PIDDriveStraight(PIDSettings settings, double goalDistance);
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
};

#endif  // PIDDriveStraight_H
