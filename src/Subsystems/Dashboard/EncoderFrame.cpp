/*
 * EncoderFrame.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Programming
 */

#include "EncoderFrame.h"

EncoderFrame::EncoderFrame(const std::string& path, frc::Encoder* encoder, int aChannel, int bChannel) : Frame(path){
	this->encoder = encoder;

	this->aChannel = aChannel;
	this->bChannel = bChannel;
}

EncoderFrame::~EncoderFrame(){
	// no thanks :(
}

void EncoderFrame::Broadcast(){

	/*
	rawValue = encoder->GetRaw();
	period = encoder->GetPeriod();
	encodingScale = encoder->GetEncodingScale();
	distancePerPulse = encoder->GetDistancePerPulse();
	direction = encoder->GetDirection();
	distance = encoder->GetDistance();
	rate = encoder->GetRate();
	samplesToAverage = encoder->GetSamplesToAverage();
	*/

		Connection::SendData(path + ".aChannel", to_string(aChannel));
		Connection::SendData(path + ".bChannel", to_string(bChannel));
		Connection::SendData(path + ".count",to_string(encoder->Get()));
		Connection::SendData(path + ".rawValue",to_string(encoder->GetRaw()));
		Connection::SendData(path + ".period", to_string(encoder->GetPeriod()));
		Connection::SendData(path + ".encodingScale", to_string(encoder->GetEncodingScale()));
		Connection::SendData(path + ".distancePerPulse",to_string(encoder->GetDistancePerPulse()));
		Connection::SendData(path + ".direction",encoder->GetDirection());


		Connection::SendData(path + ".distance", to_string(encoder->GetDistance()));



		Connection::SendData(path + ".rate", to_string(encoder->GetRate()));


		Connection::SendData(path + ".samplesToAverage", to_string(encoder->GetSamplesToAverage()));



}
