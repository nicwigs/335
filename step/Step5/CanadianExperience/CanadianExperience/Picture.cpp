/**
 * \file Picture.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Picture.h"
#include "Actor.h"

#include "PictureObserver.h"

using namespace Gdiplus;

/**
 * Constructor. 
 */
CPicture::CPicture()
{
}


/**
 * Destructor. 
 */
CPicture::~CPicture()
{
}

/** Add an observer to this picture.
* \param observer The observer to add
*/
void CPicture::AddObserver(CPictureObserver *observer)
{
	mObservers.push_back(observer);
}

/** Remove an observer from this picture
* \param observer The observer to remove
*/
void CPicture::RemoveObserver(CPictureObserver *observer)
{
	auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
	if (loc != std::end(mObservers))
	{
		mObservers.erase(loc);
	}
}

/** Update all observers to indicate the picture has changed.
*/
void CPicture::UpdateObservers()
{
	for (auto observer : mObservers)
	{
		observer->UpdateObserver();
	}
}
/** Draw this picture on a device context
* \param graphics The graphic to draw on
*/
void CPicture::Draw(Gdiplus::Graphics *graphics)
{
	for (auto actor : mActors)
	{
		actor->Draw(graphics);
	}
}

/**
* Add a actor to this picture
* \param actor The actor to add
*/
void CPicture::AddActor(std::shared_ptr<CActor> actor)
{
	mActors.push_back(actor);
	actor->SetPicture(this);
}