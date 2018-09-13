/**
* \file Stuart.cpp
* \author Jack Turak
*/

#include "stdafx.h"
#include <string>
#include "Stuart.h"
#include <time.h>
#include <cstdlib>

using namespace Gdiplus;
using namespace std;

/** Stuart filename
* \return const wstring
*/
const wstring StuartImageName = L"images/stuart.png";

/// Stuart X Position Max xLocation is 480, Min is -480
int StuartPosX = 0;

/// Stuart Y Position
const int StuartPosY = -470;

/**
 * Constructor. 
 * \param game Pointer to the game it is a part of. 
 */
CStuart::CStuart(CGame *game) : CMinion(game, StuartImageName, StuartPosX, StuartPosY)
{
}

/**
 * Destructor. 
 */
CStuart::~CStuart()
{
}
