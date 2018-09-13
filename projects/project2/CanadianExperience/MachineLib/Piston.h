/**
 * \file Piston.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a piston
 *
 * Driven by rod, moves linear up and down. 
 */

#pragma once
#include "Negotiator.h"
#include "NegotiationSink.h"

/**
 * Class that describes a piston
 */
class CPiston : public CNegotiator
{
public:
	CPiston(double height, double width);
	virtual ~CPiston();

	/** \brief Default constructor disabled */
	CPiston() = delete;
	/** \brief Copy constructor disabled */
	CPiston(const CPiston &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPiston &) = delete;

	CNegotiationSink * GetSink();
	virtual void Negotiate(CRod *rod) override;


private:
	CNegotiationSink mSink; ///< Gets energy from
};

