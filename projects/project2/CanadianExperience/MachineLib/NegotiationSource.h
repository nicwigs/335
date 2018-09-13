/**
 * \file NegotiationSource.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a negotiation source
 *
 * A rod owns this, rod gives energy and negotiates end point
 */

#pragma once
#include "Source.h"
#include <vector>
class CNegotiationSink;
class CRod;
/**
 * Class the describes a negotiation source
 */
class CNegotiationSource : public CSource
{
public:
	CNegotiationSource();
	virtual ~CNegotiationSource();

	/** \brief Copy constructor disabled */
	CNegotiationSource(const CNegotiationSource &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CNegotiationSource &) = delete;

	void AddSink(CNegotiationSink* sink);
	void Update(CRod * rod);

private:
	std::vector<CNegotiationSink*> mSinks; ///< The sinks of this source

};

