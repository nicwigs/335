/**
 * \file WorkshopWnd.h
 * Workshop simulation class
 *
 * \author Charles Owen
 * \version 1.01 11-25-2015 Initial Development
 * \version 1.02 11-21-2017 Minion Morning version
 */

#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Button2.h"
#include "ButtonWardrobe.h"
#include "MinionFactory.h"
#include "Needle.h"
#include "Minion.h"

#include "WorkshopController.h"
#include "TimeManagement.h"

/**
 * Workshop simulation class
 *
 * This class simulates the morning ritual in the Minion
 * workshop. We have to clean, cloth, and immunize Minions
 * so they can face the day.
 *
 * You do not directly access the functions in CWorkshopWnd.
 * Instead, use the functions in CWorkshopController for 
 * managing all Workshop operations.
 */
class AFX_EXT_CLASS CWorkshopWnd : public CWnd
{
public:
    /**
    * Constructor
    */
	CWorkshopWnd();

    /**
    * Destructor
    */
	virtual ~CWorkshopWnd();
	
	/**
	 * Set a controller for this window
	 * \param c Installed controller */
	void SetController(std::shared_ptr<CWorkshopController> c);

	/// Set the display scaling
	/// \param scale Display scaling
	void SetScale(double scale) { mScale = scale; }

	/// Get the current display scaling
	/// \return Scale
	double GetScale() const { return mScale; }

    /**
    * Update the simulation based on time
    *
    * This is normally only called from testing. It advances the simulation
    * by some elapsed time. Note that this does not have to be
    * real time.
    *
    * This will advance in millisecond increments only.
    *
    * \param elapsed Time to advance the simulation in seconds.
    */
    void Update(double elapsed);

    /**
     * Load all images from files
     *
     * This is only used for Test, since it is automatically
     * called when the window is created when not in test
     */
    void Load();

    /// \cond

	//
	// Getters
	//

    int GetWidth();
    int GetHeight();

	/** Get the minion position
	*
	* <1 means to the left of the short, >4 is to the right of inspection
	* The positions of the stages are 1, 2, 3, and 4
	* \return Position relative to the stages */
	double GetMinionPosition() { return mMinionPosition; }

	/// Get the current Minion
	/// \return Pointer to current Minion
	std::shared_ptr<CMinion> GetMinion() { return mMinion; }

	//
	// Activities
	//

	/** Enable the Next Minion button
	 * \param enable true to enable */
	void EnableButtonNext(bool enable) { mButtonNext.SetEnabled(enable); }


	/** Enable the Advance button
	* \param enable true to enable */
	void EnableButtonAdvance(bool enable) { mButtonAdvance.SetEnabled(enable); }

	/** Enable the Shower button
	* \param enable true to enable */
	void EnableButtonShower(bool enable) { mButtonShower.SetEnabled(enable); }

	/** Enable the Wardrobe button
	 * \param enable true to enable */
	void EnableButtonWardrobe(bool enable) { mButtonWardrobe.SetEnabled(enable); }

	/** Enable the Innoculate button
	* \param enable true to enable */
	void EnableButtonInnoculate(bool enable) { mButtonInnoculate.SetEnabled(enable); }

	/** Enable the Inspect button
	* \param enable true to enable */
	void EnableButtonInspect(bool enable) { mButtonInspect.SetEnabled(enable); }

	/** Enable showering
	* \param enable true to enable */
	void SetShower(bool enable);

	/** Apply a wardrobe item to the minion
	* \param item Wardrobe item to apply */
	void DressMinion(CWorkshopController::Wardrobe item);

    /**
    * Set the speed of the conveyor belt
    *
    * \param speed Speed to set. Positive values move the bag
    * to the right, negative values to the left. Values should
    * range from -1 to 1 (max left speed to max right speed)
    */
    void SetConveyorSpeed(double speed);

	/**
	 * Add the next Minion to the conveyor belt end
	 * Position is set to -1, speed is set to 0
	 */
	void NextMinion();

	/// Start the innoculation process
	void Innoculate();

	/// Kill the minion dead
	void KillMinion();

	/// Indicate that we have passed inspection
	void PassedInspection();

	/// Strip one item of wardrobe from the Minion
	void Strip();

    void LoadImage(std::shared_ptr<Gdiplus::Bitmap> &bitmap, const wchar_t *name);

	//
	// Testing support
	//
	CButton2 *GetButtonNext() { return &mButtonNext; }
	CButton2 *GetButtonAdvance() { return &mButtonAdvance; }
	CButton2 *GetButtonShower() { return &mButtonShower; }
	CButtonWardrobe *GetButtonWardrobe() { return &mButtonWardrobe; }
	CButton2 *GetButtonInnoculate() { return &mButtonInnoculate; }
	CButton2 *GetButtonInspect() { return &mButtonInspect; }

	bool IsShower() const { return mShower; }
	void ForceEyes(int eyes) { mForceEyes = eyes; }
	bool IsStripping() { return mStrippingItem != nullptr; }

private:
    DECLARE_DYNAMIC(CWorkshopWnd)

protected:

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


private:
    void Draw(Gdiplus::Graphics *graphics, std::shared_ptr<Gdiplus::Bitmap> &bitmap, int x, int y);
    void DrawButtons(Gdiplus::Graphics *graphics);
	void ButtonsUp();

    void TimeManagement();
    void UpdateTimeslice();

	double mScale = 2.0;				///< Display scale

	bool mLButtonDown = false;			///< Left button is down?

	//
	// Buttons
	//
	CButton2 mButtonNext;				///< Next minion button
	CButton2 mButtonAdvance;			///< Advance button
	CButton2 mButtonShower;				///< Shower button
	CButtonWardrobe mButtonWardrobe;	///< Wardrobe button
	CButton2 mButtonInnoculate;			///< Innoculate button
	CButton2 mButtonInspect;			///< Inspect button

	CNeedle mNeedle;					///< Scary needle

    bool mFirstDraw = true;				///< True for the first time we draw

	CMinionFactory mMinionFactory;		///< The Minion generating factory

    // A controller for this workshop
    std::shared_ptr<CWorkshopController> mController;

    /// Manage the simulation timing
    CTimeManagement mTimeManagement;

    double   mTime = 0;             ///< Local time

	/// Background image
    std::shared_ptr<Gdiplus::Bitmap>  mBackgroundImage;

	/// Shower image
	std::shared_ptr<Gdiplus::Bitmap>  mShowerImage;

	//
	// Conveyor belt and moving Minion
	//
	double mConveyorSpeed = 0;		///< Belt speed in stations per second
	double mMinionPosition = -1;		///< Current minion position in stations
	std::shared_ptr<CMinion> mMinion;	///< Active minion

	std::shared_ptr<CWardrobeItem> mDressingItem;	///< Flying on wardrobe item
	std::shared_ptr<CWardrobeItem> mStrippingItem;	///< Flying off wardrobe item

	/// Shower active?
	bool mShower = false;

	/// If none-zero, this will force a Minion create with a specified number of eyes.
	int mForceEyes = 0;

    /// \endcond
};


