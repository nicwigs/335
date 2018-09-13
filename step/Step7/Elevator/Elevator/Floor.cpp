/**
 * \file Floor.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Floor.h"
#include "Controller.h"

/**
 * Constructor.
 */
CFloor::CFloor()
{
}


/**
 * Destructor. 
 */
CFloor::~CFloor()
{
}

/** Set the value of Up for a floor.
* \param s The new value for mUp
*/
void CFloor::SetUp(bool s)
{
	mUp = s;
	mController->SetCallLight(mFloor, CElevatorController::Up, mUp);
}

/** Set the value of Down for a floor.
* \param s The new value for mDown
*/
void CFloor::SetDown(bool s)
{
	mDown = s;
	mController->SetCallLight(mFloor, CElevatorController::Down, mDown);
}

/** Set the value of Panel for a floor.
* \param p The new value for mPanel
*/
void CFloor::SetPanel(bool p)
{
	mPanel = p;
	mController->SetPanelFloorLight(mFloor, mPanel);
}
/**
 * Sets floor
 * \param floor Number of floor this is
 */
void CFloor::SetFloor(int floor)
{
	mFloor = floor;
}

/**
 * Sets controller for this floor
 * \param controller Pointer to controller of this floor
 */
void CFloor::SetController(CController * controller)
{
	mController = controller;
}

/**
 * Gets if floor is up
 * \returns True if floor is up
 */
bool CFloor::IsUp()
{
	return mUp;
}

/**
 * Gets if floor is down
 * \returns True if floor is down
 */
bool CFloor::IsDown()
{
	return mDown;
}

/**
 * Gets if floor has panel
 * \returns True if floor has panel
 */
bool CFloor::IsPanel()
{
	return mPanel;
}

/**
 * Gets number of floor
 * \returns Number the floor is 
 */
int CFloor::GetFloor()
{
	return mFloor;
}
