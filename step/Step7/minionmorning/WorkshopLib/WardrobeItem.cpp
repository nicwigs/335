/**
 * \file WardrobeItem.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "WardrobeItem.h"

/// Flying time in second
const double CWardrobeItem::FlyingTime = 1;


/**
 * Constructor
 * \param item The item type
 * \param image An image for the item
 */
CWardrobeItem::CWardrobeItem(CWorkshopController::Wardrobe item, 
	std::shared_ptr<Gdiplus::Bitmap> image) : mItem(item), mImage(image)
{
}


/**
 * Destructor
 */
CWardrobeItem::~CWardrobeItem()
{
}


/**
 * Draw the item
 * \param graphics Graphics context
 * \param x X location to draw (added to computed location)
 * \param y Y location to draw (added to computed location)
 */
void CWardrobeItem::Draw(Gdiplus::Graphics *graphics, int x, int y)
{
	if (mImage != nullptr)
	{
		auto bitmap = mImage;
		int wid = bitmap->GetWidth();
		int hit = bitmap->GetHeight();
		graphics->DrawImage(bitmap.get(), 
			mPosition.X + x - wid / 2, 
			mPosition.Y + y - hit / 2, wid, hit);
	}
}


/**
 * Set to fly from one point to another
 * \param from From point
 * \param to To point
 */
void CWardrobeItem::Fly(Gdiplus::Point from, Gdiplus::Point to)
{
	mT = 0;
	mFrom = from;
	mTo = to;

	mPosition = mFrom;
}


/**
 * Update the flying animation if active
 * \param elapsed Elapsed time in seconds
 */
void CWardrobeItem::Update(double elapsed)
{
	if (mT < 1)
	{
		// We are flying
		mT += elapsed / FlyingTime;
		if (mT > 1)
		{
			mT = 1;
		}

		mPosition.X = (int)(mFrom.X + mT * (mTo.X - mFrom.X));
		mPosition.Y = (int)(mFrom.Y + mT * (mTo.Y - mFrom.Y));
	}
}

/// \endcond