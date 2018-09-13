/**
* \file Timer.h
*
* \author Jack Turak
*
* Class to represent a timer.
*/

#include <time.h>
#pragma once


/**
 * Class that describes a counter for the time the game
 * has been running
 */
class CTimer
{
public:
	CTimer();
	virtual ~CTimer();
	void Draw(Gdiplus::Graphics *graphics, Gdiplus::Brush *brush, Gdiplus::Font *font);

	void StopTimer();

private:
	int mStartTime; ///< Start time of timer
	int mCurrentTime; ///< Current time in timer
	int mEndTime; ///< The time when the game ends 
	int mLastEmissionTime; ///< The time since the last minion emission

	bool mStopped = false; ///< True if the game is over 
public:
	
	/**
	* Starts the timer
	*/
	void startTimer() 
	{
		mStartTime = clock();
		mLastEmissionTime = mStartTime;
	}

	/**
	* Finds time since start
	* \return elapsed time
	*/
	int timeSinceStart() 
	{
		mCurrentTime = clock();
		if (!mStopped)
		{
			return (mCurrentTime - mStartTime);
		}
		return mEndTime;
	}

	/**
	* Finds time since last minion emission
	* \return elapsed time
	*/
	int timeSinceLastEmission() 
	{
		mCurrentTime = clock();
		return (mCurrentTime - mLastEmissionTime);
	}

	/**
	*Resets the last emission time to the current time
	*/
	void ResetEmissionTime()
	{
		mLastEmissionTime = mCurrentTime;
	}

	/**
	* Clears the timer
	*/
	void Reset() 
	{
		startTimer();
		mStopped = false;
	}

};

