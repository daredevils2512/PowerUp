/*
 * RobotClient.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: Programming
 */

#include <Robot.h>
#include <WPILib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "RobotClient.h"
#include <unistd.h>
#include <sstream>
#include <cstring>



bool RobotClient::_shouldBeConnected;
bool RobotClient::connected;
int RobotClient::pipe;
std::string RobotClient::DataDivider;

std::queue<std::string> RobotClient::pendingFrames;

void RobotClient::Init() {
	RobotClient::_shouldBeConnected=false;
	RobotClient::connected = false;
	RobotClient::pipe = -1;
	RobotClient::DataDivider = ":2512:";
}

void RobotClient::Connect(){
	_shouldBeConnected = true;
	std::cout << "Connection starting..." << std::endl;
}

bool RobotClient::IsConnected(){
	return connected;
}

void RobotClient::Disconnect() {
	_shouldBeConnected = false;
	std::cout << "Connection ending..." << std::endl;
}

void RobotClient::recv(){
	while(true) {
		Robot::dashboard->Update();
		//std::cout << (frc::RobotController::GetFPGATime() / 1000000) <<((_shouldBeConnected)?"should be connected":"dont be connected.")<<std::endl;
		if(_shouldBeConnected){
			if(pipe == -1 || !connected){
				pipe = open("/home/lvuser/pipe", O_WRONLY);
				if(pipe == -1){
					std::cout << "ERR! Fail to open pipe" << std::endl;
					connected = false;
				}else{
					std::cout << "Pipe opened" << std::endl;
					connected = true;
				}
			}else{

				if(connected){

					SendData("ping"); // run ping
					std::string str = "";

					//std::cout << pendingFrames.size() << std::endl;
					while(!pendingFrames.empty() && connected){
						str = pendingFrames.front();
						//std::cout << "packet " << str << std::endl;
						if(str.length() > 0){
							if(write( pipe, str.c_str(), str.length() ) == -1){
								connected = false;
								close(pipe);
								unlink("/home/lvuser/pipe");
								pipe = -1;
								std::cout <<"ERR:" << errno << std::endl << "Disconnected." << std::endl;

							}else{
								pendingFrames.pop();
							}
							//std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
					}
				}else{
					pipe = -1;
				}


			}
		}else{
			//disconnect
			if(pipe > -1){
				close(pipe);
				unlink("/home/lvuser/pipe");
				pipe = -1;
				connected = false;
				std::cout<< "Disconnected as per request." << std::endl;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	//TODO disconnect websocket
}
void RobotClient::SendBoolData(std::string path,bool value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  ((value)?"true":"false") << "]";
	SendData(stream.str());
}
void RobotClient::SendLongData(std::string path, long value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void RobotClient::SendIntData(std::string path, int value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void RobotClient::SendDoubleData(std::string path, double value){
	std::stringstream stream;
	stream << "[\"" + path + "\"," <<  value << "]";
	SendData(stream.str());
}
void RobotClient::SendStringData(std::string path, std::string value){
	SendData("[\"" + path + "\",\"" + value + "\"]");
}

void RobotClient::SendData(std::string data){
	// MAIN DATA SEND MECHANISM FOR COMMS XD
	pendingFrames.push( data + DataDivider );
	//std::cout << "frame data pushed" << std::endl;
}
