#ifndef UltrasonicStoreLastValue_H
#define UltrasonicStoreLastValue_H

#include "Commands/Command.h"
#include <WPILib.h>
#include "../Robot.h"

class UltrasonicStoreLastValue : public frc::Command {
public:
	UltrasonicStoreLastValue(Util::RobotSide robotSide, UltrasonicSubsystem::SensorSide side, int arrayVal);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	//double m_valid;
	UltrasonicSubsystem::SensorSide m_side;
	Util::RobotSide m_robotSide;
	int m_arrayVal;
};

#endif  // UltrasonicStoreLastValue_H
