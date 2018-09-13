/**
 * \file MinionRunAwayVisitor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "MinionRunAwayVisitor.h"
#include "TileMinion.h"


/**
 * Constructor.
 */
CMinionRunAwayVisitor::CMinionRunAwayVisitor()
{
}


/**
 * Destructor.
 */
CMinionRunAwayVisitor::~CMinionRunAwayVisitor()
{
}

/**
* Visit a CTileMinion object
* \param minion Minion tile we are visiting
*/
void CMinionRunAwayVisitor::VisitMinion(CTileMinion *minion)
{
	minion->mIsRunning = true;
}
