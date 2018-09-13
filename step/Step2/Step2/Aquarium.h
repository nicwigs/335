/**
 * \file Aquarium.h
 *
 * \author Nic Wiggins
 *
 * Class that represents the aquarium. 
 */

#pragma once

#include<memory>
#include<vector>

class CItem;

/**
 * Class that describes an aquarium. 
 */
class CAquarium
{
public:
	CAquarium();
	virtual ~CAquarium();

	void OnDraw(Gdiplus::Graphics * graphics);

	void Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(int x, int y);

	void BringToFront(std::shared_ptr<CItem> item);

	void PredatorEat(CItem * predator);

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
};

