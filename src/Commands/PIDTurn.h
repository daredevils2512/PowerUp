#ifndef PIDTurn_H
#define PIDTurn_H

#include "WPILib.h"

class PIDTurn : public frc::Command {
public:

	 enum PIDSettings {
		CARPET90
	};

	PIDTurn(PIDSettings settings, double goalAngle);
	PIDTurn(double goalAngle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDSettings m_settings;
	double m_angle;

};

#endif  // PIDTurn_H
