/*
 * FileAutonomousSource.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: noahg
 */

#include <fstream>
#include <algorithm>
#include <iostream>
#include "FileAutonomousSource.h"
#include "Util.h"

FileAutonomousSource::FileAutonomousSource(std::string filename) {
	std::ifstream ifs(filename);
	startingPosition = Robot::StartLocation::unknown;

	if (ifs.good()) {
		std::string lastPart;
		std::string firstPart;
		std::string line;
		while (std::getline(ifs, line) && !ifs.eof()) {
			firstPart = line.substr(0, line.find(":"));
			lastPart = line.substr(line.find(":") + 1, line.length());
			//TODO: trim string of whitspacing
			Util::trim(firstPart);
			Util::trim(lastPart);
			//Lowering everything to lowercase to ignore case
			std::transform(firstPart.begin(), firstPart.end(), firstPart.begin(), ::tolower);
			std::transform(lastPart.begin(), lastPart.end(), lastPart.begin(), ::tolower);

			std::cout << firstPart << " - " << lastPart << std::endl;

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
	} else {
		std::cout
				<< "ERROR: NO AUTO FILE FOUND. GO HUDDLE IN THE CORNER AND RESEARCH IT"
				<< std::endl;
		std::cout
				<< "So I'm gonna drive straight and get you some points anyway"
				<< std::endl;
	}
	ifs.close();
}

FileAutonomousSource::~FileAutonomousSource(){

}
