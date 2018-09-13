/**
 * \file PolyDrawable.h
 *
 * \author Nic Wiggins
 *
 * A drawable based on polygon images.
 */

#pragma once

#include <string>
#include <vector>
#include "Drawable.h";


 /**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class CPolyDrawable : public CDrawable
{
public:
	CPolyDrawable(const std::wstring &name);

	virtual ~CPolyDrawable();

	/** \brief Default constructor disabled */
	CPolyDrawable() = delete;
	/** \brief Copy constructor disabled */
	CPolyDrawable(const CPolyDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPolyDrawable &) = delete;

	void Draw(Gdiplus::Graphics *graphics) override;
	bool HitTest(Gdiplus::Point pos) override;
	void AddPoint(Gdiplus::Point point);
	
	/** The Drawable color
	* \returns The drawable color as a color */
	Gdiplus::Color GetColor() const { return mColor; }

	/** The drawable color
	* \param color The new drawable color */
	void SetColor(Gdiplus::Color color) { mColor = color; }

private:
	/// The polygon color
	Gdiplus::Color mColor = Gdiplus::Color::Black;

	/// The array of point objects
	std::vector<Gdiplus::Point> mPoints;
};

