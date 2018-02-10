/*
 * Ultrasonic.cpp
 *
 *  Created on: Feb 8, 2018
 *      Author: noahg
 */

#include "UltrasonicSensor.h"
#include "Util.h"

UltrasonicSensor::UltrasonicSensor(frc::AnalogInput* ultrasonicInput) {
	// TODO Auto-generated constructor stub
	this->ultrasonicInput = ultrasonicInput;
	this->ultrasonicInput->SetAverageBits(50);
	this->ultrasonicInput->SetOversampleBits(2);
}

frc::AnalogInput* UltrasonicSensor::GetAnalogInput() {
	return ultrasonicInput;
}

double UltrasonicSensor::GetDistance() {
	double voltagePerCm = Util::SUPPLIED_VOLTAGE/1024;
	double distanceCm = ultrasonicInput->GetAverageVoltage()/voltagePerCm;
	return distanceCm/2.54; // to inches
}

