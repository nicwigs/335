/**
 * \file MinionRunAwayVisitor.h
 *
 * \author Nic Wiggins
 *
 * Tile Visitor that tells the minions to start running
 */

#pragma once

#include "TileVisitor.h"


/**
 * A visitor that makes minions run off the screen
 */
class CMinionRunAwayVisitor : public CTileVisitor
{
public:
	CMinionRunAwayVisitor();
	~CMinionRunAwayVisitor();

	virtual void VisitMinion(CTileMinion *minion) override;
};

