/**
 * \file Motor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Motor.h"
using namespace std;

/// Maximum rotational speed of shaft (rotations/second)
const double MaxSpeed = 1;
/**
 * Constructor. 
 */
CMotor::CMotor()
{
	mSpeed = 1.0;
	mSource.SetComponent(this);
}

/**
 * Destructor. 
 */
CMotor::~CMotor()
{
}

/**
* Set  the bend angle
* \param speed Speed from 0 to 1, where 1 is full speed
*/
void CMotor::SetSpeed(double speed)
{
	mSpeed = speed;
}

/**
* Draws the component on the screen
* \param graphics Gdiplus grahics object
* \param position Position of machine on screen
*/
void CMotor::Draw(Gdiplus::Graphics * graphics, Gdiplus::Point position)
{
	CComponent::Draw(graphics, position);

	int drawX = position.X + GetPosition().X; //Position of machine + component position
	int drawY = position.Y + GetPosition().Y;

	mShaft->DrawPolygon(graphics, drawX, drawY);
}

/**
 * Sets the shaft of the motor
 * \param shaft The rotating part of the motor. 
 */
void CMotor::SetShaft(std::shared_ptr<CPolygon> shaft)
{
	mShaft = shaft;
}

/**
 * Updates rotation of motor shaft
 * \param elapsed Time since start. 
 */
void CMotor::Update(double elapsed)
{
	double rot = mSpeed*MaxSpeed*elapsed;
	mShaft->SetRotation(rot);
	mSource.Update(rot);
}

/**
 * Get the source of the motor.
 * \returns mSource, pointer to source. 
 */
CRotationSource * CMotor::GetSource()
{
	return &mSource;
}



