/**
* \file Timer.cpp
*
* \author Jack Turak
* \author Nic Wiggins
*
*/

#include "stdafx.h"
#include <string>

#include "Timer.h"
#include <string>
#include <sstream>


using namespace Gdiplus;
using namespace std;


/// The range from the center to the timer X (virtual pixels)
const int TimerX = 550;

/// The range from the center to the timer Y (virtual pixels)
const int TimerY = -500;

/// Converts timer value to time in seconds
const int TimerToSeconds = 1000;

/// Converts seconds to minutes
const int SecondsToMinutes = 60;


/**
 * Constructor.
 */
CTimer::CTimer()
{
	//Start timer once instantiated 
	startTimer(); 
}


/**
 * Destructor. 
 */
CTimer::~CTimer()
{
}

/**  Draw the timer
* \param graphics The graphics context to draw on
* \param brush The pen to use to draw with
* \param font The font of text to write with. 
*/
void CTimer::Draw(Gdiplus::Graphics *graphics, Gdiplus::Brush *brush, Gdiplus::Font *font)
{	
	int time = timeSinceStart();
	time /= TimerToSeconds;						//2 seconds is refered to as 2000
	int minutes = time / SecondsToMinutes;
	int seconds = time % SecondsToMinutes;

	wstringstream str;

	// if seconds are only single digits, pad with 0
	if (seconds < 10)
	{
		str << minutes << L":0" << seconds;
	}
	else
	{
		str << minutes << L":" << seconds;
	}
	graphics->DrawString(str.str().c_str(), -1, font, PointF((float)TimerX, (float)TimerY),brush);
}


/**
 * Stop the timer at the end of the game 
 */
void CTimer::StopTimer()
{
	mStopped = true;
	mEndTime = mCurrentTime - mStartTime;
}
