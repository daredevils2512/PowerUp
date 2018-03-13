/*
 * CubeIntakeActuateOpen.h
 *
 *  Created on: Mar 5, 2018
 *      Author: cmorton
 */

#ifndef SRC_COMMANDS_CUBEINTAKEACTUATEOPEN_H_
#define SRC_COMMANDS_CUBEINTAKEACTUATEOPEN_H_

#include <Commands/CubeIntakeActuate.h>

class CubeIntakeActuateOpen: public CubeIntakeActuate {
public:
	CubeIntakeActuateOpen();
	virtual ~CubeIntakeActuateOpen();
protected:
	virtual frc::DoubleSolenoid::Value getDirection(){return frc::DoubleSolenoid::kForward;} //reverse on atlas
};

#endif /* SRC_COMMANDS_CUBEINTAKEACTUATEOPEN_H_ */
