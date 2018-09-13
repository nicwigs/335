/**
* \file Jerry.h
* \author Jack Turak
* The class that defines the Jerry minion type
*/

#pragma once
#include "Minion.h"

/**
* Class that describes the Jerry Minion type
*/
class CJerry : public CMinion
{
public:
	/** Constructor
	* \param game
	*/
	CJerry::CJerry(CGame *game);

	/// Default constructor (disabled)
	CJerry() = delete;

	/// Copy constructor (disabled)
	CJerry(const CJerry &) = delete;

	/** gets the number of points
	* \returns mPoints the number of points that the Minion is worth
	*/
	int GetPoints() override { return mPoints; };

	virtual ~CJerry();

private:
	/// Number of  multiplier for points
	int mPoints = 1;
};
