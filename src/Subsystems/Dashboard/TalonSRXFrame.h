/*
 * TalonSRXFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_TALONSRXFRAME_H_
#define SRC_DASHBOARD_FRAMES_TALONSRXFRAME_H_

#include "Frame.h"


class TalonSRXFrame: public Frame {
public:
	TalonSRXFrame(const std::string& path, WPI_TalonSRX* talonSRX);
	virtual ~TalonSRXFrame();
	void Broadcast();
private:
	WPI_TalonSRX* talon;
	std::string GetFaultString();


	/*
	    "id":0,
		"alive":true,
		"controlMode":"Disabled",
		"value":0.0,
		"safetyEnabled":true,
		"outputCurrent":0, //amps
		"temperature":0,
		"firmwareVersion":"3.x",
		"faults":{
			"underVoltage":false,
		 	"forwardLimitSwitch":false,
		 	"reverseLimitSwitch":false,
		 	"forwardSoftLimit":false,
		 	"reverseSoftLimit":false,
		 	"hardwareFailure":false,
		 	"resetDuringEn":false,
		 	"sensorOverflow":false,
		 	"sensorOutOfPhase":false,
		 	"hardwareESDReset":false,
		 	"remoteLossOfSignal":false
		}
	 */
};

#endif /* SRC_DASHBOARD_FRAMES_TALONSRXFRAME_H_ */
