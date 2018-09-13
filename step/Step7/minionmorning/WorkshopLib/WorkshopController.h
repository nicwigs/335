/**
* \file WorkshopController.h
* Workshop controller abstract base class.
*
* This class is the base class for an workshop controller class.
* That class provides the workshop control.
*
*  \author Charles B. Owen
*/

#pragma once

#include <string>

class CWorkshopWnd;

/**
* Workshop controller base class.
*
* Workshop controllers are derived from this base class.
*/
class AFX_EXT_CLASS CWorkshopController
{
public:
    /** Constructor */
    CWorkshopController();

    /** Destructor */
    virtual ~CWorkshopController();

    /** Copy constructor disabled */
    CWorkshopController(const CWorkshopController &) = delete;
    /** Assignment operator disabled */
    void operator=(const CWorkshopController &) = delete;

	/// \cond
	void SetWorkshop(CWorkshopWnd *workshop);
	/// \endcond

    /** 
    * Initialization function.
    *
    * This function is called when the system is initialized. This is
    * later than when it is constructed, since the controller is not installed on
    * a workshop when it is constructed. This function is called when the workshop
    * controller is installed and ready to control a workshop.
    */
    virtual void Initialize() {}


	/** Service the workshop.
	*
	* This function is called once every millisecond during workshop
	* operation. It provides a place to put code the controls the
	* workshop. Override in a local function.
	*/
	virtual void Service() {};

	/** Get the Workshop this controller is for
	* \returns Pointer to CWorkshopWnd object */
	CWorkshopWnd *GetWorkshop() { return mWorkshop; }

	//
	// Getters
	//

	/** Get the minion position
	*
	* <1 means to the left of the short, >4 is to the right of inspection
	* The positions of the stages are 1, 2, 3, and 4
	* \return Position relative to the stages */
	double GetMinionPosition();

	/// Has the minion been innoculated?
	/// \return true if so
	bool IsInnoculated();

	/// Is the Minion clean?
	/// \returns true if Minion is clean.
	bool IsClean();

	/// Does the Minion have a wardrobe malfunction?
	/// \returns true if Wardrobe malfunction!
	bool WardrobeMalfunction();

	/// Is the Minion wearing any clothes?
	/// \returns true if any clothes are there
	bool AnyClothes();

	//
	// Events
	//

	/**
	* Indication that the Next Minion button has been pressed
	*
	* This function is called whenever the Next Minion button is pressed.
	* It is only called if the button is enabled.
	*/
	virtual void OnNextPressed() {}

	/**
	* Indication that the Advance button has been pressed
	*
	* This function is called whenever the Advance button is pressed.
	* It is only called if the button is enabled.
	*/
	virtual void OnAdvancePressed() {}

	/**
	* Indication that the Shower button has been pressed
	*
	* This function is called whenever the Shower button is pressed.
	* It is only called if the button is enabled.
	*/
	virtual void OnShowerPressed() {}

	/**
	* Indication that the Innoculate button has been pressed
	*
	* This function is called whenever the Innoculate button is pressed.
	* It is only called if the button is enabled.
	*/
	virtual void OnInnoculatePressed() {}

	/**
	* Indication that the Inspect button has been pressed
	*
	* This function is called whenever the Inspect button is pressed.
	* It is only called if the button is enabled.
	*/
	virtual void OnInspectPressed() {}

	/// Parameter passed to OnWardrobePressed
	enum Wardrobe { None=-1, BlueJeans=0, GreenJeans=1, Goggles1=2, Goggles2=3, NumWardrobe=4 };

	/**
	* Indication that a Wardrobe button has been pressed
	* \param item The item that was selected
	*/
	virtual void OnWardrobePressed(Wardrobe item) {}

	/**
	* Called when the minion has been dressed in a clothing item
	*
	* The process is started by a call to DressMinion()
	* This function is called when the process is complete.
	*/
	virtual void MinionDressed() {}

	/**
	 * Called when the innoculation process is done
	 *
	 * The process is started by a call to Innoculate()
	 * This function is called when the process is complete.
	 */
	virtual void InnoculationDone() {}

	/**
	 * Called when stripping a wardrobe item is completed
	 *
 	 * The process is started by a call to Strip()
 	 * This function is called when the process is complete.
 	 */
	virtual void StripDone() {}

	//
	// Activities
	//


	/**
	 * Add a new minion to the conveyor belt
	 */
	void NextMinion();

	/**
	* Set the speed of the bag conveyer belt
	*
	* \param speed Speed to set. Positive values move the bag
	* to the right, negative values to the left. Values should
	* range from -1 to 1 (max left speed to max right speed)
	*/
	void SetConveyorSpeed(double speed);

	/// Enable the Next Minion button
	void EnableButtonNext();

	/// Disable the Next Minion button
	void DisableButtonNext();

	/// Enable the Advance button
	void EnableButtonAdvance();

	/// Disable the Advance button
	void DisableButtonAdvance();

	/// Enable the Shower button
	void EnableButtonShower();

	/// Disable the Shower button
	void DisableButtonShower();

	/// Enable the Wardrobe button
	void EnableButtonWardrobe();

	/// Disable the Wardrobe button
	void DisableButtonWardrobe();

	/// Enable the Innoculate button
	void EnableButtonInnoculate();

	/// Disable the Innoculate button
	void DisableButtonInnoculate();

	/// Enable the Inspect button
	void EnableButtonInspect();

	/// Disable the Inspect button
	void DisableButtonInspect();

	/** Set the shower on or off
	* \param enable true for on */
	void SetShower(bool enable);

	/** Apply a wardrobe item to the minion
	 * \param item Wardrobe item to apply */
	void DressMinion(Wardrobe item);

	/** Start the innoculate process for a Minion */
	void StartInnoculate();

	/// Kill the Minion dead
	void KillMinion();

	/// Indicate the Minion has passed inspection
	void PassedInspection();

	/// Cause the Minion to lose an item of clothing
	void Strip();

private:
    /// The workshop we are controlling
    CWorkshopWnd *mWorkshop = nullptr;
};

