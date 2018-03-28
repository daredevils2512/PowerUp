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
	EncoderFrame(const std::string& path, frc::Encoder* encoder, int aChannel, int bChannel);
	virtual ~EncoderFrame();
	void Broadcast();

private:
	frc::Encoder* encoder;

	int aChannel;
	int bChannel;

};

#endif /* SRC_COMM_FRAMES_EncoderFrame_H_ */
