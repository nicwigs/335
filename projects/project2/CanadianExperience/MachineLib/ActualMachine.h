/**
 * \file ActualMachine.h
 *
 * \author Nic Wiggins
 *
 * Class that describes an actual machine
 * Extends machine class
 */
#pragma once
#include "Machine.h"
#include "WorkingMachine.h"
/**
 * Class that describes an actual machine. 
 */
class CActualMachine : public CMachine
{
public:
	CActualMachine();
	virtual ~CActualMachine();

	/** \brief Copy constructor disabled */
	CActualMachine(const CActualMachine &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CActualMachine &) = delete;

	virtual void SetLocation(int x, int y) override;
	virtual void DrawMachine(Gdiplus::Graphics *graphics) override;
	virtual void SetMachineFrame(int frame) override;
	virtual void SetFrameRate(double rate) override;
	virtual void SetSpeed(double speed) override;
	virtual void SetMachineNumber(int machine) override;
	virtual int GetMachineNumber() override;

private:
	/// Frame Rate of machine
	double mFrameRate = 30;
	/// Current time of machine
	double mCurrentTime = 0.0;
	///Position of machine
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
	/// Pointer to working machine
	std::shared_ptr<CWorkingMachine> mWorkingMachine;
};

