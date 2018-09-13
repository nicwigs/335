/**
 * \file NegotiationSink.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "NegotiationSink.h"
#include "Negotiator.h"

/**
 * Constructor. 
 */
CNegotiationSink::CNegotiationSink()
{
}


/**
 * Destructor. 
 */
CNegotiationSink::~CNegotiationSink()
{
}

/**
 * Sets negotiator. 
 * \param negotiator Component that owns this sink
 */
void CNegotiationSink::SetNegotiator(CNegotiator * negotiator)
{
	mNegotiator = negotiator;
	SetComponent(negotiator);
}

/**
 * Gives negotiator a pointer to the rod that is giving it energy
 * \param rod Pointer to the rod thats driving it. 
 */
void CNegotiationSink::Update(CRod * rod)
{
	mNegotiator->Negotiate(rod);
}
