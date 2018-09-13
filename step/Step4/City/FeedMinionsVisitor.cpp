/**
 * \file FeedMinionsVisitor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "FeedMinionsVisitor.h"
#include "TileMinion.h"


/**
 * Constructor.
 */
CFeedMinionsVisitor::CFeedMinionsVisitor()
{
}


/**
 * Destructor.
 */
CFeedMinionsVisitor::~CFeedMinionsVisitor()
{
}


/**
 * Visit a CTileMinion object
 * \param minion Minion tile we are visiting 
 */
void CFeedMinionsVisitor::VisitMinion(CTileMinion *minion)
{
	minion->FeedMinion();
}