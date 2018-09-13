/**
 * \file Negotiator.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a component that negotiates
 */

#pragma once
#include "Component.h"
#include "Rod.h"
/**
 * Class that describes a component that negotiates. 
 */
class CNegotiator:public CComponent
{
public:
	CNegotiator();
	virtual ~CNegotiator();

	/** Negotiates a rod end
	*\param rod Pointer to rod negotiating with*/
	virtual void Negotiate(CRod *rod) = 0;
};

