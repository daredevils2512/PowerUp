/*
 * PipeClient.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Chris Morton
 */

#include <Subsystems/Dashboard/Socket/PipeClient.h>

PipeClient::PipeClient() {
	pipe = -1;
	mkfifo(pipeName.c_str(), 0666);
}

PipeClient::~PipeClient() {
	unlink(pipeName.c_str());
}

void PipeClient::transmit(){
	pipe = open(pipeName.c_str(), O_WRONLY);
	std::string frame;
	while(!pendingFrames.empty()){
		frame = pendingFrames.front();
		write(pipe, frame.c_str(), sizeof(frame.c_str()));
	}
	close(pipe);
}
