/**
 * \file Source.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Source.h"


/**
 * Constructor. 
 */
CSource::CSource()
{
}


/**
 * Destructor. 
 */
CSource::~CSource()
{
}

/**
* Gets pointer to component
* \returns component Pointer to component
*/
CComponent* CSource::GetComponent()
{
	return mComponent;
}

/**
* Sets component
* \param component Component that owns this sink
*/
void CSource::SetComponent(CComponent* component)
{
	mComponent = component;
}
