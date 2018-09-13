/**
* \file Stuart.h
* \author Jack Turak
* The class that defines the stuart minion type
*/

#pragma once
#include "Minion.h"
#include <time.h>

/**
* Class that describes the Stuart Minion type
*/
class CStuart : public CMinion
{
public:
	/** Constructor
	* \param game
	*/
	CStuart::CStuart(CGame *game);

	/// Default constructor (disabled)
	CStuart() = delete;

	/// Copy constructor (disabled)
	CStuart(const CStuart &) = delete;

	/** gets the number of points 
	* \returns mPoints the number of points that the Minion is worth
	*/
	int GetPoints() override { return mPoints; };

	virtual ~CStuart();

private:
	/// Number of  multiplier for points
	int mPoints = 1;
};
