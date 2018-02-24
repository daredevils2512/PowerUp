/*
 * DoubleSolenoidFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_DoubleSolenoidFrame_H_
#define SRC_DASHBOARD_FRAMES_DoubleSolenoidFrame_H_

#include "Frame.h"


class DoubleSolenoidFrame: public Frame {
public:
	DoubleSolenoidFrame(std::string path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel);
	virtual ~DoubleSolenoidFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:

	std::string GetValue();

	frc::DoubleSolenoid* doubleSolenoid;

	std::string path;

	int forwardChannel;
	int reverseChannel;
	std::string value;

	bool forwardChannel_dirty;
	bool reverseChannel_dirty;
	bool value_dirty;

	/*

	 */
};

#endif /* SRC_COMM_FRAMES_DoubleSolenoidFrame_H_ */
