/**
 * \file Minion.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "Minion.h"
#include "WardrobeItem.h"

/// Offset for duplicate wardrobe items 
const int WardrobeOffset = 5;

CMinion::CMinion(int eyes, std::shared_ptr<Gdiplus::Bitmap> image, 
	std::shared_ptr<Gdiplus::Bitmap> imageDead,
	std::shared_ptr<Gdiplus::Bitmap> passed) : mEyes(eyes), mBody(image), mDeadBody(imageDead), mPassedStamp(passed)
{
}


CMinion::~CMinion()
{
}


void CMinion::Draw(Gdiplus::Graphics *graphics, int x, int y)
{
	mPosition.X = x;
	mPosition.Y = y;

	if (mBody != nullptr)
	{
		auto bitmap = mAlive ? mBody : mDeadBody;
		int wid = bitmap->GetWidth();
		int hit = bitmap->GetHeight();
		graphics->DrawImage(bitmap.get(), x - wid / 2, y - hit, wid, hit);

		int d = 0;
		for (auto item : mPants)
		{
			item->Draw(graphics, x + d, y + d - hit/2);
			d += WardrobeOffset;
		}

		d = 0;
		for (auto item : mGoggles)
		{
			item->Draw(graphics, x + d, y + d - hit / 2);
			d += WardrobeOffset;
		}

		if (mPassed)
		{
			graphics->DrawImage(mPassedStamp.get(), x - wid / 2, y - hit, wid, hit);
		}
	}


}


/**
 * Get the target location for a wardrobe item.
 * \param item Item type we are getting
 * \returns point that is the target
 */
Gdiplus::Point CMinion::Target(CWorkshopController::Wardrobe item)
{
	size_t cnt = IsPants(item) ? mPants.size() : mGoggles.size();
	int cx = mPosition.X;
	int cy = mPosition.Y - mBody->GetHeight() / 2;
	return Gdiplus::Point(cx + cnt * WardrobeOffset, cy + cnt * WardrobeOffset);
}

void CMinion::Add(std::shared_ptr<CWardrobeItem> item)
{
	item->SetPosition(0, 0);
	if (IsPants(item->GetItem()))
	{
		mPants.push_back(item);
	}
	else
	{
		mGoggles.push_back(item);
	}
}


bool CMinion::IsPants(CWorkshopController::Wardrobe item)
{
	return item == CWorkshopController::BlueJeans || item == CWorkshopController::GreenJeans;
}


/**
 * Determine if the Minion has a wardrobe malfunction
 * \returns true if wardrobe malfunction!
 */
bool CMinion::WardrobeMalfunction()
{
	// Must have one pants and one goggles.
	if (mPants.size() != 1 || mGoggles.size() != 1)
	{
		return true;
	}

	// Goggles must match the eyes
	if (mGoggles[0]->GetItem() != (mEyes == 1 ? CWorkshopController::Goggles1 : CWorkshopController::Goggles2))
	{
		return true;
	}
	
	return false;
}


/**
 * Remove one item of wardrobe from our minion
 * \returns Wardrobe item
 */
std::shared_ptr<CWardrobeItem> CMinion::Strip()
{
	if (mGoggles.size() > 0)
	{
		auto ret = mGoggles.back();
		mGoggles.pop_back();
		return ret;
	}

	if (mPants.size() > 0)
	{
		auto ret = mPants.back();
		mPants.pop_back();
		return ret;
	}

	return nullptr;
}

/// \endcond