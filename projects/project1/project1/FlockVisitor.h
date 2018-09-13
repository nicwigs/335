/**
 * \file FlockVisitor.h
 *
 * \author Nic Wiggins
 *
 * Class that discribes visitor used for flock
 */


#pragma once

#include "Minion.h"


/**
 * Visitor to find info for flock algorithm. 
 */
class CFlockVisitor : public CItemVisitor
{
public:
	/// Default constructor (disabled)
	CFlockVisitor() = delete;

	CFlockVisitor(CVector pos);

	~CFlockVisitor();

	virtual void VisitMinion(CMinion *minion) override;

	/** Get the sum of position vectors
	* \returns mCohesionAverage sum of minions positions */
	CVector GetCohesionAverage() const { return mCohesionAverage; }

	/** Get the number of minions
	* \returns mMinionCnt number of minions */
	int GetMinionCnt() const { return mMinionCnt; }

	/** Get the number of minions for alignment average
	* \returns mAlignmentAvgMinionCnt number of minions */
	int GetAlignAvgMinionCnt() const { return mAlignmentAvgMinionCnt; }

	/** Get the position of closest minion
	* \returns mClosestMinionPos closest minions positon vector */
	CVector GetClosestMinionPos() const { return mClosestMinionPos; }

	/** Get the average minion velocities
	* \returns mAlignmentAverage Average minion velocity vectors */
	CVector GetAlignmentAverage() const { return mAlignmentAverage; }


private:
	///THE minion we are updating currently's position
	CVector mMinionPosition;

	///Sum of all minions position vectors
	CVector mCohesionAverage;
	///Total number of minions
	int mMinionCnt;

	///Minion Count for Alignment Average
	int mAlignmentAvgMinionCnt;

	///Position of closest minion
	CVector mClosestMinionPos;
	///Distance from this minion to nearest minion
	double mMinDistance;

	///Sum of nearest minions velocities
	CVector mAlignmentAverage;

};

