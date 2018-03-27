/*
 * Connection.cpp
 *
 *  Created on: Mar 26, 2018
 *      Author: Christopher Morton
 */

#include <Subsystems/Dashboard/Socket/Connection.h>

#include <Subsystems/Dashboard/Socket/SocketClient.h>

Connection* Connection::connection  = nullptr;

Connection::Connection() {
	_shouldBeConnected=false;
	connected = false;
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

Connection* Connection::getInstance(){
	if (connection == nullptr){
		connection = new SocketClient("127.0.0.1", 5335);
	}
	return connection;
}
void Connection::Connect(){
	_shouldBeConnected = true;
	std::cout << "Connection started" << std::endl;
}

bool Connection::IsConnected(){
	return connected;
}


void Connection::Disconnect() {
	_shouldBeConnected = false;
}

void Connection::SendData(const std::string& path, const bool val){
	Connection::SendData(path, (val ? "enabled":"disabled"));
}


void Connection::SendData(const std::string& path, const std::string& val){
	// MAIN DATA SEND MECHANISM FOR COMMS XD
	std::string output("[\"" + path + "\",\"" + val + "\"]");

	Connection::connection->pendingFrames.push( output + DataDivider );
	//std::cout << "frame data pushed" << std::endl;
}
