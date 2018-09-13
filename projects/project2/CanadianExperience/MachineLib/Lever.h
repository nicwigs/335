/**
 * \file Lever.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a lever 
 *
 * Pull down on one side, pushes up on the other. 
 */

#pragma once
#include "Negotiator.h"
#include "NegotiationSink.h"
#include "RotationSource.h"
#include "PositionSource.h"

/**
 * Class that describes a lever. 
 */
class CLever : public CNegotiator
{
public:
	CLever(double length);
	virtual ~CLever();

	/** \brief Default constructor disabled */
	CLever() = delete;
	/** \brief Copy constructor disabled */
	CLever(const CLever &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CLever &) = delete;

	CRotationSource * GetRotationSource();
	CPositionSource * GetPositionSource();
	CNegotiationSink* GetSink();
	Gdiplus::Point GetDrivePoint();
	Gdiplus::Point GetPushPoint();
	void SetDriveLength(double x);
	virtual void Negotiate(CRod *rod) override;

private:
	double mLength = 0.0; ///< Length of lever
	double mDriveLength; ///< length from pivot to joint (-) is left
	CRotationSource mRotationSource; ///< Give energy through rotation
	CPositionSource mPositionSource; ///< Give energy through position
	CNegotiationSink mSink; ///< gets energy from

};

