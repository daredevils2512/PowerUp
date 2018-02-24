/*
 * DriverstationFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_DriverstationFrame_H_
#define SRC_DASHBOARD_FRAMES_DriverstationFrame_H_

#include "Frame.h"

class DriverstationFrame: public Frame {
public:
	DriverstationFrame(std::string path);
	virtual ~DriverstationFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:
	std::string GetMode();

	std::string path;

	bool enabled;
	bool enabled_dirty;

	bool estopped;
	bool estopped_dirty;

	std::string mode;
	bool mode_dirty;

	bool dsAttached;
	bool dsAttached_dirty;

	bool fmsAttached;
	bool fmsAttached_dirty;

	double batteryVoltage;
	bool batteryVoltage_dirty;

	/*
		"enabled":false, // put example of type (boolean = true, number = 1, etc)
		"estopped":false,
		"mode":"teleop",
		"dsAttached":false,
		"fmsAttached":false,
		"batteryVoltage":12.5
	 */
};

#endif /* SRC_COMM_FRAMES_DriverstationFrame_H_ */
