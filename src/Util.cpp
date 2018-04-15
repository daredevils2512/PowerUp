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

bool Util::IsInTolerance(double tolerance, double firstObject, double secondObject) {
	//determining if two objects are within a certain range of each other
	double tol = tolerance / 2;
	return (firstObject - tol <= secondObject && firstObject + tol >= secondObject) &&
		   (secondObject - tol <= firstObject && secondObject + tol >= firstObject);
}

// trim from start (in place)
void Util::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void Util::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void Util::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Util::PrintDoublesList(std::list<double> list) {
	std::cout << "[" << std::endl;
	for (int i = 0; i < int(list.size() - 1); i++) {
		std::cout << list.front() << "," << std::endl;
		list.pop_front();
	}
	std::cout << "]" << std::endl;
}
