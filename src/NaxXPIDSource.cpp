/*
 * NaxXPIDSource.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Daredevils-Prog-1
 */

#include <NavXPIDSource.h>
#include "RobotMap.h"
NavXPIDSource::~NavXPIDSource() {
	// TODO Auto-generated deconstructor stub
}
PIDSourceType NavXPIDSource::GetPIDSourceType() const {
	return this->m_pidSource;
}
double NavXPIDSource::PIDGet() {
	return RobotMap::navX->GetYaw();//->GetAngle();
}
void NavXPIDSource::SetPIDSourceType(PIDSourceType pidSource) {
	m_pidSource = pidSource;
}

