/**
 * \file Villain.cpp
 *
 * \author Zoinul Choudhury
 */

#include "stdafx.h"
#include "Villain.h"

 /** Constructor
 * \param game The game object this villain is a part of
 * \param filename The name of the image file for the villain
 * \param xPos The x position of the villain
 * \param yPos The y position of the villain
 */
CVillain::CVillain(CGame *game, const std::wstring &filename, double xPos, double yPos) : 
	CGameItem::CGameItem(game, filename, xPos, yPos)
{
}

void CVillain::AddPoints(int points)
{
}


/**
 * Destructor. 
 */
CVillain::~CVillain()
{
}
