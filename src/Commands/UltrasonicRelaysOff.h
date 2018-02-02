#ifndef UltrasonicRelaysOff_H
#define UltrasonicRelaysOff_H

#include <Commands/Command.h>

class UltrasonicRelaysOff : public frc::Command {
public:
	UltrasonicRelaysOff();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // UltrasonicRelaysOff_H
