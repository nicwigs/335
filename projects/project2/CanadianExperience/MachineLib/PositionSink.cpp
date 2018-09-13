/**
 * \file PositionSink.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "PositionSink.h"

/**
 * Constructor.
 */
CPositionSink::CPositionSink()
{
}

/**
 * Destructor. 
 */
CPositionSink::~CPositionSink()
{
}
/**
* Updates position
* \param pos Position of sink
*/
void CPositionSink::Update(Gdiplus::Point pos)
{
	GetComponent()->SetPosition(pos.X, pos.Y);
}
