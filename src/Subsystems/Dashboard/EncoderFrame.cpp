/*
 * EncoderFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "EncoderFrame.h"

EncoderFrame::EncoderFrame(std::string path, frc::Encoder* encoder, int aChannel, int bChannel) {
	this->encoder = encoder;
	this->path = path;

	this->aChannel = aChannel;
	this->bChannel = bChannel;

	count = encoder->Get();
	rawValue = encoder->GetRaw();
	period = encoder->GetPeriod();
	encodingScale = encoder->GetEncodingScale();
	distancePerPulse = encoder->GetDistancePerPulse();
	direction = encoder->GetDirection();
	distance = encoder->GetDistance();
	rate = encoder->GetRate();
	samplesToAverage = encoder->GetSamplesToAverage();

	MarkAllDirty();
}
void EncoderFrame::MarkAllDirty(){
	aChannel_dirty = true;
	bChannel_dirty = true;
	count_dirty = true;
	rawValue_dirty = true;
	period_dirty = true;
	encodingScale_dirty = true;
	distancePerPulse_dirty = true;
	direction_dirty = true;
	distance_dirty = true;
	rate_dirty = true;
	samplesToAverage_dirty = true;
}
EncoderFrame::~EncoderFrame(){
	// no thanks :(
}

void EncoderFrame::Broadcast(){
	if(aChannel_dirty){
		RobotClient::SendIntData(path + ".aChannel",aChannel);
		aChannel_dirty = false;
	}

	if(bChannel_dirty){
		RobotClient::SendIntData(path + ".bChannel",bChannel);
		bChannel_dirty = false;
	}

	if(count_dirty){
		RobotClient::SendIntData(path + ".count",count);
		count_dirty = false;
	}

	if(rawValue_dirty){
		RobotClient::SendIntData(path + ".rawValue",rawValue);
		rawValue_dirty = false;
	}

	if(period_dirty){
		RobotClient::SendIntData(path + ".period", period);
		period_dirty = false;
	}

	if(encodingScale_dirty){
		RobotClient::SendIntData(path + ".encodingScale",encodingScale);
		encodingScale_dirty = false;
	}

	if(distancePerPulse_dirty){
		RobotClient::SendDoubleData(path + ".distancePerPulse",distancePerPulse);
		distancePerPulse_dirty = false;
	}

	if(direction_dirty){
		RobotClient::SendBoolData(path + ".direction",direction);
		direction_dirty = false;
	}

	if(distance_dirty){
		RobotClient::SendDoubleData(path + ".distance", distance);
		distance_dirty = false;
	}

	if(rate_dirty){
		RobotClient::SendDoubleData(path + ".rate",rate);
		rate_dirty = false;
	}

	if(samplesToAverage_dirty){
		RobotClient::SendIntData(path + ".samplesToAverage",samplesToAverage);
		samplesToAverage_dirty = false;
	}

}

void EncoderFrame::Update(){
	if(count != encoder->Get()){
		count = encoder->Get();
		count_dirty = true;
	}

	if(rawValue != encoder->GetRaw()){
		rawValue = encoder->GetRaw();
		rawValue_dirty = true;
	}

	if(period != encoder->GetPeriod()){
		period = encoder->GetPeriod();
		period_dirty = true;
	}

	if(encodingScale != encoder->GetEncodingScale()){
		encodingScale = encoder->GetEncodingScale();
		encodingScale_dirty = true;
	}

	if(distancePerPulse != encoder->GetDistancePerPulse()){
		distancePerPulse = encoder->GetDistancePerPulse();
		distancePerPulse_dirty = true;
	}

	if(direction != encoder->GetDirection()){
		direction = encoder->GetDirection();
		direction_dirty = true;
	}

	if(distance != encoder->GetDistance()){
		distance = encoder->GetDistance();
		distance_dirty = true;
	}

	if(rate != encoder->GetRate()){
		rate = encoder->GetRate();
		rate_dirty = true;
	}

	if(samplesToAverage != encoder->GetSamplesToAverage()){
		samplesToAverage = encoder->GetSamplesToAverage();
		samplesToAverage_dirty = true;
	}
}

