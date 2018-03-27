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

	Frame(const std::string& path);
	virtual ~Frame();
	virtual void Broadcast();

protected:
	std::string path;


};

#endif /* SRC_COMM_FRAME_H_ */
