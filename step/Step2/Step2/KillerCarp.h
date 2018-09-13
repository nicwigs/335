/**
* \file KillerCarp.h
*
* \author Nic Wiggins
*
* Class than describes a Killer Carp
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* Implements a Killer Carp
*/
class CKillerCarp : public CItem
{
public:

	CKillerCarp(CAquarium * aquarium);
	virtual ~CKillerCarp();

	/// Default constructor (disabled)
	CKillerCarp() = delete;

	/// Copy constructor (disabled)
	CKillerCarp(const CKillerCarp &) = delete;

	void Draw(Gdiplus::Graphics * graphics);

	bool HitTest(int x, int y);

	void SetLocation(double x, double y);

private:
	/// Pointer to image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mFishImage; 
};
