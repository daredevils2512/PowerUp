/*
 * EncoderFrame.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Programming
 */

#ifndef SRC_DASHBOARD_FRAMES_EncoderFrame_H_
#define SRC_DASHBOARD_FRAMES_EncoderFrame_H_

#include "Frame.h"


class EncoderFrame: public Frame {
public:
	EncoderFrame(std::string path, frc::Encoder* encoder, int aChannel, int bChannel);
	virtual ~EncoderFrame();
	void Update();
	void Broadcast();
	void MarkAllDirty();
private:
	frc::Encoder* encoder;

	int aChannel;
	int bChannel;

	int count;
	int rawValue;
	double period;

	int encodingScale;
	double distancePerPulse;

	bool direction;
	double distance;
	double rate;

	int samplesToAverage;




	/*

	 */
};

#endif /* SRC_COMM_FRAMES_EncoderFrame_H_ */
