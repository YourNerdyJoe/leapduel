//
// Created by insi on 11/13/16.
//

#include <Leap.h>
#include <GL/gl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include "LeapMotion.h"
#include "LeapMotion.h"
#include "LeapListener.h"


int LeapMotion::ProcessGestures(Leap::Controller controller)
{
    const Leap::GestureList gestures = controller.frame().gestures();

    static bool swipeTracked = false;

    // on left/right swipe gesture switch between camera view and "ingame" hand rendering
    if (gestures.isEmpty() && swipeTracked)
    {
        swipeTracked = false;
    }

    for (auto it = gestures.begin(); gestures.end() != it; ++it)
    {
        Leap::Gesture gesture = *it;

        switch (gesture.type())
        {
            case Leap::Gesture::TYPE_SWIPE:
            {
                Leap::Vector handDir = gesture.hands()[0].direction();

                // naive left/right swipe detection
                if (handDir.y < -0.5f)
                    return -1;
                else if (handDir.y > 0.5f)
                    return 1;
            }
            default:
                break;
        }
    }
    return 0;
}

