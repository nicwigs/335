/**
 * \file HeadTop.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "HeadTop.h"

using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/**
 * Constructor. 
 * \param name Name of head top
 * \param filename File to image
 */
CHeadTop::CHeadTop(const std::wstring &name, const std::wstring &filename) :
	CImageDrawable(name,filename)
{
}


/**
 * Destructor. 
 */
CHeadTop::~CHeadTop()
{
}

/**
* Draw the image drawable
* \param graphics Graphics context to draw on
*/
void CHeadTop::Draw(Gdiplus::Graphics *graphics)
{
	CImageDrawable::Draw(graphics);
	
	DrawEyeBrow(graphics, mInRightEyeBrow, mOutRightEyeBrow);
	DrawEyeBrow(graphics, mInLeftEyeBrow, mOutLeftEyeBrow);
	
	DrawEye(graphics, mRightEye);
	DrawEye(graphics, mLeftEye);

}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
	// Make p relative to the image center
	p = p - GetCenter();

	// Rotate as needed and offset
	return RotatePoint(p, mPlacedR) + mPlacedPosition;
}


/**
 * Draw an eyebrow
 * \param graphics Graphics we are drawing
 * \param in In point of eyebrow
 * \param out Out point of eyebrow
 */
void CHeadTop::DrawEyeBrow(Gdiplus::Graphics *graphics, Gdiplus::Point in, Gdiplus::Point out)
{
	Pen pen(Color::Brown, 3);
	
	Point inPoint = TransformPoint(in);	
	Point outPoint = TransformPoint(out);

	graphics->DrawLine(&pen, inPoint, outPoint);
}


/**
 * Draw an eye
 * \param graphics Graphics we are drawing
 * \param center Center of the Eye
 */
void CHeadTop::DrawEye(Gdiplus::Graphics *graphics, Gdiplus::Point center)
{
	SolidBrush brush(Color(0, 0, 0));

	center = TransformPoint(center);

	float wid = 15.0f;
	float hit = 20.0f;

	auto state = graphics->Save();
	graphics->TranslateTransform(center.X, center.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(state);
}