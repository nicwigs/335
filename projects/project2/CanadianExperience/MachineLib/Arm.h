/**
 * \file Arm.h
 *
 * \author Nic Wiggins
 *
 * Class that describes an arm
 *
 * Arm attaches to a rotationg component and spins
 * Main purpose to drive a rod. 
 */

#pragma once
#include "Component.h"
#include "PositionSource.h"
#include "RotationSink.h"
/**
 * Class that describes an arm
 */
class CArm : public CComponent
{
public:
	CArm(double length);
	virtual ~CArm();

	/** \brief Default constructor disabled */
	CArm() = delete;
	/** \brief Copy constructor disabled */
	CArm(const CArm &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CArm &) = delete;

	CPositionSource * GetSource();
	CRotationSink * GetSink();
	Gdiplus::Point GetEndPoint();
	virtual void SetRotation(double rotation) override;

private:
	double mLength = 0.0; ///< Length of arm
	CPositionSource mSource; ///< Gives energy through position
	CRotationSink mSink; ///<Gets energy from


};

