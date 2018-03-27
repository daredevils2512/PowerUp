/*
 * TalonSRXFrame.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#include "TalonSRXFrame.h"

TalonSRXFrame::TalonSRXFrame(const std::string& path, WPI_TalonSRX* talonSRX) : Frame(path){
	this->talon = talonSRX;
}


TalonSRXFrame::~TalonSRXFrame(){

}

void TalonSRXFrame::Broadcast(){

		Connection::SendData(path + ".id", to_string(this->talon->GetDeviceID()));
		Connection::SendData(path + ".alive", to_string(this->talon->IsAlive()));

		std::string controlModeRep = "";
		switch(this->talon->GetControlMode()){
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
		Connection::SendData(path + ".value",to_string(this->talon->Get()));

		Connection::SendData(path + ".safetyEnabled",this->talon->IsSafetyEnabled());

		Connection::SendData(path + ".outputCurrent", to_string(this->talon->GetOutputCurrent()));
		Connection::SendData(path + ".temperature", to_string(this->talon->GetTemperature()));
		Connection::SendData(path + ".firmwareVersion",this->talon->GetFirmwareVersion());

		Connection::SendData(path + ".faults",GetFaultString());

}

std::string TalonSRXFrame::GetFaultString() {
	Faults localFaults;
	this->talon->GetFaults(localFaults);
	StickyFaults localSFaults;
	this->talon->GetStickyFaults(localSFaults);
	return "|REGULAR|" + localFaults.ToString() + " |STICKY|" + localSFaults.ToString();
}

