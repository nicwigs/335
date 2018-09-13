/**
 * \file GameItem.cpp
 *
 * \author Ian Guswiler, Mark Elinski
 */

#include "stdafx.h"
#include "GameItem.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;



/** Constructor
* \param game The game object this villain is a part of
* \param filename The name of the image file for the villain
* \param xPos The x position of the villain
* \param yPos The y position of the villain
*/
CGameItem::CGameItem(CGame *game, const std::wstring &filename, double xPos, double yPos) : mGame(game)
{
	mP.SetX(xPos);
	mP.SetY(yPos);

	mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mItemImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}


/**
 * Destructor
 */
CGameItem::~CGameItem()
{
}

/**
 * Draw this item.
 * \param graphics Graphics device to draw on 
 */
void CGameItem::Draw(Gdiplus::Graphics * graphics)
{
	double width = mItemImage->GetWidth();
	double height = mItemImage->GetHeight();

	graphics->DrawImage(mItemImage.get(),
		float(GetX() - width / 2), float(GetY() - height / 2),
		(float)width, (float)height);
}


/**
*  Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CGameItem::HitTest(int x, int y)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image.
	// Subtracting the center makes x, y relative to the center of 
	// the image. Adding half the size makes x, y relative to the top 
	// corner of the image.
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mItemImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mItemImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}