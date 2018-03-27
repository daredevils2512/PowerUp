/*
 * MatchFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_MatchFrame_H_
#define SRC_DASHBOARD_FRAMES_MatchFrame_H_

#include "Frame.h"


class MatchFrame: public Frame {
public:
	MatchFrame(const std::string& path);
	virtual ~MatchFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:

	std::string GetMatchType();
	std::string GetAlliance();
	long GetMatchStartTime();
	frc::DriverStation& ds;

	std::string eventName;

	std::string gameMessage;

	std::string type; //match type

	int number; //match number

	int replay;

	std::string alliance;

	int dslocation;

	long startTime;

	/*
		"eventName":"Daredevils",
		"gameMessage":"RRR",
		"type":"none",
		"number":1,
		"replay":0,
		"alliance":"red",
		"dslocation":1,
		"startTime":-1, // in millis
	 */
};

#endif /* SRC_COMM_FRAMES_MatchFrame_H_ */
