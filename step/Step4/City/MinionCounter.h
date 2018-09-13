/**
 * \file MinionCounter.h
 *
 * \author Nic Wiggins
 *
 * Concrete visitor, counts number of minions
 */

#pragma once

#include "TileVisitor.h"


/**
 * Visitor that counts the number of minions
 */
class CMinionCounter : public CTileVisitor
{
public:
	CMinionCounter();
	~CMinionCounter();

	void VisitMinion(CTileMinion * minion);

	/** Get the number of minions
	* \returns Number of minions */
	int GetNumMinions() const { return mNumMinions; }

	/** Get the number of mutants
	* \returns Number of mutants */
	int GetNumMutants() const { return mNumMutants; }

private:
	/// Minion Counter
	int mNumMinions = 0;

	///Mutant Counter
	int mNumMutants = 0;
};

