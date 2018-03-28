/*
 * DriverstationFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "DriverstationFrame.h"
#include <HAL/HAL.h>

DriverstationFrame::DriverstationFrame(const std::string& path) : Frame(path) {
	HAL_GetControlWord(&w);
}

std::string DriverstationFrame::GetMode(){
	frc::DriverStation& ds = frc::DriverStation::GetInstance();
	if(ds.GetMatchType() == frc::DriverStation::MatchType::kPractice){
		return "practice";
	}
	if(ds.IsAutonomous()){
		return "auto";
	}
	if(ds.IsOperatorControl()){
		return "teleop";
	}
	if(ds.IsTest()){
		return "test";
	}
	return "unknown";
}

DriverstationFrame::~DriverstationFrame(){
	// no thanks :(
}

void DriverstationFrame::Broadcast(){
	/*
			"enabled":false, // put example of type (boolean = true, number = 1, etc)
			"estopped":false,
			"mode":"teleop",
			"dsAttached":false,
			"fmsAttached":false,
			"batteryVoltage":12.5
		 */
	frc::DriverStation& ds = frc::DriverStation::GetInstance();

		Connection::SendData(path + ".enabled", ds.IsEnabled());
		Connection::SendData(path + ".estopped", to_string(w.eStop));
		Connection::SendData(path + ".mode",GetMode());
		Connection::SendData(path + ".dsAttached", ds.IsDSAttached());
		Connection::SendData(path + ".fmsAttached", ds.IsFMSAttached());
		Connection::SendData(path + ".batteryVoltage",to_string(ds.GetBatteryVoltage()));

}


