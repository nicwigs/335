/**
* \file MutantMinion.cpp
* \author Jack Turak
*/

#include "stdafx.h"
#include <string>
#include "MutantMinion.h"

using namespace Gdiplus;
using namespace std;

/// Speed multiplier of mutant mnion vs minion in pixels/second
const int MutantSpeedMultiplier = 2;

/** MutantMinion filename
* \return const wstring
*/
const wstring MutantMinionImageName = L"images/mutant.png";

/// Mutant X Position
const int MutantMinionPosX = 50;

/// Mutant Y Position
const int MutantMinionPosY = -470;

/**
 * Constructor. 
 * \param game Pointer to the game it is a part of. 
 */
CMutantMinion::CMutantMinion(CGame *game) : CMinion(game, MutantMinionImageName, MutantMinionPosX, MutantMinionPosY)
{
}

/**
 * Destructor. 
 */
CMutantMinion::~CMutantMinion()
{
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw.
*/
void CMutantMinion::Update(double elapsed)
{
	Flock();
	mV *= MutantSpeedMultiplier;
	CMinion::UpdatePos(elapsed);
}