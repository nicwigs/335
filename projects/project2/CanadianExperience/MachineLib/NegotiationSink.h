/**
 * \file NegotiationSink.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a Negotiation Sink
 *
 * A piston or lever own this
 */

#pragma once
#include "Sink.h"
class CNegotiator;
class CRod;
/**
 * Class that describes a negotiation sink
 */
class CNegotiationSink : public CSink
{
public:
	CNegotiationSink();
	virtual ~CNegotiationSink();

	/** \brief Copy constructor disabled */
	CNegotiationSink(const CNegotiationSink &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CNegotiationSink &) = delete;

	virtual void SetNegotiator(CNegotiator * negotiator);
	void Update(CRod * rod);

private:
	CNegotiator * mNegotiator = nullptr; ///< who owns this sink. Gets energy
};

