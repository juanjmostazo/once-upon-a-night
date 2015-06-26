# Introduction #

Below is a list of resources dealing with animation blending. Some of them cover theoretical concepts, where others are more practical, containing code samples.

# Partial blending support in Ogre3D: Blending Masks #
It allows masking bones in an animationState by defining an array of weights for bones. Setting all bones to 0 except the ones we're interested in will result on that animation not blending those bones (example of use: combine a "point flashlight towards", and "run", so we can discard the bones in the lower body for the point flashlight animation).

Note: the skeleton's blending mode must probably be changed to ANIMBLEND\_CUMULATIVE (default is AVERAGE, I think)



# Bibliography #
  * [Ogre Wiki - Pose manual loading - for pose animations](http://www.ogre3d.org/tikiwiki/Generic+Manual+Pose+Loading&highlight=pose)
  * [Ogre API - Animation State Class](http://www.ogre3d.org/docs/api/html/classOgre_1_1AnimationState.html)
  * [Partial blending example](http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54998)
  * [Tecnofreak animation system](http://www.ogre3d.org/forums/viewtopic.php?f=11&t=45260), by Pau Novau. It may be a good idea to dive into the source code (hosted at sourceforge, a link is provided)
  * [Creating a character in Drake's Fortune](http://www.naughtydog.com/docs/Naughty-Dog-GDC08-Creating-a-Character-in-Drakes-Fortune.pdf) Paper about animation states (or translating states to animation sequences/blends). Some of the images seem to have been taken/used in Jason Gregory's book as well -obvious, as the ppt was written by a colleague of him at Naughty Dog
  * [Animation Blending - Achieving inverse kinematics and more](http://www.gamasutra.com/features/20030704/edsall_01.shtml). Gamasutra's article on animation blending.
  * [Animation Blender](http://www.ogre3d.org/tikiwiki/AnimationBlender): Link to Ogre's wiki where a snippet featuring an animation blender class has been pasted.
  * [Blending and state machines](http://graphics.ucsd.edu/courses/cse169_w05/CSE169_11.ppt)

  * Jason Gregory's Game Engine Architecture. **Chapter 11: Animation Systems**
