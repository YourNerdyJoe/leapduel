# HackPSU 2016
### [devpost](https://devpost.com/software/leapduel)

Most of us didn't sleep.

That's ok though. We built an awesome throw-back to Yugioh using the LeapMotion Controller, a modern twist on a retro piece of nostalgia we all remembered from our childhoods.

The game controls are simple:

    'Tap' as if on a keyboard to add a card from the deck to the hand.
    'Swipe up' on a card to add it to the Playing Field.
    'Jab at the screen' to change a monsters battle position, or flip a spell or trap card.
    'Tap' on cards in the field to send them to the Graveyard.

We hacked through the night, at first expecting to incorporate Oculus Rift into an Immersive 3D real-time Card Game using the Leap Motion controller and it's advanced bone tracking. After hours of playing with both Leap Motion and Oculus' Libraries, we decided against hacking together a 3D application in the time we had, and instead spent our time creating the card game using just Leap Motion's Libraries.

We hacked together the graphics using OpenGL, SDL2, and SDL2_image. We interpret Gestures captured by Leap Motion in order to direct the game according to the Players hand-motions, almost like a real card game.

In the future, we hope to add networking using SDL2_net for a true Two-Player experience, add soundtracks, notifications for other player moves. Finally, going along with the original plan, incorporate the Oculus rift with a card-table, avatars, and different environmental settings for a truly immersive out-of-the-world awesome experience.

Currently Availably Only on Linux......../#LinuxFTW

Built By: Joseph LoManto Andrew Plaza Ryan Corcoran

