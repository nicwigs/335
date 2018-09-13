/**
 * \file BuildingCounter.h
 *
 * \author Nic Wiggins
 *
 * Concrete visitor. Counts number of buildings
 */

#pragma once

#include "TileVisitor.h"

/**
 * A visitor that counts buildings
 */
class CBuildingCounter : public CTileVisitor
{
public:
	CBuildingCounter();
	~CBuildingCounter();

	void VisitBuilding(CTileBuilding * building);

	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

private:
	/// Buildings counter
	int mNumBuildings = 0;
};

