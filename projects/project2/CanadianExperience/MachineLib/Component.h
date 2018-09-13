/**
 * \file Component.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a component of the machine.
 *
 * A machine is made out of multiple components. 
 */

#pragma once
#include "Polygon.h"
class CWorkingMachine;
/**
 * Class that describes a component of a machine. 
 */
class CComponent : public CPolygon
{
public:
	CComponent();
	virtual ~CComponent();

	/** \brief Copy constructor disabled */
	CComponent(const CComponent &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CComponent &) = delete;

	virtual void SetPosition(int x, int y);
	virtual Gdiplus::Point GetPosition();
	virtual void Draw(Gdiplus::Graphics *graphics, Gdiplus::Point position);
	virtual void SetMachine(CWorkingMachine * machine);
	int GetX();
	int GetY();

private:
	///Position of component
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
	///The working machine using this component
	CWorkingMachine *mWorkingMachine = nullptr;
};

