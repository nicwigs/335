/**
 * \file Juicer.cpp
 *
 * \author Zoinul Choudhury
 */

#include "stdafx.h"
#include <string>
#include "Juicer.h"

using namespace Gdiplus;
using namespace std;

/** Juicer filename
* \return const wstring
*/
const wstring JuicerImageName = L"images/juicer.png";

/// Juicer X Position
const int JuicerPosX = -300;

/// Juicer Y Position
const int JuicerPosY = -200;


/**
 * Constructor
 * \param game Pointer to game it is apart of
 */
CJuicer::CJuicer(CGame *game) : CVillain(game, JuicerImageName, JuicerPosX, JuicerPosY)
{
}


/**
 * Destructor.
 */
CJuicer::~CJuicer()
{
}

/**
 * Add points to the juicer counter
 * \param points Number of points to add
 */
void CJuicer::AddPoints(int points)
{
	GetGame()->GetScoreboard()->AddJuicerPoints(points);
}
