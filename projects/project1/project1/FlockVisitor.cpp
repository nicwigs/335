/**
 * \file FlockVisitor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "FlockVisitor.h"

///Inital minimum distance, in virtual pixels. 
const double InitalMinDistance = 10000000000;
///Radius of minions considered for Alignment in virtual pixels.
const double AlignmentRadius = 200;

/**
 * Constructor. 
 * \param pos Position of current Minion
 */
CFlockVisitor::CFlockVisitor(CVector pos)
{
	mMinionPosition = pos;
	mMinDistance = InitalMinDistance;
	mMinionCnt = 0;
	mAlignmentAvgMinionCnt = 0;
}


/**
 * Destructor.
 */
CFlockVisitor::~CFlockVisitor()
{
}


/**
 * Visit a CMinion object
 * \param minion Minion we are visiting 
 */
void CFlockVisitor::VisitMinion(CMinion * minion)
{
	//
	//For Cohesion...
	//

	//Add position of minion
	mCohesionAverage += minion->GetP();
	//Add to count of minions
	mMinionCnt++;

	//
	//For Seperation...
	//
	double distance = mMinionPosition.Distance(minion->GetP());
	if (distance > 0 && distance < mMinDistance)
	{
		mMinDistance = distance;
		mClosestMinionPos = minion->GetP();
	}
	//
	//For Alignment...
	//
	if (distance < AlignmentRadius)
	{
		mAlignmentAverage += minion->GetV();
		mAlignmentAvgMinionCnt++;
	}
}
