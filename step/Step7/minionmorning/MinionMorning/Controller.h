/**
 * \file Controller.h
 *
 * \author Charles Owen
 * \author Nic Wiggins
 *
 * Main controller for the Minion Morning system
 */

#include "WorkshopController.h"

#pragma once

/**
 * Main controller for the Minion Morning system
 */
class CController :
    public CWorkshopController
{
public:
    CController();
    virtual ~CController();
    
    virtual void Initialize() override;
    virtual void Service() override;

	virtual void OnNextPressed() override;
	virtual void OnAdvancePressed() override;
	virtual void OnShowerPressed() override;
	virtual void OnWardrobePressed(CWorkshopController::Wardrobe item) override;
	virtual void MinionDressed() override;
	virtual void OnInspectPressed() override;
	virtual void StripDone() override;

	/// The state machine states
	enum States { Idle, ToShower, ShowerStation, Showering, ToWardrobe, WardrobeStation
					, Dressing, ToInspection, InspectionStation, Inspecting, Passed, ToStrip
					, ToIdle, StripStation, Stripping, BackToShower};

private:

	States mState = Idle; ///< The current state
	double mStateTime = 0;  ///< The time in a current state
	void SetState(States state);

};

