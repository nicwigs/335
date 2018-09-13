/**
 * \file PointHistory.cpp
 *
 * \author Charles Owen
 */


#include "stdafx.h"
#include "PointHistory.h"

using namespace std;
using namespace Gdiplus;

/**
* Constructor
*/
CPointHistory::CPointHistory()
{
	// Lists are initially empty
	mHead = nullptr;
	mTail = nullptr;
}


/**
 * Destructor
 */
CPointHistory::~CPointHistory()
{
}



/**
* Add a pointer to the collection of points.
* \param p Point to add
*/
void CPointHistory::Add(Gdiplus::Point p)
{
	// On first add we create the first node
	if (mHead == nullptr)
	{
		mHead = make_shared<PointBin>();
		mTail = mHead;
	}

	// Is the last node (tail) full?
	if (mTail->GetCnt() >= PointBin::MaxPoints)
	{
		// If so, add a new tail node
		auto newTail = make_shared<PointBin>();
		mTail->SetNext(newTail);
		mTail = newTail;
	}

	// Assertion: Tail not is not empty
	// Add point to the tail node
	mTail->Add(p);
}


/**
* Add a point to this bin.
* \param point Point to add to this bin
* \return true if successful, false if bin is full
*/
bool CPointHistory::PointBin::Add(Gdiplus::Point point)
{
	if (mCnt >= MaxPoints) {
		return false;
	}

	mPoints[mCnt++] = point;

	return true;
}
