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
	DriverstationFrame(const std::string& path);
	virtual ~DriverstationFrame();
	void Broadcast();

private:
	std::string GetMode();
	HAL_ControlWord w;



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
