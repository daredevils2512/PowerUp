/*
 * MatchFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "MatchFrame.h"
#include <chrono>

MatchFrame::MatchFrame(const std::string& path) : Frame(path) {
	this->ds = frc::DriverStation::GetInstance();
}

std::string MatchFrame::GetMatchType(){
	switch(ds.GetMatchType()){
		case frc::DriverStation::MatchType::kElimination: return "elimination";
		case frc::DriverStation::MatchType::kQualification: return "qualification";
		case frc::DriverStation::MatchType::kPractice: return "practice";
		case frc::DriverStation::MatchType::kNone: return "none";
	}
	return "unknown";
}

std::string MatchFrame::GetAlliance() {
	switch (ds.GetAlliance()){
		case frc::DriverStation::Alliance::kBlue:
			return "blue";
		case frc::DriverStation::Alliance::kRed:
			return "red";
		default:
			return "invalid";
	}
}

long MatchFrame::GetMatchStartTime(){
	if(  (ds.GetMatchTime() > 0 && ds.IsFMSAttached()) || (ds.IsEnabled() && !ds.IsFMSAttached()) ){
		if(startTime == -1){
			return 1; //1 equals epoch serverside.
		}else{
			return startTime;
		}
	}
	return -1;
}

MatchFrame::~MatchFrame(){
	// no thanks :(
}

/*
	"eventName":"Daredevils",
	"gameMessage":"RRR",
	"type":"none",
	"number":1,
	"replay":0,
	"alliance":"red",
	"dslocation":1,
	"startTime":-1, // in millis
 */
void MatchFrame::Broadcast(){

	Connection::SendData(path + ".eventName", ds.GetEventName());
	Connection::SendData(path + ".gameMessage",  ds.GetGameSpecificMessage());
	Connection::SendData(path + ".type", GetMatchType());
	Connection::SendData(path + ".number", to_string(ds.GetMatchNumber()));
	Connection::SendData(path + ".number", to_string(number));
	Connection::SendData(path + ".replay", to_string(ds.GetReplayNumber()));
	Connection::SendData(path + ".alliance", alliance);
	Connection::SendData(path + ".dslocation", to_string(ds.GetLocation()));
	Connection::SendData(path + ".startTime", to_string(startTime));
}
