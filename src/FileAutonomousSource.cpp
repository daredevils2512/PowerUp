/*
 * FileAutonomousSource.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: noahg
 */

#include <fstream>
#include "FileAutonomousSource.h"

FileAutonomousSource::FileAutonomousSource(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs.good()) {
		std::cout
				<< "ERROR: NO AUTO FILE FOUND. GO HUDDLE IN THE CORNER AND RESEARCH IT"
				<< std::endl;
		std::cout
				<< "So I'm gonna drive straight and get you some points anyway"
				<< std::endl;
		ifs.close();
		startingPosition = Robot::StartLocation::unknown;
	}
	while (!ifs.eof()) { //TODO look into error handling for the cases in which the file is missing or empty
		std::string lastPart;
		std::string firstPart;
		std::getline(ifs, firstPart, ':');
		std::getline(ifs, lastPart);
		while (lastPart[0] == ' ') {
			lastPart = lastPart.substr(1);
		}
		//		if (!ifs.eof()) {
		//			lastPart = lastPart.substr(0, lastPart.size() - 1);
		//		}
		std::cout << firstPart << " - " << lastPart << std::endl;
		//Lowering everything to lowercase to ignore case
		std::transform(firstPart.begin(), firstPart.end(), firstPart.begin(),
				::tolower);
		std::transform(lastPart.begin(), lastPart.end(), lastPart.begin(),
				::tolower);
		if (firstPart == "startposition") {
			if (lastPart == "left") {
				startingPosition = Robot::StartLocation::left;
			} else if (lastPart == "center") {
				startingPosition = Robot::StartLocation::center;
			} else if (lastPart == "right") {
				startingPosition = Robot::StartLocation::right;
			} else {
				std::cout
						<< "That's not an option for starting positions. Don't feel like doing anything now"
						<< std::endl;
				startingPosition = Robot::StartLocation::unknown;
			}
		} else if (firstPart == "doswitch") {
			if (lastPart == "true") {
				std::cout << "Doing the switch" << std::endl;
				doSwitch = true;
			} else if (lastPart == "false") {
				std::cout << "No switch for us" << std::endl;
				doSwitch = false;
			} else {
				std::cout
						<< "That's not an option for doing the switch. Need more zip-ties to accomplish anything"
						<< std::endl;
				doSwitch = false;
			}
		} else if (firstPart == "doscale") {
			if (lastPart == "true") {
				std::cout << "Doing the scale" << std::endl;
				doScale = true;
			} else if (lastPart == "false") {
				std::cout << "No scale for us" << std::endl;
				doScale = false;
			} else {
				std::cout
						<< "That's not an option for doing the scale. Is everything plugged in?"
						<< std::endl;
				doScale = false;
			}
		}
	}
}

FileAutonomousSource::~FileAutonomousSource(){

}

bool FileAutonomousSource::IsDoSwitch() {
	return doSwitch;
}

bool FileAutonomousSource::IsDoScale() {
	return doScale;
}

Robot::StartLocation FileAutonomousSource::GetStartLocation() {
	return startingPosition;
}
