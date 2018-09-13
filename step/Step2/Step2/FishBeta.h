/**
 * \file FishBeta.h
 *
 * \author Nic Wiggins
 *
 * Class than describes a beta fish
 */

#pragma once

#include <memory>

#include "Item.h"


/**
 * Implements a beta fish
 */
class CFishBeta : public CItem
{
public:	 
	
	CFishBeta(CAquarium * aquarium);
	virtual ~CFishBeta();

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	void Draw(Gdiplus::Graphics * graphics);

	bool HitTest(int x, int y);

private:
	/// Pointer to image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage;
};

