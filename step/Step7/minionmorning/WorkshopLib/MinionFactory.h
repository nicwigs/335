/**
 * \file MinionFactory.h
 *
 * \author Charles Owen
 *
 * Factory class that makes Minion objects
 * \cond
 */

#pragma once

#include <memory>
#include "WorkshopController.h"

class CMinion;
class CWardrobeItem;

/**
 * Factory class that makes Minion objects
 *
 * This is an unusual factory, since we are going to keep it 
 * around all of the time. We do this because it holds pointers
 * to all of the images that are used so we only have to 
 * load them one time.
 */
class CMinionFactory
{
public:
	CMinionFactory();
	~CMinionFactory();

	std::shared_ptr<CMinion> Create(int eyes);
	std::shared_ptr<CWardrobeItem> CreateWardrobe(CWorkshopController::Wardrobe item);

	bool Load();

private:
	std::shared_ptr<Gdiplus::Bitmap> mMinion1;
	std::shared_ptr<Gdiplus::Bitmap> mMinion2;
	std::shared_ptr<Gdiplus::Bitmap> mMinion1dead;
	std::shared_ptr<Gdiplus::Bitmap> mMinion2dead;
	std::shared_ptr<Gdiplus::Bitmap> mPassed;

	/// Wardrobe items
	std::shared_ptr<Gdiplus::Bitmap>  mWardrobe[CWorkshopController::NumWardrobe];
};

/// \endcond