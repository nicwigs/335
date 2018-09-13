/**
 * \file NegotiationSource.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "NegotiationSource.h"
#include "Rod.h"
#include "NegotiationSink.h"

/**
 * Constructor.
 */
CNegotiationSource::CNegotiationSource()
{
}

/**
 * Destructor. 
 */
CNegotiationSource::~CNegotiationSource()
{
}
/**
* Add sink to source
* \param sink The sink to add
*/
void CNegotiationSource::AddSink(CNegotiationSink * sink)
{
	mSinks.push_back(sink);
}

/**
 * Updates sinks
 * \param rod Pointer to rod that is driving
 */
void CNegotiationSource::Update(CRod * rod)
{
	for (auto sink : mSinks)
	{
		sink->Update(rod);
	}
}
