//
// Created by insi on 11/13/16.
//
#include <stdlib.h>
#include <iostream>
#include <Leap.h>
#include "SampleListener.h"

void SampleListener::onConnect(const Leap::Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void SampleListener::onFrame(const Leap::Controller& controller) {
	const Leap::Frame frame = controller.frame();
	Leap::Finger pointable = frame.fingers().frontmost();
	//Hand hand = frame.hands()[0];
	Leap::Finger index = frame.finger(4);
	//Finger pointer = frame.fingers().fingerType(Finger.Type.TYPE_INDEX).get(0);

	//Leap::Vector direction = index.direction();

	//if (index.isValid()) {
		std::cout << "Frame id: " << frame.id()
			<< ", timestamp: " << frame.timestamp()
			<< ", hands: " << frame.hands().count()
			<< ", fingers: " << frame.fingers().count() << std::endl;

		std::cout << "Finger :" << pointable.tipPosition().toString();
	//}
}
