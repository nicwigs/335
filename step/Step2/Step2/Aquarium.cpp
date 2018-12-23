/**
 * \file Aquarium.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Aquarium.h"
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;

/**
 * Constructor. 
 */
CAquarium::CAquarium()
{
	mBackground = unique_ptr<Gdiplus::Bitmap>(
		Bitmap::FromFile(L"images/background1.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/background1.png");
	}	
}


/**
 * Destructor
 */
CAquarium::~CAquarium()
{
}

/** Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics *graphics)
{
	graphics->DrawImage(mBackground.get(), 0, 0,
		mBackground->GetWidth(), mBackground->GetHeight());

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));
	graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
}

/**
* Add an item to the aquarium
* \param item New item to add
*/
void CAquarium::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}
	return  nullptr;
}


/**
 * Puts item just moved at end of mItems to ensure proper draw order
 *
 * \param item is the chosen item via user
 */
void CAquarium::BringToFront(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		auto movedItem = *loc;
		mItems.erase(loc);
		mItems.push_back(movedItem);		
	}
}


/**
 *  Finds fish(s) to kill and removes it from aquarium 
 *
 * \param predator the fish that is doing the killing
 */
void CAquarium::PredatorEat(CItem * predator)
{
	
	int numItems = mItems.size();

	for (int j = 0; j < numItems; j++)
	{
		for (auto i = mItems.begin(); i != mItems.end(); i++)
		{
			if ((*i)->HitTest(predator->GetX(), predator->GetY()) && 
				i->get() != predator)
			{
				mItems.erase(i);
				break;
			}
		}
	}	
}