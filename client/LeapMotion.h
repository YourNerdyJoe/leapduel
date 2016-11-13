//
// Created by insi on 11/13/16.
//
//eventually, rendering something on screen with OpenGL. Maybe like a hand, or, something like that
#ifndef LEAPDUEL_LEAPMOTION_H
#define LEAPDUEL_LEAPMOTION_H
struct LData;

class LeapMotion {
public:
	virtual void onConnCurserMove(const Leap::Controller&);
	static int ProcessGestures(Leap::Controller controller);
};

#endif //LEAPDUEL_LEAPMOTION_H
