/**
 * \file Counter.cpp
 *
 * \author Zoinul Choudhury
 */


#include "stdafx.h"
#include <string>
#include <sstream>
#include "Counter.h"
#include "Scoreboard.h"

using namespace Gdiplus;
using namespace std;

/// Y pixel spacing count between the image and the point count
const int countSpace = 5;

/**
 * Constructor. 
 * \param scoreboard Scoreboard object that holds the points and timer
 * \param filename Filename for the image to load
 * \param pointMultiplier Number to multiply points by for display
 */
CCounter::CCounter(CScoreboard *scoreboard, const std::wstring & filename, int pointMultiplier)
{
	mScoreboard = scoreboard;
	mPointMultiplier = pointMultiplier;

	mImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}


/**
 * Destructor. 
 */
CCounter::~CCounter()
{
}

/**  Draw the counter
* \param graphics The graphics context to draw on
* \param brush The pen to use to draw with
* \param font The font of text to write with.
*/
void CCounter::Draw(Gdiplus::Graphics *graphics, Gdiplus::Brush *brush, Gdiplus::Font *font)
{
	wstringstream wss;

	wstring pointCountString = to_wstring(GetPoints());

	wss << pointCountString;

	double width = mImage->GetWidth();
	double height = mImage->GetHeight();

	graphics->DrawImage(mImage.get(),
		float(GetX() - width / 2), float(GetY() - height / 2),
		(float)width, (float)height);

	graphics->DrawString(wss.str().c_str(), -1, font, PointF(float(GetX()), float(GetY() + height/2)), brush);

}