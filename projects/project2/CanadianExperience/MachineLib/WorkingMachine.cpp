/**
 * \file WorkingMachine.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include "WorkingMachine.h"

/**
 * Constructor
 * \param number Number of machine.
 */
CWorkingMachine::CWorkingMachine(int number)
{
	mNumber = number;
}

/**
 * Destructor. 
 */
CWorkingMachine::~CWorkingMachine()
{
}

/**
* Draw the machine at the currently specified location
* \param graphics GDI+ Graphics object
 * \param point Position of the machine
 */
void CWorkingMachine::DrawMachine(Gdiplus::Graphics * graphics, Gdiplus::Point point)
{
	for (auto component : mComponentsInOrder)
	{
		component->Draw(graphics, point); //this is position of machine.
	}
}

/**
* Set the current machine time
* \param elapsed Time elapsed since beginning 
*/
void CWorkingMachine::SetMachineTime(double elapsed)
{
	mMotor->Update(elapsed);
}

/**
* Set  the bend angle
* \param speed Speed from 0 to 1, where 1 is full speed
*/
void CWorkingMachine::SetSpeed(double speed)
{
	mMotor->SetSpeed(speed);
}

/**
* Get the current machine number
* \return Machine number integer
*/
int CWorkingMachine::GetMachineNumber()
{
	return mNumber;
}
/**
* Add a component to this machine
* \param component The compnent to add
*/
void CWorkingMachine::AddComponent(std::shared_ptr<CComponent> component)
{
	mComponentsInOrder.push_back(component);
	component->SetMachine(this);
}

/** Set the motor for the machine
* \param motor Pointer to motor */
void CWorkingMachine::SetMotor(std::shared_ptr<CMotor> motor)
{
	mMotor = motor;
}
