/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

#include <map>

#include "Dashboard/LimitSwitchFrame.h"
#include "Dashboard/TalonSRXFrame.h"
#include "Dashboard/EncoderFrame.h"
#include "Dashboard/DoubleSolenoidFrame.h"
#include "Dashboard/DriverstationFrame.h"
#include "Dashboard/MatchFrame.h"

#include "Dashboard/Socket/SocketClient.h"

class DareDashboard : public frc::Subsystem {
private:
	std::map<std::string, Frame*> frames;
public:
	DareDashboard();
	void InitDefaultCommand() override;
	void Update();
	bool IsConnected();
	/*
	 * TalonSRX
	 * LimitSwitch (digital input)
	 * Ultrasonic Subsystem
	 * Encoders (digital input)
	 * DoubleSolenoids
	 */

	void RegisterTalonSRX(std::string path, WPI_TalonSRX* talon);

	void RegisterLimitSwitch(std::string path, frc::DigitalInput* limitSwitch);

	//void RegisterUltrasonics(std::string path, UltrasonicSubsystem ultrasonicSubsystem);

	//Reminder to associate path with talon
	void RegisterEncoder(std::string path, frc::Encoder* encoder, int aChannel, int bChannel);

	void RegisterDoubleSolenoid(std::string path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel);

};

