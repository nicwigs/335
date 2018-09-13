/**
* \file KillerCarp.cpp
*
* \author Nic Wiggins
*/

#include "stdafx.h"
#include <string>
#include "KillerCarp.h"
#include "Aquarium.h"


using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring KillerCarpImageName = L"images/carp.png";

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CKillerCarp::CKillerCarp(CAquarium *aquarium) :
	CItem(aquarium, KillerCarpImageName)
{
}

/**
* Destructor.
*/
CKillerCarp::~CKillerCarp()
{
}

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CKillerCarp::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mFishImage->GetWidth();
	double hit = mFishImage->GetHeight();
	graphics->DrawImage(mFishImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)mFishImage->GetWidth(), (float)mFishImage->GetHeight());
}


/**
 * Set the item location. checks to see if item can
 * eat another item
 * 
 * \param x X Location
 * \param y Y Location 
 */
void CKillerCarp::SetLocation(double x, double y)
{
	CItem::SetLocation(x,y); //upcall

	auto aquarium = GetAquarium();

	CItem * predator = this;

	aquarium->PredatorEat(predator);
}

