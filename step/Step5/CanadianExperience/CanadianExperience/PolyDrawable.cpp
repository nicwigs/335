/**
 * \file PolyDrawable.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "PolyDrawable.h"
#include <vector>


using namespace Gdiplus;
using namespace std;


/**
 * Constructor.
 * \param name The drawable name
 */
CPolyDrawable::CPolyDrawable(const std::wstring &name) : CDrawable(name)
{
}


/**
 * Destructor.
 */
CPolyDrawable::~CPolyDrawable()
{
}


/**
 * Draws the polydrawable
 * \param graphics Graphics we are drawing
 */
void CPolyDrawable::Draw(Gdiplus::Graphics *graphics)
{
	SolidBrush brush(mColor);

	// Transform the points
	vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	graphics->FillPolygon(&brush, &points[0], (int)points.size());
}


/**
 * Sees if click on polydrawable
 * \param pos of mouse click
 * \returns ture if click on this object
 */
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
	// Transform the points
	vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	GraphicsPath path;
	path.AddPolygon(&points[0], (int)points.size());
	return path.IsVisible(pos) ? true : false;
}


/**
 * Add point to array of point objects
 * \param point Point to be added to array
 */
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}
