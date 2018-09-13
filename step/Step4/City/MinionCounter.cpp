/**
 * \file MinionCounter.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "MinionCounter.h"
#include "TileMinion.h"

/**
 * Constructor.
 */
CMinionCounter::CMinionCounter()
{
}


/**
 * Destructor.
 */
CMinionCounter::~CMinionCounter()
{
}

/** Visit a CTileMinion object
* \param minion Minion we are visiting */
void CMinionCounter::VisitMinion(CTileMinion *minion)
{
	mNumMinions++;
	if (minion->IsMutant())
	{
		mNumMutants++;
	}
}