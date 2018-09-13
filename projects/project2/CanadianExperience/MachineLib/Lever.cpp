/**
 * \file Lever.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Lever.h"

const int LeverWidth = 40; ///< Pixel width of levers
const double PI2 = 6.28318530718; ///< 2*PI

/**
 * Constructor
 * \param length The length of the lever.  
 */
CLever::CLever(double length)
{
	mLength = length;
	mDriveLength = length / 2; //default to having drive end the right side, end
	mRotationSource.SetComponent(this); //Rotation source knows lever
	mPositionSource.SetComponent(this); //Position source knows lever
	mSink.SetNegotiator(this); //Sink source knows lever. 

	Rectangle(-length/2, LeverWidth / 2, length, LeverWidth); //Make Lever

}

/**
 * Destrutor. 
 */
CLever::~CLever()
{
}
/**
* Get the rotation source of the lever.
* \returns mSource, pointer to rotationsource.
*/
CRotationSource * CLever::GetRotationSource()
{
	return &mRotationSource;
}
/**
* Get the position source of the lever.
* \returns mSource, pointer to position source.
*/
CPositionSource * CLever::GetPositionSource()
{
	return &mPositionSource;
}
/**
* Get the sink of the lever
* \returns mSink, pointer to the sink.
*/
CNegotiationSink * CLever::GetSink()
{
	return &mSink;
}

/**
 * Gets the right point of lever
 * \returns Point of lever that rod is attached to
 */
Gdiplus::Point CLever::GetDrivePoint()
{
	double rotation = GetRotation();
	double x = GetPosition().X + mDriveLength*cos(rotation*PI2);
	double y = GetPosition().Y - mDriveLength*sin(rotation*PI2);
	return Gdiplus::Point(x, y);
}
/**
* Gets the left point of lever
* \returns Point of lever that rod is attached to
*/
Gdiplus::Point CLever::GetPushPoint()
{
	double rotation = GetRotation();
	double x = GetPosition().X - mDriveLength*cos(rotation*PI2);
	double y = GetPosition().Y - mDriveLength*sin(rotation*PI2);
	return Gdiplus::Point(x, y);
}

/**
 * Sets the drive end of the lever
 * \param x Length from pivot to joint
 */
void CLever::SetDriveLength(double x)
{
	mDriveLength = x;
}

/**
 * Finds new position of lever end and rod
 * \param rod Pointer to the rod
 */
void CLever::Negotiate(CRod * rod)
{
		
	//needed lengths
	double a = mDriveLength;
	double b = rod->GetLength();

	//end of arm location
	double armEndX = rod->GetX();
	double armEndY = rod->GetY();

	//length between center of lever and arm end - law of cosines
	double c = sqrt(pow((double)(GetY() - armEndY),2.0)
		+ pow((double)(GetX() - armEndX),2.0));

	//angle from horizontal to c
	double delta = atan2(-(GetY() - armEndY), (GetX() - armEndX));
	
	//angle between rod and c
	double alpha = acos((pow(b, 2.0) + pow(c, 2.0) - pow(a, 2.0)) / (2 * b*c));
	
	//angle between rod and horrizontal
	double theta = delta - alpha;
	
	//New point of lever end/rod end
	double newSharedX = armEndX + b*cos(-theta);
	double newSharedY = armEndY + b*sin(-theta);
	
	//angle of lever from horizontal ... set lever angle
	double phi = atan2((newSharedY - GetY()), (newSharedX - GetX()));

	//Fractional revolutions from radians
	phi = phi / PI2; 
	theta = -theta / PI2; 

	//Set rotations of lever and rod
	SetRotation(phi); //Lever	
	rod->SetRotation(theta); //rod
	
	mRotationSource.Update(phi);
	mPositionSource.Update(GetPushPoint()); 
}
