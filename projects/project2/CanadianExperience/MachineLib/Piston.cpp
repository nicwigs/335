/**
 * \file Piston.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Piston.h"

const double PI2 = 6.28318530718; ///< 2*PI
const double HalfPI = 1.57079632679; ///< PI/2
const double ConnectionDistance = 13.0 / 215.0; ///< Distance from top of image to eye hold


/**
 * Constructor. 
 * \param height Height of piston
 * \param width Width of piston
 */
CPiston::CPiston(double height, double width)
{
	mSink.SetNegotiator(this); //Sink source knows piston
	//Attahment point of piston is at 0,0
	Rectangle(-width / 2, -ConnectionDistance*height, width, -height); //Make Lever
}

/**
 * Destructor. 
 */
CPiston::~CPiston()
{
}
/**
* Get the sink of the lever
* \returns mSink, pointer to the sink.
*/
CNegotiationSink * CPiston::GetSink()
{
	return &mSink;
}
/**
* Finds new position of lpiston end and rod
* \param rod Pointer to the rod
*/
void CPiston::Negotiate(CRod * rod)
{
	double alpha = asin((GetX() - rod->GetX()) / rod->GetLength());
	double beta = HalfPI - alpha;
	double b = rod->GetLength()*sin(beta);
	double pistonY = rod->GetY() + b;

	beta /= PI2; //Get fractional revolutions

	SetPosition(GetX(), pistonY);
	rod->SetRotation(beta);

}
