/**
 * \file GiveMinionsPotionVisitor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "GiveMinionsPotionVisitor.h"
#include "TileMinion.h"


/**
 * Constructor.
 */
CGiveMinionsPotionVisitor::CGiveMinionsPotionVisitor()
{
}


/**
 * Destructor.
 */
CGiveMinionsPotionVisitor::~CGiveMinionsPotionVisitor()
{
}


/**
* Visit a CTileMinion object
* \param minion Minion tile we are visiting
*/
void CGiveMinionsPotionVisitor::VisitMinion(CTileMinion *minion)
{
	minion->TakePotion();
}