/**
* \file FishDory.h
*
* \author Nic Wiggins
*
* Class than describes a Dory fish
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* Implements a Dory fish
*/
class CFishDory : public CItem
{
public:

	CFishDory(CAquarium * aquarium);
	virtual ~CFishDory();

	/// Default constructor (disabled)
	CFishDory() = delete;

	/// Copy constructor (disabled)
	CFishDory(const CFishDory &) = delete;

	void Draw(Gdiplus::Graphics * graphics);

	bool HitTest(int x, int y);

private:
	/// Pointer to image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};
