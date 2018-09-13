/**
 * \file Timeline.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
 * Constructor. 
 */
CTimeline::CTimeline()
{
}


/**
 * Destructor. 
 */
CTimeline::~CTimeline()
{
}


/**
 * Adds channel to timeline
 * \param channel Channel we are adding. 
 */
void CTimeline::AddChannel(CAnimChannel * channel)
{
	mChannels.push_back(channel);
	channel->SetTimeline(this);
}

/** Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
* \param t new time. 
*/
void CTimeline::SetCurrentTime(double t)
{
	// Set the time
	mCurrentTime = t;

	for (auto channel : mChannels)
	{
		channel->SetFrame(GetCurrentFrame());
	}
}