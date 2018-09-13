/**
 * \file Rod.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Rod.h"
const int ArmWidth = 6; ///< Pixel width of arms
const double PI2 = 6.28318530718; ///< 2*PI
/**
 * Constructor from points. Given two points draws line inbetween. 
 * \param a Point getting energy
 * \param b Point giving energy
 */
CRod::CRod(Gdiplus::Point a, Gdiplus::Point b)
{
	mLength = sqrt(pow(b.Y - a.Y, 2.0) + pow(b.X - a.X, 2.0));

	Rectangle( 0, ArmWidth / 2, (int)mLength, ArmWidth); //make rod
	CComponent::SetPosition(a.X, a.Y); //position is where it get energy


	//angle in rad from horizontal
	double delta = atan2((b.Y - a.Y), (b.X - a.X));
	delta = delta / PI2; //get into fractional revolutions
	SetRotation(delta); 

	mSource.SetComponent(this); //source knows rod
	mSink.SetComponent(this); //sink knows rod
}


/**
 * Destructor. 
 */
CRod::~CRod()
{
}
/**
* Get the source of the rod
* \returns mSource, pointer to source.
*/
CNegotiationSource * CRod::GetSource()
{
	return &mSource;
}
/**
* Get the sink of the rod
* \returns mSink, pointer to the sink.
*/
CPositionSink * CRod::GetSink()
{
	return &mSink;
}

/**
 * Gets length of rod
 * \returns mLength, length of rod
 */
double CRod::GetLength()
{
	return mLength;
}
/**
* Set the position for this component.
* \param x X location (pixels)
* \param y Y location (pixels)
*/
void CRod::SetPosition(int x, int y)
{
	CComponent::SetPosition(x, y);
	mSource.Update(this);
}

