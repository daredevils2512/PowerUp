#ifndef RelayOnOff_H
#define RelayOnOff_H

#include <Commands/Command.h>

class RelayOnOff : public frc::Command {
public:
	RelayOnOff(double relayID);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_relayID = 0.0;
};

#endif  // RelayOnOff_H
