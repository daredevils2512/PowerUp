/*
 * LimitSwitchFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_LIMITSWITCHFRAME_H_
#define SRC_DASHBOARD_FRAMES_LIMITSWITCHFRAME_H_

#include "Frame.h"


class LimitSwitchFrame: public Frame {
public:
	LimitSwitchFrame(const std::string& path, frc::DigitalInput* limitSwitch);
	virtual ~LimitSwitchFrame();

	void Broadcast();

private:
	frc::DigitalInput* limitSwitch;
};

#endif /* SRC_COMM_FRAMES_LimitSwitchFrame_H_ */
