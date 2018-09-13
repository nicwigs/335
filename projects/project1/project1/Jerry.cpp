/**
* \file Jerry.cpp
* \author Jack Turak
*/

#include "stdafx.h"
#include <string>
#include "Jerry.h"

using namespace Gdiplus;
using namespace std;

/** Jerry filename
* \return const wstring
*/
const wstring JerryImageName = L"images/jerry.png";

/// Jerry X Position
const int JerryPosX = 50;

/// Jerry Y Position
const int JerryPosY = -470;

/**
 * Constructor.
 * \param game Pointer to the game it is apart of. 
 */
CJerry::CJerry(CGame *game) : CMinion(game, JerryImageName, JerryPosX, JerryPosY)
{
}

/**
 * Destructor. 
 */
CJerry::~CJerry()
{
}
