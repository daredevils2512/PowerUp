/*
 * PipeClient.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Chris Morton
 */

#ifndef SRC_SUBSYSTEMS_DASHBOARD_SOCKET_PIPECLIENT_H_
#define SRC_SUBSYSTEMS_DASHBOARD_SOCKET_PIPECLIENT_H_

#include <Subsystems/Dashboard/Socket/Connection.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

class PipeClient: public Connection {
public:
	PipeClient();
	virtual ~PipeClient();
	virtual void transmit();
private:
	int pipe;
	const std::string pipeName = "/tmp/ddboardpipe";
};

#endif /* SRC_SUBSYSTEMS_DASHBOARD_SOCKET_PIPECLIENT_H_ */
