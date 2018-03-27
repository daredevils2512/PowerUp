/*
 * Frame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_COMM_FRAME_H_
#define SRC_COMM_FRAME_H_


#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "Socket/Connection.h"
class Frame {
public:
	virtual ~Frame();

	virtual void Update();
	virtual void Broadcast();
	virtual void MarkAllDirty();
};

#endif /* SRC_COMM_FRAME_H_ */
