/**
 * \file Gear.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Gear.h"

const double ToothDepth = 5;     ///< Depth of a tooth in pixels
const double ToothWidth = 0.33;  ///< Width of a tooth at the top as fraction of tooth pitch
const double ToothSlope = 0.1;   ///< Fraction of pitch where the tooth slopes up or down
const double PI2 = 6.28318530718; ///< 2*PI
/**
 * Constructor 
 * \param radius Radius of gear in pixels
 * \param teeth Number of teeth 
 */
CGear::CGear(double radius, int teeth)
{
	mRadius = radius;
	mTeeth = teeth;

	mSource.SetComponent(this); //source knows gear
	mSink.SetComponent(this); //sink knows gear. 

	//make the gear
	// Where the tooth starts in the arc
	double toothStart = 1.0 - ToothWidth - ToothSlope * 2;
	double innerRadius = radius - ToothDepth;

	for (int t = 0; t < teeth; t++)
	{
		double angle1 = double(t) / double(teeth) * PI2;
		double angle2 = double(t + toothStart) / double(teeth) * PI2;
		double angle3 = double(t + toothStart + ToothSlope) / double(teeth) * PI2;
		double angle4 = double(t + toothStart + ToothSlope + ToothWidth) / double(teeth) * PI2;
		double angle5 = double(t + toothStart + ToothSlope * 2 + ToothWidth) / double(teeth) * PI2;

		AddPoint(innerRadius * cos(angle1), innerRadius * sin(angle1));
		AddPoint(innerRadius * cos(angle2), innerRadius * sin(angle2));
		AddPoint(radius * cos(angle3), radius * sin(angle3));
		AddPoint(radius * cos(angle4), radius * sin(angle4));
		AddPoint(innerRadius * cos(angle5), innerRadius * sin(angle5));
	}
}

/**
 * Destructor. 
 */
CGear::~CGear()
{
}
/**
* Get the source of the gear.
* \returns mSource, pointer to source.
*/
CRotationSource * CGear::GetSource()
{
	return &mSource;
}

/**
 * Get the sink of the gear
 * \returns mSink, pointer to the sink. 
 */
CRotationSink * CGear::GetSink()
{
	return &mSink;
}

/**
 * Set the rotation of the polygon
 * \param rotation Rotation in turns, where 0-1 is one revolution.
 */
void CGear::SetRotation(double rotation)
{
	CPolygon::SetRotation(rotation);
	mSource.Update(rotation);
}
