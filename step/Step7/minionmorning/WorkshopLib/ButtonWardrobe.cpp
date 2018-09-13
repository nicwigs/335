/**
 * \file ButtonWardrobe.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "ButtonWardrobe.h"
#include "ImageHelper.h"


CButtonWardrobe::CButtonWardrobe()
{
}


CButtonWardrobe::~CButtonWardrobe()
{
}


CWorkshopController::Wardrobe CButtonWardrobe::ButtonDown(CPoint point)
{
	if (mLoaded)
	{
		int wid = mImage->GetWidth();
		int hit = mImage->GetHeight();
		if (mEnabled && point.x >= mPosition.X - wid / 2 && point.x < mPosition.X + wid / 2 &&
			point.y >= mPosition.Y - hit / 2 && point.y < mPosition.Y + hit / 2)
		{
			// Where on the image did we click?
			int rx = point.x - (mPosition.X - wid / 2);
			int ry = point.y - (mPosition.Y - hit / 2);
			if (rx < wid / 2) 
			{
				// Left side
				if (ry < hit / 2)
				{
					return CWorkshopController::Goggles1;
				}
				else 
				{
					return CWorkshopController::GreenJeans;
				}
			}
			else
			{
				// Right side
				if (ry < hit / 2)
				{
					return CWorkshopController::Goggles2;
				}
				else
				{
					return CWorkshopController::BlueJeans;
				}
			}

			return CWorkshopController::None;
		}
	}

	return CWorkshopController::None;
}



/**
* Draw the button
* \param graphics Graphics context
*/
void CButtonWardrobe::Draw(Gdiplus::Graphics *graphics)
{
	if (mEnabled)
	{
		auto bitmap = mImage;
		int wid = bitmap->GetWidth();
		int hit = bitmap->GetHeight();
		graphics->DrawImage(bitmap.get(), mPosition.X - wid / 2, mPosition.Y - hit / 2, wid, hit);
	}
}


/**
* Load the images for the button
* \param up Up image
* \param down Down image
* \return true if successfully loaded
*/
bool CButtonWardrobe::Load(const wchar_t *image)
{
	mImage = CImageHelper::LoadImage(image);
	mLoaded = mImage != nullptr;
	return mLoaded;
}

/// \endcond