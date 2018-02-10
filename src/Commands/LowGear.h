/*
 * LowGear.h
 *
 *  Created on: Feb 3, 2018
 *      Author: noahg
 */

#ifndef SRC_COMMANDS_LOWGEAR_H_
#define SRC_COMMANDS_LOWGEAR_H_

#include <Commands/DrivetrainShift.h>

class LowGear: public DrivetrainShift {
public:
	LowGear();
	virtual void Execute();
};

#endif /* SRC_COMMANDS_LOWGEAR_H_ */
