#ifndef RelayOnOff_H
#define RelayOnOff_H

#include <Commands/Command.h>

class RelayOnOff : public frc::Command {
public:
	RelayOnOff();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool m_currentState = true;
};

#endif  // RelayOnOff_H
