/**
* \file FishNemo.h
*
* \author Nic Wiggins
*
* Class than describes a Nemo fish
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* Implements a Nemo fish
*/
class CFishNemo : public CItem
{
public:

	CFishNemo(CAquarium * aquarium);
	virtual ~CFishNemo();

	/// Default constructor (disabled)
	CFishNemo() = delete;

	/// Copy constructor (disabled)
	CFishNemo(const CFishNemo &) = delete;

	void Draw(Gdiplus::Graphics * graphics);

	bool HitTest(int x, int y);

private:
	/// Pointer to image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
