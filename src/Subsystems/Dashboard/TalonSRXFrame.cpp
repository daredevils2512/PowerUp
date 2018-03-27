/*
 * TalonSRXFrame.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#include "TalonSRXFrame.h"

TalonSRXFrame::TalonSRXFrame(std::string path, WPI_TalonSRX* talonSRX) {
	this->talon = talonSRX;
	this->path = path;

	id = this->talon->GetDeviceID();
	alive = this->talon->IsAlive();
	controlMode = this->talon->GetControlMode();
	value = this->talon->Get();
	safetyEnabled = this->talon->IsSafetyEnabled();
	outputCurrent = this->talon->GetOutputCurrent();
	temperature = this->talon->GetTemperature();
	version = this->talon->GetFirmwareVersion();
	faults = "";

	MarkAllDirty();
}

void TalonSRXFrame::MarkAllDirty(){
	id_dirty = true;
	alive_dirty = true;
	controlMode_dirty = true;
	value_dirty = true;
	safetyEnabled_dirty = true;
	outputCurrent_dirty = true;
	temperature_dirty = true;
	version_dirty = true;
	faults_dirty = true;
}

TalonSRXFrame::~TalonSRXFrame(){

}

void TalonSRXFrame::Broadcast(){
	if(id_dirty){
		Connection::SendData(path + ".id", to_string(id));
		id_dirty = false;
	}

	if(alive_dirty){
		Connection::SendData(path + ".alive", to_string(id));
		alive_dirty = false;
	}

	if(controlMode_dirty){
		std::string controlModeRep = "";
		switch(controlMode){
			case ControlMode::Current: controlModeRep="Current"; break;
			case ControlMode::Disabled: controlModeRep="Disabled"; break;
			case ControlMode::Follower: controlModeRep="Follower"; break;
			case ControlMode::MotionMagic: controlModeRep="MotionMagic"; break;
			//case ControlMode::MotionMagicArc: controlModeRep="MotionMagicArc"; break;
			case ControlMode::MotionProfile: controlModeRep="MotionProfile"; break;
			case ControlMode::MotionProfileArc: controlModeRep="MotionProfileArc"; break;
			case ControlMode::PercentOutput: controlModeRep="PercentOutput"; break;
			case ControlMode::Position: controlModeRep="Position"; break;
			case ControlMode::Velocity: controlModeRep="Velocity"; break;
			default: controlModeRep="Unknown"; break;
		}
		Connection::SendData(path + ".controlMode", controlModeRep);
		controlMode_dirty = false;
	}

	if(value_dirty){
		Connection::SendData(path + ".value",value);
		value_dirty = false;
	}

	if(safetyEnabled_dirty){
		Connection::SendData(path + ".safetyEnabled",value);
		safetyEnabled_dirty = false;
	}

	if(outputCurrent_dirty){
		Connection::SendData(path + ".outputCurrent", outputCurrent);
		outputCurrent_dirty = false;
	}

	if(temperature_dirty){
		Connection::SendData(path + ".temperature", to_string(temperature));
		temperature_dirty = false;
	}

	if(version_dirty){
		Connection::SendData(path + ".firmwareVersion",version);
		version_dirty = false;
	}

	if(faults_dirty){
		Connection::SendData(path + ".faults",faults);
		faults_dirty = false;
	}
}

std::string TalonSRXFrame::GetFaultString() {
	Faults localFaults;
	this->talon->GetFaults(localFaults);
	StickyFaults localSFaults;
	this->talon->GetStickyFaults(localSFaults);
	return "|REGULAR|" + localFaults.ToString() + " |STICKY|" + localSFaults.ToString();
}

void TalonSRXFrame::Update(){
	if(id != talon->GetDeviceID()){
		id = talon->GetDeviceID();
		id_dirty = true;
	}
	if(alive != this->talon->IsAlive()){
		alive = this->talon->IsAlive();
		alive_dirty = true;
	}
	if(controlMode != this->talon->GetControlMode()){//TODO mark everything as dirty when it is.
		controlMode = this->talon->GetControlMode();
		controlMode_dirty = true;
	}
	if(value != this->talon->Get()){
		value = this->talon->Get();
		value_dirty = true;
	}
	if(safetyEnabled != this->talon->IsSafetyEnabled()){
		safetyEnabled = this->talon->IsSafetyEnabled();
		safetyEnabled_dirty = true;
	}
	if(outputCurrent != this->talon->GetOutputCurrent()){
		outputCurrent = this->talon->GetOutputCurrent();
		outputCurrent_dirty = true;
	}
	if(temperature != this->talon->GetTemperature()){
		temperature = this->talon->GetTemperature();
		temperature_dirty = true;
	}

	if(version != this->talon->GetFirmwareVersion()){
		version = this->talon->GetFirmwareVersion();
		version_dirty = true;
	}

	std::string faultStr = GetFaultString();
	if(faultStr != faults){
		faults = faultStr;
		faults_dirty = true;
	}

}

