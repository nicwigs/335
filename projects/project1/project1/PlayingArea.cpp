/**
 * \file PlayingArea.cpp
 *
 * \author Nic Wiggins
 */


#include "stdafx.h"
#include "PlayingArea.h"
#include <string>
#include "Stuart.h"

using namespace Gdiplus;
using namespace std;



 /** Stuart filename
 * \return const wstring
 */
const wstring StuartImageName = L"images/stuart.png";

using namespace Gdiplus;

 /// The size of the playing area square in virtual pixels
const double CPlayingArea::GridSize = 1000.0;

/// The range from the center to an edge for the playing area
/// in virtual pixels
const double CPlayingArea::GridRadius = CPlayingArea::GridSize / 2.0;

/// Do not allow Minions or Gru to come closer than this distance
/// to the playing area edges (virtual pixels)
const double CPlayingArea::GridMargin = 2.0;

/**
 * Constructor. 
 */
CPlayingArea::CPlayingArea()
{
}


/**
 * Destructor. 
 */
CPlayingArea::~CPlayingArea()
{
}

/**  Draw a border around the tile
* \param graphics The graphics context to draw on
* \param pen The pen to use to draw with
*/
void CPlayingArea::DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen)
{
	Point points[] = { { -(int)GridRadius, -(int)GridRadius },{ (int)GridRadius, -(int)GridRadius },{ (int)GridRadius, (int)GridRadius },{ -(int)GridRadius, (int)GridRadius },{ -(int)GridRadius, -(int)GridRadius } };

	graphics->DrawLines(pen, points, 5);
	
}
