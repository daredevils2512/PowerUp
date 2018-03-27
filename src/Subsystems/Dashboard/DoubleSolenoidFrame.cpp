/*
 * DoubleSolenoidFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "DoubleSolenoidFrame.h"

DoubleSolenoidFrame::DoubleSolenoidFrame(const std::string& path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel) : Frame(path){
	this->doubleSolenoid = doubleSolenoid;
	this->path = path;
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

DoubleSolenoidFrame::~DoubleSolenoidFrame(){
	// no thanks :(
}

void DoubleSolenoidFrame::Broadcast(){
		Connection::SendData(path + ".value", GetValue());
}
