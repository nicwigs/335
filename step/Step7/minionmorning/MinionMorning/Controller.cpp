/**
 * \file Controller.cpp
 *
 * \author Charles Owen
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Controller.h"

 /// The position of showerstation
const double ShowerPosition = 1.0;
/// The position of wardrobe
const double WardrobePosition = 2.0;
/// The position of inspection
const double InspectionPosition = 4.0;
/// The position of end
const double EndPosition = 5.0;
/// The time to shower
const double TimeToShower = 1.0;
/// The time to inspect
const double TimeToInspect = 1.0;
/// The time to pass
const double TimeToPass = 1.0;


/**
 * Constructor
 */
CController::CController()
{
}

/**
 * Destructor
 */
CController::~CController()
{
}

//
// Empty functions for Initialize and Service functions, as well as 
// the events have been provided for your convenience.
//

/** Initialization function.
*
* This function is called when the system is initialized. This is
* later than when it is constructed, since the controller is not installed on
* a workshop when it is constructed. This function is called when the workshop
* controller is installed and ready to control a workshop.
*/
void CController::Initialize()
{
	EnableButtonNext();
}


/** Service the workshop.
*
* This function is called once every millisecond during workshop
* operation. It provides a place to put code the controls the
* workshop. Override in a local function.
*/
void CController::Service()
{
	// Increment state time by 1 millisecond
	mStateTime += 0.001;

	switch (mState)
	{
	case ToShower:
		if (GetMinionPosition() >= ShowerPosition)
		{
			SetState(ShowerStation);
		}
		break;

	case Showering:
		if (mStateTime >= TimeToShower)
		{
			SetState(ShowerStation);
		}
		break;

	case ToWardrobe:
		if (GetMinionPosition() >= WardrobePosition)
		{
			SetState(WardrobeStation);
		}
		break;

	case ToInspection:
		if (GetMinionPosition() >= InspectionPosition)
		{
			SetState(InspectionStation);
		}
		break;

	case Inspecting:
		if (mStateTime >= TimeToInspect)
		{
			if (IsClean() && !WardrobeMalfunction()) //You passed!!!
			{
				SetState(Passed);
			}
			else
			{
				SetState(ToStrip); //FAILED!!!
			}
		}
		break;

	case Passed:
		if (mStateTime >= TimeToPass)
		{
			SetState(ToIdle);
		}
		break;

	case ToIdle:
		if (GetMinionPosition() >= EndPosition)
		{
			SetState(Idle);
		}
		break;

	case ToStrip:
		if (GetMinionPosition() <= WardrobePosition)
		{
			EnableButtonWardrobe();
			SetState(StripStation);
		}
		break;

	case BackToShower:
		if (GetMinionPosition() <= ShowerPosition)
		{
			SetState(ShowerStation);
		}
		break;

	default:
		break;
	}
}



/**
* Indication that the Next Minion button has been pressed
*
* This function is called whenever the Next On List button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnNextPressed()
{
	switch (mState)
	{
	case Idle:
		NextMinion();
		SetState(ToShower);
		break;

	default:
		break;
	}
}


/**
* Indication that the Advance button has been pressed
*
* This function is called whenever the Advance button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnAdvancePressed()
{
	switch (mState)
	{
	case ShowerStation:
		DisableButtonShower(); //Cant be placed in exit event, since we leave to go to showering. 
		SetState(ToWardrobe);
		break;

	case WardrobeStation:
		DisableButtonWardrobe();
		SetState(ToInspection);
		break;

	default:
		break;
	}
}



/**
* Indication that the Shower button has been pressed
*
* This function is called whenever the Shower button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnShowerPressed()
{
	switch (mState)
	{
	case ShowerStation:
		SetState(Showering);
		break;

	default:
		break;
	}
}

/**
* Indication that a Wardrobe button has been pressed
* \param item The item that was selected
*/
void CController::OnWardrobePressed(CWorkshopController::Wardrobe item)
{
	switch (mState)
	{
	case WardrobeStation:
		DressMinion(item);
		SetState(Dressing);
		break;

	default:
		break;
	}
}

/**
* Called when the minion has been dressed in a clothing item
*
* The process is started by a call to DressMinion()
* This function is called when the process is complete.
*/
void CController::MinionDressed()
{
	SetState(WardrobeStation);
}



/**
* Indication that the Inspect button has been pressed
*
* This function is called whenever the Inspect button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnInspectPressed()
{
	switch (mState)
	{
	case InspectionStation:
		SetState(Inspecting);
		break;

	default:
		break;
	}
}

/**
* Called when stripping a wardrobe item is completed
*
* The process is started by a call to Strip()
* This function is called when the process is complete.
*/
void CController::StripDone()
{
	SetState(StripStation);
}
/** Set a state
* \param state The new state to set
*/
void CController::SetState(States state)
{
	// Exit activities for states
	switch (mState)
	{
	case BackToShower:
	case ToStrip:
	case ToInspection:
	case ToWardrobe:
	case ToShower:
		SetConveyorSpeed(0); //Stop conveyor. 
		break;

	case Showering:
		SetShower(false);
		break;

	case Inspecting:
		DisableButtonInspect();
		break;

	default:
		break;
	}
	//End of exit activities 

	mState = state;
	mStateTime = 0;

	// Entry activities for states
	switch (mState)
	{
	case Idle:
		EnableButtonNext();
		break;

	case ToIdle:
	case ToInspection:
	case ToWardrobe:
	case ToShower:
		SetConveyorSpeed(1); //Positive values are movement to the right. 
		break;

	case ShowerStation:
		DisableButtonNext();
		EnableButtonAdvance();
		EnableButtonShower();
		break;

	case Showering:
		SetShower(true);
		break;

	case WardrobeStation:
		EnableButtonWardrobe();
		break;

	case InspectionStation:
		DisableButtonAdvance();
		EnableButtonInspect();
		break;

	case Passed:
		PassedInspection();
		break;

	case BackToShower:
	case ToStrip:
		SetConveyorSpeed(-1); //Backward!
		break;

	case StripStation:
		if (AnyClothes()) //clothed
		{
			SetState(Stripping);
		}
		else if (!AnyClothes() && !IsClean()) //naked and dirty
		{
			DisableButtonWardrobe();
			SetState(BackToShower);
		}
		else if (!AnyClothes() && IsClean()) //naked and clean 
		{
			EnableButtonAdvance();
			SetState(WardrobeStation);
		}
		break;

	case Stripping:
		Strip();
		break;
		
	default:
		break;
	}
}
