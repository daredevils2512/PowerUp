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
	LimitSwitchFrame(std::string path, frc::DigitalInput* limitSwitch);
	virtual ~LimitSwitchFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:
	frc::DigitalInput* limitSwitch;

	std::string path;

	bool activated;
	bool activated_dirty;

	int channel;
	bool channel_dirty;

	/*

	 */
};

#endif /* SRC_COMM_FRAMES_LimitSwitchFrame_H_ */
