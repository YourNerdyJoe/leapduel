#include <Windows.h>
#include <iostream>
#include <string.h>
#include "Leap.h"

using namespace Leap;

class SampleListener : public Listener {
public:
	virtual void onConnect(const Controller&);
	virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();
	Leap::Finger pointable = frame.fingers().frontmost();
	//Hand hand = frame.hands()[0];
	Finger index = frame.finger(4);
	//Finger pointer = frame.fingers().fingerType(Finger.Type.TYPE_INDEX).get(0);
	
	Leap::Vector direction = index.direction();

	//if (index.isValid()) {
		std::cout << "Frame id: " << frame.id()
			<< ", timestamp: " << frame.timestamp()
			<< ", hands: " << frame.hands().count()
			<< ", fingers: " << frame.fingers().count() << std::endl;

		Sleep(50);
		std::cout << "Finger :" << pointable.tipPosition().toString();
	//}
}

int main(int argc, char** argv) {
	SampleListener listener;
	Controller controller;

	controller.addListener(listener);
	controller.setPolicy(Leap::Controller::POLICY_IMAGES);
	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}