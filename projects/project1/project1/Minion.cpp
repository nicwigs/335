/**
* \file Minion.cpp
*
* \author Jack Turak
* \author Nic Wiggins
*/

#include "stdafx.h"
#include "Minion.h"
#include "FlockVisitor.h"
#include "Game.h"


/// Weight of cohesion vector
const int CWeight = 1;
/// Weight of Seperation vector
const int SWeight = 3;
/// Weight of Ailgnment vector
const int AWeight = 5;
/// Weight of Attraction vector
const int GruWeight = 10;
/// Max Speed of minion in pixels/second
const int MinionSpeed = 100;
/// To divide image height/width in 2
const int ImageDivisor = 2;
/// Mutant Y Position
const int MutantMinionPosY = -470;
/// Minimum X Position that the minion can be spawned at
const int minPositionX = -480;
/// Max X Position that the minion can be spawned at
const int maxPositionX = 480;

/** Constructor
* \param game The game object this minion is a part of
* \param filename The name of the image file for the minion
* \param xPos The x position of the minion
* \param yPos The y position of the minion
*/
CMinion::CMinion(CGame *game, const std::wstring &filename, double xPos, double yPos) :
	CGameItem::CGameItem(game, filename, xPos, yPos)
{
	double randXLocation = minPositionX + ((double)rand() / RAND_MAX) * (maxPositionX - minPositionX);
	SetLocation(randXLocation, MutantMinionPosY);
	mV.SetX(0);
	mV.SetY(0);
}


/**
 * Destructor. 
 */
CMinion::~CMinion()
{
}


/**
 * Checks if minion has moved out of play boundary
 * \param elapsed Time since last draw.
 */
void CMinion::UpdatePos(double elapsed)
{
	CVector newP = GetP() + mV * elapsed;

	double width = mItemImage->GetWidth();
	double height = mItemImage->GetHeight();
	double gridRadius = mGame->GetPlayingArea()->GetGridRadius();
	double gridMargin = mGame->GetPlayingArea()->GetGridMargin();


	// Check if the minion is escaping playing area and reset them inside if so
	if (newP.X() > gridRadius - gridMargin - width / ImageDivisor) {
		newP.SetX(gridRadius - gridMargin - width / ImageDivisor);
	}
	if (newP.X() < -(gridRadius - gridMargin - width / ImageDivisor)) {
		newP.SetX(-(gridRadius - gridMargin - width / ImageDivisor));
	}
	if (newP.Y() > gridRadius - gridMargin - height / ImageDivisor) {
		newP.SetY(gridRadius - gridMargin - height / ImageDivisor);
	}
	if (newP.Y() < -(gridRadius - gridMargin - height / ImageDivisor)) {
		newP.SetY(-(gridRadius - gridMargin - height / ImageDivisor));
	}
	SetLocation(newP.X(), newP.Y());

}

/**
 * Called before the image is drawn
 * \param elapsed Time since last draw. 
 */
void CMinion::Update(double elapsed)
{
	Flock();
	UpdatePos(elapsed);
}

/**
* Updates items velocity vector
*/
void CMinion::Flock()
{
	// Cohesion vector
	CVector cv;
	// Separation vector
	CVector sv;
	// Alignment vector
	CVector av;
	// Gru vector
	CVector gruV;

	CFlockVisitor visitor(GetP());
	mGame->Accept(&visitor);

	int minionCnt = visitor.GetMinionCnt();
	int alignAvgMinionCnt = visitor.GetAlignAvgMinionCnt();
	CVector cohesionCenter = visitor.GetCohesionAverage();
	CVector nearestMinionPos = visitor.GetClosestMinionPos();
	CVector alignmentAverage = visitor.GetAlignmentAverage();

	// Cohesion
	cohesionCenter /= minionCnt;
	cv = cohesionCenter - GetP();
	double len = cv.Length();
	if (len > 0)
	{
		cv /= len;
	}

	// Seperation
	sv = GetP() - nearestMinionPos;
	sv.Normalize();

	//Alignment
	alignmentAverage /= alignAvgMinionCnt;
	av = alignmentAverage;
	if (av.Length() > 0)
	{
		av.Normalize();
	}

	//Attraction
	if (mGame->GetGameOver())
	{
		gruV.SetX(0);
		gruV.SetY(0);
	}
	else
	{
		gruV = mGame->GetGruPos() - GetP();
		if (gruV.Length() > 0)
		{
			gruV.Normalize();
		}
	}

	//Combining
	mV = cv * CWeight + sv * SWeight + av * AWeight + gruV * GruWeight;
	mV.Normalize();
	mV *= MinionSpeed;
}
