/**
* \file Arya.h
*
* \author Zoinul Choudhury
*
* This class defines the Arya villain
*/

#pragma once
#include "Villain.h"

/**
 * Class that describes the Arya villain, a sub class of CVillain
 */
class CArya : public CVillain
{
public:
	/** Constructor
	* \param game
	*/
	CArya::CArya(CGame *game);

	/// Default constructor (disabled)
	CArya() = delete;

	/// Copy constructor (disabled)
	CArya(const CArya &) = delete;

	virtual ~CArya();

	/** Increments the accumulated points
	* \param points the amout of points to increment by
	*/
	void AddPoints(int points);

private:
	/// Villains point multiplier
	int mPointMultiplier = 1;
};

