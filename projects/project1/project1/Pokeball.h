/**
* \file Pokeball.h
*
* \author Zoinul Choudhury
*
* This class defines the Pokeball villain
*/

#pragma once
#include "Villain.h"

/**
 * Class that describes the Pokeball villain, a sub class of CVillain
 */
class CPokeball : public CVillain
{
public:
	/** Constructor
	* \param game
	*/
	CPokeball::CPokeball(CGame *game);

	/// Default constructor (disabled)
	CPokeball() = delete;

	/// Copy constructor (disabled)
	CPokeball(const CPokeball &) = delete;

	virtual ~CPokeball();

	/** Increments the accumulated points
	* \param points the amout of points to increment by
	*/
	void AddPoints(int points);


private:
	/// Villains point multiplier
	int mPointMultiplier = 3;
};

