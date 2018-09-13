/**
 * \file ActualMachine.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include "ActualMachine.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"
/**
 * Constructor.
 */
CActualMachine::CActualMachine()
{
	//Default to Machine 1
	SetMachineNumber(1);
}
/**
 * Destructor. 
 */
CActualMachine::~CActualMachine()
{
}
/**
* Set the position for the root of the machine
* \param x X location (pixels)
* \param y Y location (pixels)
*/
void CActualMachine::SetLocation(int x, int y)
{
	mPosition = Gdiplus::Point(x, y);
}
/**
* Draw the machine at the currently specified location
* \param graphics GDI+ Graphics object
*/
void CActualMachine::DrawMachine(Gdiplus::Graphics * graphics)
{
	mWorkingMachine->DrawMachine(graphics, mPosition);
}
/**
* Set the current machine animation frame
* \param frame Frame number
*/
void CActualMachine::SetMachineFrame(int frame)
{
	mCurrentTime = (double)frame / mFrameRate;
	mWorkingMachine->SetMachineTime(mCurrentTime); //updates time of machine
}
/**
* Set the expected frame rate in frames per second
* \param rate Frame rate in frames per second
*/
void CActualMachine::SetFrameRate(double rate)
{
	mFrameRate = rate;
}
/**
* Set  the bend angle
* \param speed Speed from 0 to 1, where 1 is full speed
*/
void CActualMachine::SetSpeed(double speed)
{
	mWorkingMachine->SetSpeed(speed);
}
/**
* Set the machine number
* \param machine An integer number. Each number makes a different machine
*/
void CActualMachine::SetMachineNumber(int machine)
{
	if (machine == 1)
	{
		// Use a factory to create the machine object
		CMachineFactory1 factory;
		mWorkingMachine = factory.CreateMachine();
	}
	else //machine == 2
	{
		// Use a factory to create the machine object
		CMachineFactory2 factory;
		mWorkingMachine = factory.CreateMachine();
	}
}
/**
* Get the current machine number
* \return Machine number integer
*/
int CActualMachine::GetMachineNumber()
{
	return mWorkingMachine->GetMachineNumber();
}