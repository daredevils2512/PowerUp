/*
 * DoubleSolenoidFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "DoubleSolenoidFrame.h"

DoubleSolenoidFrame::DoubleSolenoidFrame(std::string path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel) {
	this->doubleSolenoid = doubleSolenoid;
	this->path = path;

	this->forwardChannel = forwardChannel;
	this->reverseChannel = reverseChannel;
	value = GetValue();

	MarkAllDirty();
}

std::string DoubleSolenoidFrame::GetValue(){
	switch(doubleSolenoid->Get()){
	case frc::DoubleSolenoid::kForward:
		return "forward";
	case frc::DoubleSolenoid::kReverse:
		return "reverse";
	case frc::DoubleSolenoid::kOff:
		return "off";
	default:
		return "uh";
	}
}

void DoubleSolenoidFrame::MarkAllDirty(){
	forwardChannel_dirty = true;
	reverseChannel_dirty = true;
	value_dirty = true;
}
DoubleSolenoidFrame::~DoubleSolenoidFrame(){
	// no thanks :(
}

void DoubleSolenoidFrame::Broadcast(){
	if(forwardChannel_dirty){
		SocketClient::SendIntData(path + ".forwardChannel",forwardChannel);
		forwardChannel_dirty = false;
	}

	if(reverseChannel_dirty){
		SocketClient::SendIntData(path + ".reverseChannel",reverseChannel);
		reverseChannel_dirty = false;
	}

	if(value_dirty){
		SocketClient::SendStringData(path + ".value",value);
		value_dirty = false;
	}
}

void DoubleSolenoidFrame::Update(){
	if(value != GetValue()){
		value = GetValue();
		value_dirty = true;
	}
}

