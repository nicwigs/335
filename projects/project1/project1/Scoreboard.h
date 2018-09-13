/**
 * \file Scoreboard.h
 *
 * \author Mark Elinski
 * \author Nic Wiggins
 *
 * Class to represent a scoreboard.
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Counter.h"
#include "Timer.h"

/**
 * Class that discribes a scoreboard for villans
 */
class CScoreboard
{
public:
	CScoreboard();
	virtual ~CScoreboard();

	void Draw(Gdiplus::Graphics * graphics);

	/// reset the time and counters
	void Reset();

	void StopTimer();

	int GetTime();

	void AddAryaPoints(int points);
	void AddJuicerPoints(int points);
	void AddPokeballPoints(int points);

	/**
	* Get the arya point score
	* \return Number of points scored by arya (multiplier included)
	*/
	int GetAryaPoints() { return mAryaCounter->GetPoints(); }

	/**
	* Get the juicer point score
	* \return Number of points scored by the juicer (multiplier included)
	*/
	int GetJuicerPoints() { return mJuicerCounter->GetPoints(); }

	/**
	* Get the Pokeball point score
	* \return Number of points scored by the pokeball (multiplier included)
	*/
	int GetPokeballPoints() { return mPokeballCounter->GetPoints(); }

	/**
	* Finds time since last minion emission
	* \return elapsed time
	*/
	int timeSinceLastEmission()
	{
		return mTimer.timeSinceLastEmission();
	}

	/**
	*Resets the last emission time to the current time
	*/
	void ResetEmissionTime()
	{
		mTimer.ResetEmissionTime();
	}

private:
	/// Instantiate a timer
	CTimer mTimer;

	/// Counter for villain arya
	std::shared_ptr<CCounter> mAryaCounter;

	/// Counter for villain juicer
	std::shared_ptr<CCounter> mJuicerCounter;

	/// Counter for villain pokeball
	std::shared_ptr<CCounter> mPokeballCounter;

	/// List of counters to be drawn
	std::vector<std::shared_ptr<CCounter>> mCounterDrawList;
};

