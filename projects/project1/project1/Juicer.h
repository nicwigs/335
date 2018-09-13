/**
 * \file Juicer.h
 *
 * \author Zoinul Choudhury
 *
 * This class defines the Juicer villain
 */

#pragma once
#include "Villain.h"
#include "Minion.h"
#include "Game.h"

 /**
  * Class that describes the Juicer villain, a sub class of CVillain
  */
class CJuicer : public CVillain
{
public:
	/** Constructor
	* \param game
	*/
	CJuicer::CJuicer(CGame *game);

	/// Default constructor (disabled)
	CJuicer() = delete;

	/// Copy constructor (disabled)
	CJuicer(const CJuicer &) = delete;

	virtual ~CJuicer();

	/** Increments the accumulated points
	* \param points the amout of points to increment by
	*/
	void AddPoints(int points);

private:
	/// Villains point multiplier
	int mPointMultiplier = 2;
};

