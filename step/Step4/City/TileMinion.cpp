/**
 * \file TileMinion.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include <string>
#include <memory>

#include "TileMinion.h"

using namespace std;
using namespace Gdiplus;

/// Image for background
const wstring TileBackground = L"grass.png";
/// Image for normal minion
const wstring MinionImage = L"minion.png";
/// Image for bananna minion
const wstring BananaImage = L"banana.png";
/// Image for mutant minion
const wstring MutantImage = L"mutant.png";

/// How much we offset drawing the tile to the left of the center
const int OffsetLeft = 64;
/// How much we offset drawing the tile above the center
const int OffsetDown = 32;

/// Number of bananas until mutant
const int MutantBananaThreshold = 3;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;
/// Minimum speed in the X direction in
/// in pixels per second
const double MinSpeedX = -50;

/**
 * Constructor.
 * \param city The city this is a member of
 */
CTileMinion::CTileMinion(CCity *city) : CTile(city)
{
	SetImage(TileBackground);

	LoadImage(mMinionImage, MinionImage);
	LoadImage(mBananaImage, BananaImage);
	LoadImage(mMutantImage, MutantImage);

	while (mSpeedX == 0) //incase it randomly generates 0 as speed
	{
		mSpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
	}

}


/**
 * Destructor
 */
CTileMinion::~CTileMinion()
{
}

/**
* Load an image into a bitmap
* \param image Image pointer to load
* \param name Filename to load from
*/
void CTileMinion::LoadImage(std::unique_ptr<Gdiplus::Bitmap> &image, std::wstring name)
{
	wstring filename = ImagesDirectory + name;
	image = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (image->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}

/**  Draw this item
* \param graphics The graphics context to draw on */
void CTileMinion::Draw(Gdiplus::Graphics *graphics)
{
	CTile::Draw(graphics);
	
	
	if (mState == Normal)
	{
		int wid = mMinionImage->GetWidth();
		int hit = mMinionImage->GetHeight();

		graphics->DrawImage(mMinionImage.get(),
			(int)(GetX() + mRunX - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	else if (mState == Banana)
	{
		int wid = mBananaImage->GetWidth();
		int hit = mBananaImage->GetHeight();

		graphics->DrawImage(mBananaImage.get(),
			(int)(GetX() + mRunX - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	else
	{
		int wid = mMutantImage->GetWidth();
		int hit = mMutantImage->GetHeight();

		graphics->DrawImage(mMutantImage.get(),
			(int)(GetX() + mRunX - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	

}


/**
 * Updates minions state based off of banana count
 */
void CTileMinion::UpdateState()
{
	if (mBananaCount > MutantBananaThreshold)
	{
		mState = Mutant;
	}
	else if (mBananaCount > 0)
	{
		mState = Banana;
	}
}

/**
 * Feeds minion a banana, and calls updatestate
 */
void CTileMinion::FeedMinion()
{
	mBananaCount++;
	UpdateState();
}


/**
 * Gives minion some potion
 */
void CTileMinion::TakePotion()
{
	if (mState == Mutant)
	{
		mBananaCount = 0;
		mState = Normal;
	}
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileMinion::Update(double elapsed)
{
	CTile::Update(elapsed);

	if (mIsRunning)
	{
		// when the Minion is running...
		// mSpeedX is a constant pixels per second running speed...
		mRunX += mSpeedX * elapsed;
	}
}

/**  Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileMinion::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"minion");
	itemNode->SetAttribute(L"file", GetFile());	
	itemNode->SetAttribute(L"bananas", mBananaCount);
	itemNode->SetAttribute(L"SpeedX", mSpeedX);

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileMinion::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));

	mBananaCount = node->GetAttributeIntValue(L"bananas", 0);
	UpdateState();

	mSpeedX = node->GetAttributeDoubleValue(L"SpeedX", 0);

	LoadImage(mMinionImage, MinionImage);
	LoadImage(mBananaImage, BananaImage);
	LoadImage(mMutantImage, MutantImage);
}