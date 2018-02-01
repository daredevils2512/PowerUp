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

		static const int CLIMBER_LEFT_WING_MOTOR_1 = 0; //theoretical CAN Talong ID's
		static const int CLIMBER_LEFT_WING_MOTOR_2 = 1;
		static const int CLIMBER_RIGHT_WING_MOTOR_1 = 2;
		static const int CLIMBER_RIGHT_WING_MOTOR_2 = 3;

		static const int CUBE_INTAKE_LEFT_MOTOR = 5;
		static const int CUBE_INTAKE_RIGHT_MOTOR = 7;
		static constexpr double LEFT_INCH_PER_PULSE = (1/9.537878); //Inches per pulse for the left encoder
		static constexpr double RIGHT_INCH_PER_PULSE = (1/9.737373); // Inches per pulse for the right encoder

		static const int ULTRASONIC_FRONT_LEFT = 4; //Equivalent to NavX Analog Pin 0
		static const int ULTRASONIC_REAR_LEFT = 5; //Equivalent to NavX Analog Pin 1
		static constexpr double SUPPLIED_VOLTAGE = 4.96; //The voltage sent through the NavX analogInput pins for converting voltage to distance
		static constexpr double ULTRASONIC_TOLERANCE = 0.3; //The acceptable tolerance for comparing the two ultrasonic sensors on a side
		static constexpr double ULTRASONIC_TURN_MULTIPLIER = 0.1; //The amount we reduce motor speed for ultrasonic staightDrive 0.0775//0.0975(current reliable test value)//0.0975

		static const int ELEVATOR_LEFT_MOTOR = 3;
		static const int ELEVATOR_RIGHT_MOTOR = 4;
		static const int ELEVATOR_TOP_LIMIT_SWITCH = 4;
		static const int ELEVATOR_BOTTOM_LIMIT_SWITCH = 5;
		static constexpr double ELEVATOR_MAX_ENCODER_CLICKS = 5000;

		enum class RobotSide {
			unknown,
			leftSide,
			rightSide
		};

		//keeping all the functions that can be used everywhere
		static void ReportError(std::string errorMessage);
		static void ReportWarning(std::string warningMessage);
		static bool IsInTolerance(double tolerance, double firstValue, double secondValue);
};

#endif /* SRC_UTIL_H_ */
