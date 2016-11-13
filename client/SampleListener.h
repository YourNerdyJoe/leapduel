//
// Created by insi on 11/13/16.
//

#ifndef LEAPDUEL_SAMPLELISTENER_H
#define LEAPDUEL_SAMPLELISTENER_H


class SampleListener : public Leap::Listener {
public:
	virtual void onConnect(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
};


#endif //LEAPDUEL_SAMPLELISTENER_H
