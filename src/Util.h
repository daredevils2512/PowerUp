/*
 * Util.h
 *
 *  Created on: Jan 12, 2018
 *      Author: Daredevils-Prog-1
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <algorithm>
#include <locale>
#include <cctype>

class Util {
	public:
#ifdef ARIES
		static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 2;
		static const int DRIVETRAIN_REAR_LEFT_MOTOR = 1;
		static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 10;
		static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 6;

#else
		//Keeping all the constants in one place
		static const int DRIVETRAIN_FRONT_LEFT_MOTOR = 1; //2
		static const int DRIVETRAIN_REAR_LEFT_MOTOR = 2; //
		static const int DRIVETRAIN_FRONT_RIGHT_MOTOR = 3; //10
		static const int DRIVETRAIN_REAR_RIGHT_MOTOR = 4; //6
#endif

		static const int CLIMBER = 8;
		static const int CLIMBSERVO1 = 0; //Servos are PWM
		static const int CLIMBSERVO2 = 1;

		static const int CUBE_INTAKE_LEFT_MOTOR = 6;
		static const int CUBE_INTAKE_RIGHT_MOTOR = 7;
		static const int CUBE_INTAKE_LIMIT_SWITCH = 5; //limit switch that will tell us if the cube is fully into the robot

		//Drivetrain encoder clicks per real world inch
#ifdef ARIES
		static constexpr double LEFT_INCH_PER_PULSE = (1/9.537878);
		static constexpr double RIGHT_INCH_PER_PULSE = (1/9.737373);
#else
		static constexpr double LEFT_INCH_PER_PULSE = 0.0236065636; //Inches per pulse for the left encoder //(1/9.537878)
		static constexpr double RIGHT_INCH_PER_PULSE = 0.0236065636; // Inches per pulse for the right encoder //(1/9.737373)
#endif
		static const int ULTRASONIC_FRONT_LEFT = 4; //Equivalent to NavX Analog Pin 0
		static const int ULTRASONIC_REAR_LEFT = 5; //Equivalent to NavX Analog Pin 1
		static const int ULTRASONIC_FRONT_RIGHT = 6; //Analog Pin 2
		static const int ULTRASONIC_REAR_RIGHT = 7; //Analog Pin 3
		static constexpr double SUPPLIED_VOLTAGE = 4.94; //The voltage sent through the NavX analogInput pins for converting voltage to distance //4.96
		static constexpr double ULTRASONIC_ANGLE_TOLERANCE = 0.2; //The acceptable tolerance for comparing the two ultrasonic sensors on a side
		static constexpr double ULTRASONIC_DIST_TOLERANCE = 3.5;
		static constexpr double ULTRASONIC_TURN_MULTIPLIER = 0.10; //The amount we reduce motor speed for ultrasonic staightDrive 0.0775//0.0975(current reliable test value)//0.0975

		static const int ELEVATOR_MOTOR = 5;
		static const int ELEVATOR_BOTTOM_LIMIT_SWITCH = 4;
		static constexpr double ELEVATOR_MAX_ENCODER_HEIGHT = 7.2; //In feet

		enum class RobotSide {
			unknown,
			leftSide,
			rightSide
		};

		//keeping all the functions that can be used everywhere
		static void ReportError(std::string errorMessage);
		static void ReportWarning(std::string warningMessage);
		static bool IsInTolerance(double tolerance, double firstValue, double secondValue);

		static void ltrim(std::string &s);
		static void rtrim(std::string &s);
		static void trim(std::string &s);

};

#endif /* SRC_UTIL_H_ */
