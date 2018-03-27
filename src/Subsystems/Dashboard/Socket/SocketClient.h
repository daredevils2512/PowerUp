/*
 * SocketClient.h
 *
 *  Created on: Feb 20, 2018
 *      Author: Programming
 */

#ifndef SRC_SUBSYSTEMS_DASHBOARD_SOCKET_SOCKETCLIENT_H_
#define SRC_SUBSYSTEMS_DASHBOARD_SOCKET_SOCKETCLIENT_H_

#include "Connection.h"
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent

class SocketClient : public Connection {
public:
	void SetConnection(const std::string& host, int port);

	SocketClient(const std::string& host, const int port);

	void recv();

private:
	static std::string host;
	static int port;
	static int sock;
	static struct sockaddr_in server;

};

#endif /* SRC_SUBSYSTEMS_DASHBOARD_SOCKET_SOCKETCLIENT_H_ */
