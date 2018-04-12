#ifndef PIDTurn_H
#define PIDTurn_H

#include "WPILib.h"

class PIDTurn : public frc::Command {
public:

	 enum PIDSettings {
		CARPET90
	};

	PIDTurn(PIDSettings settings, double goalAngle , double maxOutput, double timeout = 3.0);
	PIDTurn(double goalAngle, double maxOutput = 0.75, double timeout = 3.0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDSettings m_settings;
	double m_angle;
	double m_maxoutput;

};

#endif  // PIDTurn_H
