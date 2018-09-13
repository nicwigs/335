/**
 * \file WardrobeItem.h
 *
 * \author Charles Owen
 *
 * Class that represents one item of Minion clothing.
 * \cond
 */

#pragma once

#include <memory>
#include "WorkshopController.h"

class CWardrobeItem
{
public:
	static const double FlyingTime;

	CWardrobeItem(CWorkshopController::Wardrobe item, std::shared_ptr<Gdiplus::Bitmap> image);
	~CWardrobeItem();

	void Draw(Gdiplus::Graphics * graphics, int x, int y);

	void Fly(Gdiplus::Point from, Gdiplus::Point to);

	void Update(double elapsed);

	CWardrobeItem() = delete;
	CWardrobeItem(const CWardrobeItem &) = delete;
	void operator=(const CWardrobeItem &) = delete;

	CWorkshopController::Wardrobe GetItem() const { return mItem; }
	void SetPosition(int x, int y) { mPosition.X = x; mPosition.Y = y; }
	bool IsFlying() { return mT < 1; }

private:
	CWorkshopController::Wardrobe mItem;
	std::shared_ptr<Gdiplus::Bitmap> mImage;

	/// Flying item
	double mT = 1;

	/// Where we are flying from
	Gdiplus::Point mFrom;

	/// Where we are flying to
	Gdiplus::Point mTo;

	Gdiplus::Point mPosition;
};

/// \endcond
