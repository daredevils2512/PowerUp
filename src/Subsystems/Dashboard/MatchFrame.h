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
	MatchFrame(std::string path);
	virtual ~MatchFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:

	std::string GetMatchType();
	std::string GetAlliance();
	long GetMatchStartTime();

	std::string path;

	std::string eventName;
	bool eventName_dirty;

	std::string gameMessage;
	bool gameMessage_dirty;

	std::string type; //match type
	bool type_dirty;

	int number; //match number
	bool number_dirty;

	int replay;
	bool replay_dirty;

	std::string alliance;
	bool alliance_dirty;

	int dslocation;
	bool dslocation_dirty;

	long startTime;
	bool startTime_dirty;

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
