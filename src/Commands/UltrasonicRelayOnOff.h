#ifndef UltrasonicRelayOnOff_H
#define UltrasonicRelayOnOff_H

#include <Commands/Command.h>

class UltrasonicRelayOnOff : public frc::Command {
public:
	UltrasonicRelayOnOff(double relayID);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_relayID = 0.0;
};

#endif  // UltrasonicRelayOnOff_H
