/**
 * \file Scoreboard.cpp
 *
 * \author Mark Elinski
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include <algorithm>
#include "Scoreboard.h"

using namespace Gdiplus;
using namespace std;

/// Filename for the arya counter image
const wstring aryaImage = L"images/arya.png";

/// Filename for the juicer counter image
const wstring juicerImage = L"images/juicer.png";

/// Filename for the pokeball counter image
const wstring pokeballImage = L"images/pokeball.png";

/// X location to draw the counters
const int counterXLocation = 600;

/// Y pixel spacing between counters
const int counterYSpacing = 50;

/// Y location to start drawing counters
const int counterYLocation = -350;

/**
 * Constructor
 */
CScoreboard::CScoreboard()
{
	mAryaCounter = make_shared<CCounter>(this, aryaImage, 1);
	mJuicerCounter = make_shared<CCounter>(this, juicerImage, 2);
	mPokeballCounter = make_shared<CCounter>(this, pokeballImage, 3);
}


/**
 * Destructor
 */
CScoreboard::~CScoreboard()
{
}

/**  Draw the ScoreBoard
* \param graphics The graphics context to draw on
*/
void CScoreboard::Draw(Gdiplus::Graphics *graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 25);

	SolidBrush green(Color(0, 250, 0));

	mTimer.Draw(graphics, &green, &font);

	int currentDrawY = counterYLocation;
	for (unsigned int i = 0; i < mCounterDrawList.size(); i++)
	{
		shared_ptr<CCounter> counter = mCounterDrawList[i];
		counter->SetPosition(counterXLocation, currentDrawY);
		counter->Draw(graphics, &green, &font);

		if (i + 1 < mCounterDrawList.size())
		{
			currentDrawY += counter->GetHeight()/2 + counterYSpacing + mCounterDrawList[i + 1]->GetHeight()/2;
		}
	}

	currentDrawY = counterYLocation;
}

/** Reset the scoreboard
*/
void CScoreboard::Reset() {
	mTimer.Reset();
	mAryaCounter->Clear();
	mJuicerCounter->Clear();
	mPokeballCounter->Clear();

	mCounterDrawList.clear();
}

/** Stop the timer
*/
void CScoreboard::StopTimer()
{
	mTimer.StopTimer();
}

/**
 * Get the current game time
 * \returns Time since start of the timer
 */
int CScoreboard::GetTime()
{
	return mTimer.timeSinceStart();
}

/**
 * Add points to the arya point counter
 * \param points Number of points to add (without multiplier)
 */
void CScoreboard::AddAryaPoints(int points)
{
	// Check if the arya counter has been drawn yet
	if (find(mCounterDrawList.begin(), mCounterDrawList.end(),mAryaCounter) == mCounterDrawList.end())
	{
		mCounterDrawList.push_back(mAryaCounter);
	}

	mAryaCounter->AddPoints(points);
}

/**
 * Add points to the juicer point counter
 * \param points Number of points to add (without multiplier)
 */
void CScoreboard::AddJuicerPoints(int points)
{
	// Check if the juicer counter has been drawn yet
	if (find(mCounterDrawList.begin(), mCounterDrawList.end(), mJuicerCounter) == mCounterDrawList.end())
	{
		mCounterDrawList.push_back(mJuicerCounter);
	}

	mJuicerCounter->AddPoints(points);
}

/**
 * Add points to the pokeball point counter
 * \param points Number of points to add (without multiplier)
 */
void CScoreboard::AddPokeballPoints(int points)
{
	// Check if the pokeball counter has been drawn yet
	if (find(mCounterDrawList.begin(), mCounterDrawList.end(), mPokeballCounter) == mCounterDrawList.end())
	{
		mCounterDrawList.push_back(mPokeballCounter);
	}

	mPokeballCounter->AddPoints(points);
}
