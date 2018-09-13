/**
 * \file WorkingMachine.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a working machine
 * Owned by actualMachine
 */

#pragma once
#include <vector>
#include "Component.h"
#include "Motor.h"
/**
 * Class that describes a working machine. 
 */
class CWorkingMachine
{
public:
	CWorkingMachine(int number);
	virtual ~CWorkingMachine();

	/** \brief Default constructor disabled */
	CWorkingMachine() = delete;
	/** \brief Copy constructor disabled */
	CWorkingMachine(const CWorkingMachine &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CWorkingMachine &) = delete;

	virtual void DrawMachine(Gdiplus::Graphics *graphics,Gdiplus::Point point);
	virtual void SetMachineTime(double elapsed);
	virtual void SetSpeed(double speed);
	virtual int GetMachineNumber();
	void AddComponent(std::shared_ptr<CComponent> component);
	void SetMotor(std::shared_ptr<CMotor> motor);

private:
	///Machine Number
	int mNumber = 1;
	/// The components in drawing order
	std::vector<std::shared_ptr<CComponent>> mComponentsInOrder;
	/// The motor of the machine
	std::shared_ptr<CMotor> mMotor;
};

