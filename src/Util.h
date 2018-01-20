/*
 * Util.h
 *
 *  Created on: Jan 12, 2018
 *      Author: Daredevils-Prog-1
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>

class Util {
	public:
		//Keeping all the constants in one place
		static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 2; //ports for Aries drivetrain, change for comp robot
		static const int DRIVETRAIN_REAR_LEFT_MOTOR = 1;
		static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 10;
		static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 6;
		static constexpr double SUPPLIED_VOLTAGE = 4.96;
		static constexpr double ULTRASONIC_TOLERANCE = 3.0;

		//keeping all the functions that can be used everywhere
		static void ReportError(std::string errorMessage);
		static void ReportWarning(std::string warningMessage);
		static bool IsInTolerance(double tolerance, double firstValue, double secondValue);
};

#endif /* SRC_UTIL_H_ */
