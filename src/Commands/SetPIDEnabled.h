#ifndef SetPIDEnabled_H
#define SetPIDEnabled_H

#include <WPILib.h>

class SetPIDEnabled : public frc::Command {
public:
	SetPIDEnabled(bool enabled);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool m_enabled;
};

#endif  // SetPIDEnabled_H
