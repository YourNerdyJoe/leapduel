//
// Created by insi on 11/13/16.
//

#include <Leap.h>
//#include <GL/gl.h>
//#include <GLES/gl.h>
//#include <GLES2/gl2.h>
#include "LeapMotion.h"
#include "LeapMotion.h"
#include "LeapListener.h"


int LeapMotion::ProcessGestures(Leap::Controller controller, uint32_t* id, bool* is_horizontal, int* type)
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
        *is_horizontal = false;

        switch (gesture.type())
        {
            case Leap::Gesture::TYPE_SWIPE:
            {
                Leap::Vector handDir = gesture.hands()[0].direction();

                if(id) *id = gesture.id();
                // naive left/right swipe detection
                
                if (handDir.y < -0.7f)
                {
                    return -1;
                }
                else if (handDir.y > 0.7f)
                {
                    return 1;
                }
                if (handDir.x < -0.7f)
                {
                    *is_horizontal = true;
                    std::cout << "-1 yo" << std::endl;
                    return -1;
                }
                else if (handDir.x > 0.7f)
                {
                    *is_horizontal = true;
                    std::cout << "1 yo" << std::endl;
                    return 1;
                }
            }
            case Leap::Gesture::TYPE_KEY_TAP:
            {
                Leap::Vector handDir = gesture.hands()[0].direction();


            }
            default:
                break;
        }
    }
    return 0;
}

