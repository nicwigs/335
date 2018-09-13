/**
* \file Arya.cpp
*
* \author Zoinul Choudhury
*/

#include "stdafx.h"
#include <string>
#include "Arya.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/** Arya filename
* \return const wstring
*/
const wstring AryaImageName = L"images/arya.png";

/// Arya X Position
const int AryaPosX = 0;

/// Arya Y Position
const int AryaPosY = 300;


/**
 * Constructor. 
 * \param game Pointer to game it is apart of. 
 */
CArya::CArya(CGame *game) : CVillain(game, AryaImageName, AryaPosX, AryaPosY)
{
}


/**
 * Destructor. 
 */
CArya::~CArya()
{
}

/**
 * Add points to the villain's counter
 * \param points Number of points to add
 */
void CArya::AddPoints(int points)
{
	GetGame()->GetScoreboard()->AddAryaPoints(points);
}