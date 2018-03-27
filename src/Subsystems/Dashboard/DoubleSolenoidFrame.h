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
	DoubleSolenoidFrame(const std::string& path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel);
	virtual ~DoubleSolenoidFrame();
	void Broadcast();

private:

	std::string GetValue();

	frc::DoubleSolenoid* doubleSolenoid;

};

#endif /* SRC_COMM_FRAMES_DoubleSolenoidFrame_H_ */
