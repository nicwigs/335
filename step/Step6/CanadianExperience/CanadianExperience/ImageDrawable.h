/**
 * \file ImageDrawable.h
 *
 * \author Nic Wiggins
 *
 * A drawable Image Class
 */

#pragma once

#include "Drawable.h"

/**
 * A drawable image
 */
class CImageDrawable : public CDrawable
{
public:
	CImageDrawable(const std::wstring &name, const std::wstring &filename);
	virtual ~CImageDrawable();

	/** \brief Default constructor disabled */
	CImageDrawable() = delete;
	/** \brief Copy constructor disabled */
	CImageDrawable(const CImageDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CImageDrawable &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics) override;
	bool HitTest(Gdiplus::Point pos) override;

	/** The Drawable center
	* \returns The drawable center as a point */
	Gdiplus::Point GetCenter() const { return mCenter; }

	/** The drawable center
	* \param pos The new drawable position */
	void SetCenter(Gdiplus::Point pos) { mCenter = pos; }

protected:
	/// The image for this drawable
	std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
	///Center of image
	Gdiplus::Point mCenter = Gdiplus::Point(0, 0);


};

