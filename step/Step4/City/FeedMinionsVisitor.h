/**
 * \file FeedMinionsVisitor.h
 *
 * \author Nic Wiggins
 *
 * Tile visitor that feeds minions
 */

#pragma once

#include "TileVisitor.h"


/**
 * A visitor that feeds minions bananas
 */
class CFeedMinionsVisitor : public CTileVisitor
{
public:

	CFeedMinionsVisitor();
	~CFeedMinionsVisitor();

	virtual void VisitMinion(CTileMinion *minion) override;
};

