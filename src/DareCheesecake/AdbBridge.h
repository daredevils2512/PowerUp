/*
 * RunADBCommand.h
 *
 *  Created on: Jul 16, 2017
 *      Author: daredevils
 */

#ifndef SRC_DARECHEESECAKE_ADBBRIDGE_H_
#define SRC_DARECHEESECAKE_ADBBRIDGE_H_
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
class AdbBridge {
public:
	static bool runCommand(const char* command);
	static bool start();
	static bool stop();
	static void restartAdb();
	static bool portForward(int local_post, int remote_port);
	static bool reversePortForward(int remote_port, int local_port);
	static bool restartApp();
};

#endif /* SRC_DARECHEESECAKE_ADBBRIDGE_H_ */
