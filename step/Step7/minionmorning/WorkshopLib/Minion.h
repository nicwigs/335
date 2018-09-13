/**
 * \file Minion.h
 *
 * \author Charles Owen
 *
 * Class for a minion we are dressing...
 * \cond
 */

#pragma once

#include <memory>
#include <vector>
#include "WorkshopController.h"

class CWardrobeItem;

/**
 * Class for a minion we are dressing...
 */
class AFX_EXT_CLASS CMinion
{
public:
	CMinion(int eyes, std::shared_ptr<Gdiplus::Bitmap> image, 
		std::shared_ptr<Gdiplus::Bitmap> imageDead,
		std::shared_ptr<Gdiplus::Bitmap> passed);
	CMinion() = delete;
	CMinion(const CMinion &) = delete;
	~CMinion();

	void Draw(Gdiplus::Graphics * graphics, int x, int y);

	void Shower() { mClean = true; }
	bool IsClean() const { return mClean; }

	Gdiplus::Point Target(CWorkshopController::Wardrobe item);

	void Add(std::shared_ptr<CWardrobeItem> item);

	/// Kill this minion
	void Kill() { mAlive = false; }

	/// Minion has been innoculated
	void Innoculate() { mInnoculated = true; }

	bool IsInnoculated() { return mInnoculated; }

	void Passed() { mPassed = true; }
	bool HasPassed() const { return mPassed; }

	bool WardrobeMalfunction();

	bool AnyClothes() { return mPants.size() > 0 || mGoggles.size() > 0; }

	std::shared_ptr<CWardrobeItem> Strip();

private:
	bool IsPants(CWorkshopController::Wardrobe item);

	int mEyes;
	Gdiplus::Point mPosition;


	std::shared_ptr<Gdiplus::Bitmap> mBody;
	std::shared_ptr<Gdiplus::Bitmap> mDeadBody;
	std::shared_ptr<Gdiplus::Bitmap> mPassedStamp;

	bool mAlive = true;			///< Is this Minion alive?
	bool mClean = false;		///< Is this minion clean?
	bool mInnoculated = false;	///< Has the minion been innoculated?
	bool mPassed = false;		///< Passed inspection?

	std::vector<std::shared_ptr<CWardrobeItem>> mPants;
	std::vector<std::shared_ptr<CWardrobeItem>> mGoggles;
};

/// \endcond