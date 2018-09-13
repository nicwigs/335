/**
 * \file Rod.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a rod. 
 */

#pragma once
#include "Component.h"
#include "PositionSink.h"
#include "NegotiationSource.h"
/**
 * Class that describes a rod for a machine. 
 */
class CRod : public CComponent
{
public:
	CRod(Gdiplus::Point a, Gdiplus::Point b);
	virtual ~CRod();

	/** \brief Default constructor disabled */
	CRod() = delete;
	/** \brief Copy constructor disabled */
	CRod(const CRod &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CRod &) = delete;

	CNegotiationSource * GetSource();
	CPositionSink * GetSink();
	double GetLength();
	virtual void SetPosition(int x, int y) override;

private:
	double mLength = 0.0; ///< Length of arm
	CNegotiationSource mSource; ///<Rod gives energy through this
	CPositionSink mSink; ///< Arm gets energy from position 

};

