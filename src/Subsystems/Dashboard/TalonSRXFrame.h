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
	TalonSRXFrame(std::string path, WPI_TalonSRX* talonSRX);
	virtual ~TalonSRXFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:
	WPI_TalonSRX* talon;

	std::string path;

	int id;
	bool alive;
	ControlMode controlMode;
	double value;
	bool safetyEnabled;
	double outputCurrent;
	double temperature;
	int version;
	std::string faults;

	std::string GetFaultString();

	bool id_dirty;
	bool alive_dirty;
	bool controlMode_dirty;
	bool value_dirty;
	bool safetyEnabled_dirty;
	bool outputCurrent_dirty;
	bool temperature_dirty;
	bool version_dirty;
	bool faults_dirty;
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
