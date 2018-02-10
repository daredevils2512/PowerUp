/*
 * Ultrasonic.h
 *
 *  Created on: Feb 8, 2018
 *      Author: noahg
 */

#ifndef SRC_ULTRASONICSENSOR_H_
#define SRC_ULTRASONICSENSOR_H_
#include "WPILib.h"


class UltrasonicSensor {
public:
	UltrasonicSensor(frc::AnalogInput* ultrasonicInput);
	double GetDistance();
	frc::AnalogInput* GetAnalogInput();

private:
	frc::AnalogInput* ultrasonicInput;

};

#endif /* SRC_ULTRASONIC_H_ */
