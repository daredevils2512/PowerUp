/*
 * LimitSwitchFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "LimitSwitchFrame.h"

LimitSwitchFrame::LimitSwitchFrame(const std::string& path, frc::DigitalInput* limitSwitch) : Frame(path){
	this->limitSwitch = limitSwitch;
}

LimitSwitchFrame::~LimitSwitchFrame(){
	// no thanks :(
}

void LimitSwitchFrame::Broadcast(){
		Connection::SendData(path + ".activated",limitSwitch->Get());
		Connection::SendData(path + ".channel",limitSwitch->GetChannel());
}

