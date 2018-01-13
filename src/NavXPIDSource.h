/*
 * NaxXPIDSource.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Daredevils-Prog-1
 */

#ifndef SRC_NAVXPIDSOURCE_H_
#define SRC_NAVXPIDSOURCE_H_
#include <WPILib.h>

class NavXPIDSource: public PIDSource {
public:
	virtual ~NavXPIDSource();
	void SetPIDSourceType(PIDSourceType pidSource);
	PIDSourceType GetPIDSourceType() const;
	double PIDGet();
};

#endif /* SRC_NAVXPIDSOURCE_H_ */
