/*
 * DriverstationFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "DriverstationFrame.h"
#include <HAL/HAL.h>

DriverstationFrame::DriverstationFrame(std::string path) {

	this->path = path;

	frc::DriverStation& ds = frc::DriverStation::GetInstance();
	HAL_ControlWord w;
	HAL_GetControlWord(&w);

	enabled = ds.IsEnabled();

	estopped = w.eStop;

	mode = GetMode();

	dsAttached = ds.IsDSAttached();

	fmsAttached = ds.IsFMSAttached();

	batteryVoltage = ds.GetBatteryVoltage();

	MarkAllDirty();
}

void DriverstationFrame::MarkAllDirty(){
	enabled_dirty = true;
	estopped_dirty = true;
	mode_dirty = true;
	dsAttached_dirty = true;
	fmsAttached_dirty = true;
	batteryVoltage_dirty = true;
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
	if(enabled_dirty){
		SocketClient::SendBoolData(path + ".enabled",enabled);
		enabled_dirty = false;
	}

	if(estopped_dirty){
		SocketClient::SendBoolData(path + ".estopped", estopped);
		estopped_dirty = false;
	}

	if(mode_dirty){
		SocketClient::SendStringData(path + ".mode",mode);
		mode_dirty = false;
	}

	if(dsAttached_dirty){
		SocketClient::SendBoolData(path + ".dsAttached",dsAttached);
		dsAttached_dirty = false;
	}

	if(fmsAttached_dirty){
		SocketClient::SendBoolData(path + ".fmsAttached",fmsAttached);
		fmsAttached_dirty = false;
	}

	if(batteryVoltage_dirty){
		SocketClient::SendDoubleData(path + ".batteryVoltage",batteryVoltage);
		batteryVoltage_dirty = false;
	}
}

void DriverstationFrame::Update(){
	frc::DriverStation& ds = frc::DriverStation::GetInstance();
	HAL_ControlWord w;
	HAL_GetControlWord(&w);

	if(enabled != ds.IsEnabled()){
		enabled = ds.IsEnabled();
		enabled_dirty = true;
	}

	if(estopped != w.eStop){
		estopped = w.eStop;
		estopped_dirty = true;
	}

	if(GetMode() != mode){
		mode = GetMode();
		mode_dirty = true;
	}

	if(dsAttached != ds.IsDSAttached()){
		dsAttached = ds.IsDSAttached();
		dsAttached_dirty = true;
	}

	if(fmsAttached != ds.IsFMSAttached()){
		fmsAttached = ds.IsFMSAttached();
		fmsAttached_dirty = true;
	}

	if(batteryVoltage != ds.GetBatteryVoltage()){
		batteryVoltage = ds.GetBatteryVoltage();
		batteryVoltage_dirty = true;
	}
}

