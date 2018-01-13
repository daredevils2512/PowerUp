/*
 * Util.cpp
 *
 *  Created on: Jan 12, 2018
 *      Author: Daredevils-Prog-1
 */

#include <Util.h>
#include <WPILib.h>

void Util::ReportError(std::string errorMessage){
	frc::DriverStation::GetInstance().ReportError(true,2512,errorMessage,"","");
}

void Util::ReportWarning(std::string warningMessage){
	frc::DriverStation::GetInstance().ReportError(false,2512,warningMessage,"","");
}
