/*
 * HighGear.h
 *
 *  Created on: Feb 3, 2018
 *      Author: noahg
 */

#ifndef SRC_COMMANDS_HIGHGEAR_H_
#define SRC_COMMANDS_HIGHGEAR_H_

#include <Commands/DrivetrainShift.h>

class HighGear: public DrivetrainShift {
public:
	HighGear();
	virtual void Execute();
};

#endif /* SRC_COMMANDS_HIGHGEAR_H_ */
