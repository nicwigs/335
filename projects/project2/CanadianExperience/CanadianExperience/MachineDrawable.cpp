/**
 * \file MachineDrawable.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "MachineDrawable.h"
#include "Machine.h"
#include "MachineFactory.h"
#include "Timeline.h"
#include "MachineDlg.h"
#include <sstream>

using namespace std;

/**
 * Constructor. 
 * \param name The drawable name
 */
CMachineDrawable::CMachineDrawable(const std::wstring &name) : CDrawable(name)
{
	CMachineFactory factory;
	mMachine = factory.CreateMachine();
}

/**
 * Destructor. 
 */
CMachineDrawable::~CMachineDrawable()
{
}

/**
* Draw the machine at the currently specified location
* \param graphics GDI+ Graphics object
*/
void CMachineDrawable::Draw(Gdiplus::Graphics * graphics)
{
	float scale = 0.75f;
	auto save = graphics->Save();
	graphics->TranslateTransform((float)mPlacedPosition.X,
		(float)mPlacedPosition.Y);
	graphics->ScaleTransform(scale, scale);
	mMachine->DrawMachine(graphics);
	graphics->Restore(save);
	
}

/**
 * Test to see if we have been clicked on by the mouse
 * \param pos Position to test
 * \returns false Machine not clickable, must override since pure virtual
 */
bool CMachineDrawable::HitTest(Gdiplus::Point pos)
{
	return false;
}

/**
 * Call mMachine set location
 * \param offset Actual position in drawing
 * \param rotate Rotate of entire machine
 */
void CMachineDrawable::Place(Gdiplus::Point offset, double rotate)
{
	CDrawable::Place(offset, rotate);
	mMachine->SetLocation(mPlacedPosition.X, mPlacedPosition.Y);
}

/**
 * Sets seed of machine
 * \param number Number of machine
 */
void CMachineDrawable::SetMachineNumber(int number)
{
	mMachine->SetMachineNumber(number);
}

/**
 * Draws dialog box to change machine number
 */
void CMachineDrawable::ShowMachineSeedDialogBox()
{
	CMachineDlg dlg(mMachine);
	if (dlg.DoModal() == IDOK)
	{
		//Machine number has been set.
	}
}

/**
 * Sets machine frame rate
 * \param rate New frame rate
 */
void CMachineDrawable::SetFrameRate(double rate)
{
	mMachine->SetFrameRate(rate);
}

/**
 * Sets time when the machine starts running
 * \param frame The frame it starts at
 */
void CMachineDrawable::SetMachineStartFrame(int frame)
{
	mStartFrame = frame;
}

/**
 * Gets when machine starts running
 * \returns Start frame
 */
int CMachineDrawable::GetStartFrame()
{
	return mStartFrame;
}

/**
 * Get the current channel from the animation system
 * Called whenever system updates, override to send current frame to machine
 */
void CMachineDrawable::GetKeyframe()
{
	CDrawable::GetKeyframe();

	int currentFrame = GetAngleChannel()->GetTimeline()->GetCurrentFrame();

	if (currentFrame >= mStartFrame)
	{
		mMachine->SetMachineFrame(currentFrame - mStartFrame);
	}
	else
	{
		mMachine->SetMachineFrame(0);
	}
}

/**
 * Save the timeline animation to a file
 * \param root The XML node to save to
 * \param name Name of machine "A" or "B"
 */
void CMachineDrawable::Save(std::shared_ptr<xmlnode::CXmlNode> root, const std::wstring &name)
{
	wstringstream number;
	number << L"machineNumber" << name;
	wstringstream frame;
	frame << L"startFrame" << name;

	root->SetAttribute(number.str().c_str(), mMachine->GetMachineNumber());
	root->SetAttribute(frame.str().c_str(), mStartFrame);
}
/**
* Load the timeline animation to a file
* \param root The XML node to load to
* \param name Name of machine "A" or "B"
*/
void CMachineDrawable::Load(std::shared_ptr<xmlnode::CXmlNode> root, const std::wstring &name)
{
	wstringstream number;
	number << L"machineNumber" << name;
	wstringstream frame;
	frame << L"startFrame" << name;
	
	mMachine->SetMachineNumber(root->GetAttributeIntValue(number.str().c_str(), 1));
	mStartFrame = root->GetAttributeIntValue(frame.str().c_str(), 0);
}
