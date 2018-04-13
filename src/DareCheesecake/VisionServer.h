/*
 * VisionServer.h
 *
 *  Created on: Jul 16, 2017
 *      Author: daredevils
 */

#ifndef SRC_DARECHEESECAKE_VISIONSERVER_H_
#define SRC_DARECHEESECAKE_VISIONSERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "AdbBridge.h"
#include <WPILib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

class VisionServer {

public:
	static const bool DEBUG_MODE=false;
	struct TargetInfo {
		double x;
		double y;
	};
	static void resetVars();
	static void setupServer();
	static void setupCamera();
	static bool isConnected();
	static void reqAppRestart();
	static void findCamera();
	static void runServerRoutine();

	static void visionLoop();
	static void visionUpdater();


	static std::vector<TargetInfo> targets;
	static bool hasSetup;
	static bool isActive;
	static const int port = 8254; // Port. Defined by Team254. Not changing it rn.
private:
	static int socketfd; // Socket instance ID, used in socket methods.
	static int clientfd;
	static bool pendingRestart;
	static bool mIsConnected;
	static double lastMessageReceivedTime;
	static long lastReceived;
	static int failConnectCount;
	template<typename Out>
	static void splitr(const std::string &s, char delim, Out result);
	static std::vector<std::string> split(const std::string &s, char delim);


};

#endif /* SRC_DARECHEESECAKE_VISIONSERVER_H_ */
