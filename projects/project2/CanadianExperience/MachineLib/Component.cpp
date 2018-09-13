/**
 * \file Component.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Component.h"
#include "WorkingMachine.h"

/**
 * Constructor. 
 */
CComponent::CComponent()
{
}

/**
 * Destructor. 
 */
CComponent::~CComponent()
{
}
/**
* Set the position for this component.
* \param x X location (pixels)
* \param y Y location (pixels)
*/
void CComponent::SetPosition(int x, int y)
{
	mPosition = Gdiplus::Point(x, y);
}

/**
 * Gets position of component
 * \returns position The position of the component
 */
Gdiplus::Point CComponent::GetPosition()
{
	return mPosition;
}


/**
 * Draws the component on the screen
 * \param graphics Gdiplus grahics object
 * \param position Position of machine on screen
 */
void CComponent::Draw(Gdiplus::Graphics *graphics, Gdiplus::Point position)
{
	int drawX = position.X + mPosition.X; //Position of machine + component position
	int drawY = position.Y + mPosition.Y; 

	DrawPolygon(graphics, drawX, drawY);
}
/**
* Set the machine using this component
* \param machine WorkingMachine using this component
*/
void CComponent::SetMachine(CWorkingMachine * machine)
{
	mWorkingMachine = machine;
}

/**
 * Gets x position
 * \returns X, position in x
 */
int CComponent::GetX()
{
	return mPosition.X;
}

/**
 * Gets y position
 * \returns Y, position in y
 */
int CComponent::GetY()
{
	return mPosition.Y;
}
