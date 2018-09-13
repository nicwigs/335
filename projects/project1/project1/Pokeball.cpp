/**
* \file Pokeball.cpp
*
* \author Zoinul Choudhury
*/

#include "stdafx.h"
#include <string>
#include "Pokeball.h"
#include "Minion.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/** Pokeball filename
* \return const wstring
*/
const wstring PokeballImageName = L"images/pokeball.png";

/// Pokeball X Position
const int PokeballPosX = 300;

/// Pokeball Y Position
const int PokeballPosY = -200;


/**
 * Constructor.
 * \param game Pointer to game it is apart of.
 */
CPokeball::CPokeball(CGame *game) : CVillain(game, PokeballImageName, PokeballPosX, PokeballPosY)
{
}


/**
 * Destructor.
 */
CPokeball::~CPokeball()
{
}

/**
 * Add points to the pokeball counter
 * \param points Number of points to add
 */
void CPokeball::AddPoints(int points)
{
	GetGame()->GetScoreboard()->AddPokeballPoints(points);
}