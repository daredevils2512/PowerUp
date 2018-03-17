/*
 * SocketClient.h
 *
 *  Created on: Feb 20, 2018
 *      Author: Programming
 */

#ifndef SRC_SUBSYSTEMS_DASHBOARD_SOCKET_ROBOTCLIENT_H_
#define SRC_SUBSYSTEMS_DASHBOARD_SOCKET_ROBOTCLIENT_H_

#include <thread>
#include <string>
#include <iostream>
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <queue>

class RobotClient {
public:
	static void Connect();
	static void Disconnect();
	static void Init();

	static void SendBoolData(std::string path,bool value);
	static void SendIntData(std::string path, int value);
	static void SendLongData(std::string path, long value);
	static void SendDoubleData(std::string path, double value);
	static void SendStringData(std::string path, std::string value);

	static void SendData(std::string data);

	static bool IsConnected();
	static void recv();
	static std::string DataDivider;
private:

	static int pipe;

	static bool _shouldBeConnected;
	static bool connected;

	static std::queue<std::string> pendingFrames;
};

#endif /* SRC_SUBSYSTEMS_DASHBOARD_SOCKET_ROBOTCLIENT_H_ */
