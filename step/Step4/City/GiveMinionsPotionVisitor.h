/**
 * \file GiveMinionsPotionVisitor.h
 *
 * \author Nic Wiggins
 *
 * Tile Visitor that gives minions potion
 */

#pragma once

#include "TileVisitor.h"


/**
 * A visitor that gives minions potion
 */
class CGiveMinionsPotionVisitor :public CTileVisitor
{
public:
	CGiveMinionsPotionVisitor();
	~CGiveMinionsPotionVisitor();

	virtual void VisitMinion(CTileMinion *minion) override;
};

