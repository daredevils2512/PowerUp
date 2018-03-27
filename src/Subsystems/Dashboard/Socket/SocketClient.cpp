/*
 * SocketClient.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: Programming
 */

#include "SocketClient.h"
#include <Robot.h>
#include <WPILib.h>
#include <unistd.h>
#include <sstream>
#include <cstring>



bool SocketClient::_shouldBeConnected;
bool SocketClient::connected;
std::string SocketClient::host;
int SocketClient::port;
int SocketClient::sock;
sockaddr_in SocketClient::server;
std::string SocketClient::DataDivider;

std::queue<std::string> SocketClient::pendingFrames;

void SocketClient::SetConnection(std::string host, int port) {
	SocketClient::_shouldBeConnected=false;
	SocketClient::connected = false;
	SocketClient::host = host;
	SocketClient::port = port;
	SocketClient::sock = -1;
	SocketClient::DataDivider = ":2512:";
}

void SocketClient::Connect(){
	_shouldBeConnected = true;
	std::cout << "Connection started" << std::endl;
}

bool SocketClient::IsConnected(){
	return connected;
}

void SocketClient::Disconnect() {
	_shouldBeConnected = false;
}

void SocketClient::recv(){
	while(true) {
		Robot::dashboard->Update();
		//std::cout << (frc::RobotController::GetFPGATime() / 1000000) <<((_shouldBeConnected)?"should be connected":"dont be connected.")<<std::endl;
		if(_shouldBeConnected){
			if(sock == -1){
				sock = socket( AF_INET, SOCK_STREAM, 0);
				if(sock == -1){
					std::cout << "ERR! Fail to create socket" << std::endl;
					connected = false;
				}else{
					std::cout << "Socket created; Waiting for connection success..." << std::endl;
				}
			}else{

				if(!connected){

					server.sin_addr.s_addr = inet_addr ( host.c_str() );
					server.sin_family = AF_INET;
					server.sin_port = htons( port );

					int connResult = connect(sock, (struct sockaddr *)&server, sizeof(server));
					if(connResult < 0){
						if(errno != 111){
							std::cout << "ERR! Failed to connect: " << errno << std::endl;
						}
					}else{
						connected = true;
						std::cout << "Connection established." << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(30)); // wait 100 ms for connection to complete before finishing
					}
				}else{ // CONNECTED //
					SendData("ping"); // run ping
					std::string str = "";

					//std::cout << pendingFrames.size() << std::endl;
					while(!pendingFrames.empty() && connected){
						str = pendingFrames.front();
						//std::cout << "packet " << str << std::endl;
						if(str.length() > 0){
							if(send( sock, str.c_str(), str.length(), 0 ) == -1){
								if(errno == 32 || errno == 104){
									connected = false;
									sock = -1;
									std::cout << "Connection Lost: ";
									if(errno == 104){
										std::cout << "Dropped by server" << std::endl;
									}else{
										std::cout << "Broken Pipe" << std::endl;
									}

								}else{
									connected = false;
									close(sock);
									sock = -1;
									std::cout <<"ERR:" << errno << std::endl << "Disconnected." << std::endl;
								}
							}else{
								pendingFrames.pop();
							}
							//std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
					}
				}


			}
		}else{
			//disconnect
			if(sock > -1){
				close(sock);
				sock = -1;
				connected = false;
				std::cout<< "Disconnected" << std::endl;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	//TODO disconnect websocket
}
void SocketClient::SendBoolData(std::string path,bool value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  ((value)?"true":"false") << "]";
	SendData(stream.str());
}
void SocketClient::SendLongData(std::string path, long value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void SocketClient::SendIntData(std::string path, int value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void SocketClient::SendDoubleData(std::string path, double value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void SocketClient::SendStringData(std::string path, std::string value){
	SendData("[\"" + path + "\",\"" + value + "\"]");
}

void SocketClient::SendData(std::string data){
	// MAIN DATA SEND MECHANISM FOR COMMS XD
	pendingFrames.push( data + DataDivider );
	//std::cout << "frame data pushed" << std::endl;
}
