/**
 * \file Needle.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "Needle.h"
#include "ImageHelper.h"

/// Y value in pixels when needle is up
const int NeedleUpY = -280;

/// Y value in pixels when needle is down
const int NeedleDownY = 0;

/// Time to complete an innoculation in seconds
const double InnoculateTime = 2.0;

CNeedle::CNeedle()
{
}


CNeedle::~CNeedle()
{
}


/**
* Draw the button
* \param graphics Graphics context
*/
void CNeedle::Draw(Gdiplus::Graphics *graphics)
{
	if (mT < 1)
	{
		int y;
		if (mT < 0.33)
		{
			double t = mT / 0.33;
			y = (int)(NeedleUpY + t * (NeedleDownY - NeedleUpY));
		}
		else if(mT > 0.66)
		{
			double t = (mT - 0.66) / 0.33;
			y = (int)(NeedleDownY + t * (NeedleUpY - NeedleDownY));
		}
		else
		{
			y = NeedleDownY;
		}

		auto bitmap = mImage;
		int wid = bitmap->GetWidth();
		int hit = bitmap->GetHeight();
		graphics->DrawImage(bitmap.get(), mX, y, wid, hit);
	}
}


/**
 * Update the animation in time
 * \param elapsed Elapsed time in seconds
 */
void CNeedle::Update(double elapsed)
{
	if (mT < 1)
	{
		mT += elapsed / InnoculateTime;
		if (mT > 1)
		{
			mT = 1;
		}
	}
}

/**
* Load the images for the button
* \param up Up image
* \param down Down image
* \return true if successfully loaded
*/
bool CNeedle::Load(const wchar_t *image)
{
	mImage = CImageHelper::LoadImage(image);
	mLoaded = mImage != nullptr;
	return mLoaded;
}

/**
 * Start the needle innoculation sequence
 */
void CNeedle::Innoculate()
{
	mT = 0;
}

/// \endcond