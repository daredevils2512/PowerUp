/*
 * CubeIntakeActuateClose.h
 *
 *  Created on: Mar 5, 2018
 *      Author: cmorton
 */

#ifndef SRC_COMMANDS_CUBEINTAKEACTUATECLOSE_H_
#define SRC_COMMANDS_CUBEINTAKEACTUATECLOSE_H_

#include <Commands/CubeIntakeActuate.h>

class CubeIntakeActuateClose: public CubeIntakeActuate {
public:
	CubeIntakeActuateClose();
	virtual ~CubeIntakeActuateClose();

protected:
	virtual frc::DoubleSolenoid::Value getDirection(){return frc::DoubleSolenoid::kReverse;}
};

#endif /* SRC_COMMANDS_CUBEINTAKEACTUATECLOSE_H_ */
