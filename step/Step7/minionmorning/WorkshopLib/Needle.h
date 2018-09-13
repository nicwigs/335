/**
 * \file Needle.h
 *
 * \author Charles Owen
 *
 * Scary innoculation needle!
 * \cond
 */

#pragma once

#include <memory>

/**
 * Scary innoculation needle!
 */
class CNeedle
{
public:
	CNeedle();
	~CNeedle();

	bool Load(const wchar_t * image);

	void Innoculate();

	void Draw(Gdiplus::Graphics *graphics);

	void Update(double elapsed);

	/// Set the X location for the needle
	/// \param x X location in pixels
	void SetX(int x) { mX = x; }

	/// Is the innoculation process active?
	/// \return true if so.
	bool IsInnoculating() { return mT < 1; }

private:
	int mX = 0;			///< Y location
	double mT = 1;		///< Needle time in T value

	bool mLoaded = false;

	Gdiplus::Point mPosition;

	std::shared_ptr<Gdiplus::Bitmap>  mImage;

};

/// \endcond