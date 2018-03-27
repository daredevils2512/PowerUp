/*
 * LimitSwitchFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "LimitSwitchFrame.h"

LimitSwitchFrame::LimitSwitchFrame(std::string path, frc::DigitalInput* limitSwitch) {
	this->limitSwitch = limitSwitch;
	this->path = path;

	activated = limitSwitch->Get();

	channel = limitSwitch->GetChannel();

	MarkAllDirty();
}
void LimitSwitchFrame::MarkAllDirty(){
	activated_dirty = true;
	channel_dirty = true;
}
LimitSwitchFrame::~LimitSwitchFrame(){
	// no thanks :(
}

void LimitSwitchFrame::Broadcast(){
	if(activated_dirty){
		Connection::SendData(path + ".activated",activated);
		activated_dirty = false;
	}

	if(channel_dirty){
		Connection::SendData(path + ".channel",channel);
		channel_dirty = false;
	}
}

void LimitSwitchFrame::Update(){
	if(limitSwitch->Get() != activated){
		activated = limitSwitch->Get();
		activated_dirty = true;
	}

	if(limitSwitch->GetChannel() != channel){
		channel = limitSwitch->GetChannel();
		channel_dirty = true;
	}
}

