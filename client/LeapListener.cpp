//
// Created by insi on 11/13/16.
//
#include <stdlib.h>
#include <iostream>
#include <Leap.h>
#include <zconf.h>
#include "LeapListener.h"

#ifdef _DEBUG
#define LEAP_DEBUG_ENABLED
#endif


void LeapListener::onConnect(const Leap::Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void LeapListener::onFrame(const Leap::Controller& controller) {
	unsigned microseconds = 50;
	const Leap::Frame frame = controller.frame();
	Leap::Finger pointable = frame.fingers().frontmost();
	float scale_factor = 2;
	//Hand hand = frame.hands()[0];
	//Finger pointer = frame.fingers().fingerType(Finger.Type.TYPE_INDEX).get(0);
	//Leap::Vector direction = index.direction();


		std::cout << "Frame id: " << frame.id()
			<< ", timestamp: " << frame.timestamp()
			<< ", hands: " << frame.hands().count()
			<< ", fingers: " << frame.fingers().count() << std::endl;

		std::cout << "Finger :" << pointable.stabilizedTipPosition().toString();
		usleep(microseconds);

}


