/*
 * MatchFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "MatchFrame.h"
#include <chrono>

MatchFrame::MatchFrame(std::string path) {
	this->path = path;

	frc::DriverStation& ds = frc::DriverStation::GetInstance();

	eventName = ds.GetEventName();

	gameMessage = ds.GetGameSpecificMessage();

	type = GetMatchType(); //match type

	number = ds.GetMatchNumber(); //match number

	replay = ds.GetReplayNumber();

	alliance = GetAlliance();

	dslocation = ds.GetLocation();

	startTime = GetMatchStartTime();

	MarkAllDirty();
}

void MatchFrame::MarkAllDirty(){
	eventName_dirty = true;
	gameMessage_dirty = true;
	type_dirty = true;
	number_dirty = true;
	replay_dirty = true;
	alliance_dirty = true;
	dslocation_dirty = true;
	startTime_dirty = true;
}

std::string MatchFrame::GetMatchType(){
	switch(frc::DriverStation::GetInstance().GetMatchType()){
		case frc::DriverStation::MatchType::kElimination: return "elimination";
		case frc::DriverStation::MatchType::kQualification: return "qualification";
		case frc::DriverStation::MatchType::kPractice: return "practice";
		case frc::DriverStation::MatchType::kNone: return "none";
	}
	return "unknown";
}

std::string MatchFrame::GetAlliance() {
	switch (frc::DriverStation::GetInstance().GetAlliance()){
		case frc::DriverStation::Alliance::kBlue:
			return "blue";
		case frc::DriverStation::Alliance::kRed:
			return "red";
		default:
			return "invalid";
	}
}

long MatchFrame::GetMatchStartTime(){
	frc::DriverStation& ds = frc::DriverStation::GetInstance();
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

void MatchFrame::Broadcast(){
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
	if(eventName_dirty){
		RobotClient::SendStringData(path + ".eventName", eventName);
		eventName_dirty = false;
	}

	if(gameMessage_dirty){
		RobotClient::SendStringData(path + ".gameMessage", gameMessage);
		gameMessage_dirty = false;
	}

	if(type_dirty){
		RobotClient::SendStringData(path + ".type", type);
		type_dirty = false;
	}

	if(number_dirty){
		RobotClient::SendIntData(path + ".number", number);
		number_dirty = false;
	}

	if(replay_dirty){
		RobotClient::SendIntData(path + ".replay", replay);
		replay_dirty = false;
	}

	if(alliance_dirty){
		RobotClient::SendStringData(path + ".alliance", alliance);
		alliance_dirty = false;
	}

	if(dslocation_dirty){
		RobotClient::SendIntData(path + ".dslocation", dslocation);
		dslocation_dirty = false;
	}

	if(startTime_dirty){
		RobotClient::SendLongData(path + ".startTime", startTime);
		startTime_dirty = false;
	}
}

void MatchFrame::Update(){
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
	frc::DriverStation& ds = frc::DriverStation::GetInstance();

	if(eventName != ds.GetEventName()){
		eventName = ds.GetEventName();
		eventName_dirty = true;
	}

	if(gameMessage != ds.GetGameSpecificMessage()){
		gameMessage = ds.GetGameSpecificMessage();
		gameMessage_dirty = true;
	}

	if(type != GetMatchType()){
		type = GetMatchType(); //match type
		type_dirty = true;
	}

	if(number != ds.GetMatchNumber()){
		number = ds.GetMatchNumber(); //match number
		number_dirty = true;
	}

	if(replay != ds.GetReplayNumber()){
		replay = ds.GetReplayNumber();
		replay_dirty = true;
	}

	if(alliance != GetAlliance()){
		alliance = GetAlliance();
		alliance_dirty = true;
	}

	if(dslocation != ds.GetLocation()){
		dslocation = ds.GetLocation();
		dslocation_dirty = true;
	}

	if(startTime != GetMatchStartTime()){
		startTime = GetMatchStartTime();
		startTime_dirty = true;
	}
}

