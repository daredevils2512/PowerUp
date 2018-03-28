/*
 * Connection.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Christopher Morton
 */

#ifndef SRC_SUBSYSTEMS_DASHBOARD_SOCKET_CONNECTION_H_
#define SRC_SUBSYSTEMS_DASHBOARD_SOCKET_CONNECTION_H_

#include <queue>
#include <string>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h> //printf

static std::string DataDivider = ":2512:";
template<typename DataType>
std::string to_string(const DataType d)
{
	std::stringstream output;
	output << d;
	std::string result = output.str();
    return  result; // convert string to DataType
}




class Connection {
public:
	Connection();
	virtual ~Connection();

	void Connect();
	void Disconnect();
	bool IsConnected();

	virtual void transmit() = 0;

	static Connection* getInstance();

	static void SendData(const std::string & path, const std::string& val);
	static void SendData(const std::string& path, const bool val);

protected:
	bool _shouldBeConnected;
	bool connected;
	std::queue<std::string> pendingFrames;
private:
	 static Connection * connection;

};


#endif /* SRC_SUBSYSTEMS_DASHBOARD_SOCKET_CONNECTION_H_ */
