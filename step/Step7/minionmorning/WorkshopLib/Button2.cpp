/**
 * \file Button2.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "Button2.h"
#include "ImageHelper.h"

CButton2::CButton2()
{
}


CButton2::~CButton2()
{
}


bool CButton2::ButtonDown(CPoint point)
{
	if (mLoaded)
	{
		int wid = mUp->GetWidth();
		int hit = mUp->GetHeight();
		if (mEnabled && point.x >= mPosition.X - wid / 2 && point.x < mPosition.X + wid / 2 &&
			point.y >= mPosition.Y - hit / 2 && point.y < mPosition.Y + hit / 2)
		{
			mPressed = true;
			return true;
		}
	}

	return false;
}

void CButton2::ButtonUp()
{
	mPressed = false;
}

/**
 * Draw the button
 * \param graphics Graphics context
 */
void CButton2::Draw(Gdiplus::Graphics *graphics)
{
	if (mEnabled) 
	{
		auto bitmap = mPressed ? mDown : mUp;
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
bool CButton2::Load(const wchar_t *up, const wchar_t *down)
{
	mUp = CImageHelper::LoadImage(up);
	mDown = CImageHelper::LoadImage(down);

	mLoaded = mUp != nullptr && mDown != nullptr;
	return mLoaded;
}

/// \endcond