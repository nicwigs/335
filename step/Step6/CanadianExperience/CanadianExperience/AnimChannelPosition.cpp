/**
 * \file AnimChannelPosition.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "AnimChannelPosition.h"
#include <memory>
using namespace std;

/**
 * Constructor. 
 */
CAnimChannelPosition::CAnimChannelPosition()
{
}


/**
 * Destructor. 
 */
CAnimChannelPosition::~CAnimChannelPosition()
{
}


/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param pos Position for the keyframe.
*/
void CAnimChannelPosition::SetKeyframe(Gdiplus::Point pos)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the angle
	shared_ptr<KeyframePosition> keyframe =
		make_shared<KeyframePosition>(this, pos);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/**
* Compute a position that is an interpolation between two keyframes
*
* This function is called after Use1 and Use2, so we have pointers to
* to valid keyframes of the type KeyframePosition. This function does the
* tweening.
* \param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
* interpolate between.
*/
void CAnimChannelPosition::Tween(double t)
{
	Gdiplus::Point a = mKeyframe1->GetPosition();
	Gdiplus::Point b = mKeyframe2->GetPosition();

	Gdiplus::Point c(int(a.X + t * (b.X - a.X)), int(a.Y + t * (b.Y - a.Y)));

	mPosition = c;
}
