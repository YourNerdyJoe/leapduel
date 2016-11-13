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
	static int ProcessGestures(Leap::Controller controller, uint32_t* id, bool* is_horizontal, int* type);
};

#endif //LEAPDUEL_LEAPMOTION_H
