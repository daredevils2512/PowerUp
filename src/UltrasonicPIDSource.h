/*
 * UltrasonicPIDSource.h
 *
 *  Created on: Jan 20, 2018
 *      Author: noahg
 */

#ifndef ULTRASONICPIDSOURCE_H_
#define ULTRASONICPIDSOURCE_H_

#include <WPILib.h>
#include "Util.h"

class UltrasonicPIDSource: public PIDSource {
public:
	UltrasonicPIDSource();
	void SetRobotSide(Util::RobotSide robotSide);
	virtual ~UltrasonicPIDSource();
	void SetPIDSourceType(PIDSourceType pidSource);
	PIDSourceType GetPIDSourceType() const;
	double PIDGet();

private:
	double frontDistance = 0.0;
	double rearDistance = 0.0;
	Util::RobotSide m_robotSide = Util::RobotSide::leftSide;
};

#endif /* ULTRASONICPIDSOURCE_H_ */
