/**
* \file MutantMinion.h
* \author Jack Turak
* The class that defines the Mutant Minion type
*/

#pragma once
#include "Minion.h"

/**
* Class that describes the Mutant Minion type
*/
class CMutantMinion : public CMinion
{
public:
	/** Constructor
	* \param game
	*/
	CMutantMinion::CMutantMinion(CGame *game);

	/// Default constructor (disabled)
	CMutantMinion() = delete;

	/// Copy constructor (disabled)
	CMutantMinion(const CMutantMinion &) = delete;

	virtual ~CMutantMinion();

	/** gets the number of points
	* \returns mPoints the number of points that the Minion is worth
	*/
	int GetPoints() override { return mPoints; };


	void Update(double elapsed) override;

private:

	/// Number of  multiplier for points 
	int mPoints = 5;
};
