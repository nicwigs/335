/**
 * \file Controller.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a controller
 */

#pragma once
#include "ElevatorController.h"
#include "Floor.h"

/**
 * Class that describes the controller
 */
class CController : public CElevatorController
{
public:
	CController();
	virtual ~CController();

	void Initalize();
	void Service() override;
	virtual void OnOpenPressed() override;
	void OnClosePressed() override;	
	void OnPanelFloorPressed(int floor) override;
	void OnCallUpPressed(int floor) override;
	void OnCallDownPressed(int floor) override;

	/// The state machine states
	enum States { Idle, DoorOpening, DoorOpen, DoorClosing, Moving, Stop };

private:

	int    mFloor = 1;      ///< The current floor
	States mState = Idle;   ///< The current state
	double mStateTime = 0;  ///< The time in a current state
	bool mGoingUp = true; ///< True if elevator is moving up
	/// An object for each floor
	CFloor mFloors[NumFloors];

	void SetState(States state);
	int WhatFloorToGoTo();
	int WhatFloorUp();
	int WhatFloorDown();

};

