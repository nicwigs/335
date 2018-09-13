/**
 * \file Sink.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Sink.h"


/**
 * Constructor. 
 */
CSink::CSink()
{
}


/**
 * Destructor. 
 */
CSink::~CSink()
{
}

/**
 * Gets pointer to component
 * \returns component Pointer to component
 */
CComponent* CSink::GetComponent()
{
	return mComponent;
}

/**
 * Sets component
 * \param component Component that owns this sink
 */
void CSink::SetComponent(CComponent* component)
{
	mComponent = component;
}
