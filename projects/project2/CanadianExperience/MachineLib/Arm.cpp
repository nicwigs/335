/**
 * \file Arm.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Arm.h"
const int ArmWidth = 10; ///< Pixel width of arms
const double PI2 = 6.28318530718; ///< 2*PI
const int Half = 2; ///< to divide width in two

/**
 * Constructor 
 * \param length Length of Arm
 */
CArm::CArm(double length)
{
	mLength = length;

	mSource.SetComponent(this); //source knows arm
	mSink.SetComponent(this); //sink knows arm
		
	Rectangle(-ArmWidth / Half, 0, ArmWidth, length); //Make arm
}
/**
* Destructor.
*/
CArm::~CArm()
{
}
/**
* Get the source of the arm.
* \returns mSource, pointer to source.
*/
CPositionSource * CArm::GetSource()
{
	return &mSource;
}
/**
* Get the sink of the arm
* \returns mSink, pointer to the sink.
*/
CRotationSink * CArm::GetSink()
{
	return &mSink;
}

/**
 * Gets the moving point of the arm
 * \returns point that rod is attached to. 
 */
Gdiplus::Point CArm::GetEndPoint()
{
	double rotation = GetRotation();
	double x = GetPosition().X + mLength*sin(rotation*PI2);
	double y = GetPosition().Y + -mLength*cos(rotation*PI2);
	return Gdiplus::Point(x, y);
}
/**
* Set the rotation of the polygon
* \param rotation Rotation in turns, where 0-1 is one revolution.
*/
void CArm::SetRotation(double rotation)
{
	CPolygon::SetRotation(rotation);
	mSource.Update(GetEndPoint());
}


