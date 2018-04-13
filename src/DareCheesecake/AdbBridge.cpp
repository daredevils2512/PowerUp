/*
 * AdbBridge.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: daredevils
 *
 *  This file is based on code from Team 254, The Cheesy Poofs
 *  This is an adaption of Java code.
 */

#include <DareCheesecake/AdbBridge.h>
#include <sstream>
bool AdbBridge::runCommand(const char* command){
	std::ostringstream test;
	test << "/usr/bin/adb " << command;
	int status = system(test.str().c_str());
	if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
		return false;
	}
	return true;
}
bool AdbBridge::start(){
	return runCommand("start-server");
}
bool AdbBridge::stop(){
	return runCommand("kill-server");
}
void AdbBridge::restartAdb(){
	stop();
	start();
}
bool AdbBridge::portForward(int local_port, int remote_port){
	std::ostringstream test;
	test << "forward tcp:" << local_port << " tcp:" << remote_port;
	return runCommand(test.str().c_str());
}
bool AdbBridge::reversePortForward(int remote_port, int local_port){
	std::ostringstream test;
	test << "reverse tcp:" << remote_port << " tcp:" << local_port;
	return runCommand(test.str().c_str());
}
bool AdbBridge::restartApp(){
	return runCommand("shell am force-stop com.team.cheezdroid") && runCommand("shell am start com.team254.cheezdroid/com.team254.cheezdroid.VisionTrackerActivity");
}
