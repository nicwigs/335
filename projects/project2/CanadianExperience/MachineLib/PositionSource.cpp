/**
 * \file PositionSource.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include "PositionSource.h"
#include "PositionSink.h"
/**
 * Constructor. 
 */
CPositionSource::CPositionSource()
{
}
/**
 * Destructor. 
 */
CPositionSource::~CPositionSource()
{
}
/**
* Add sink to source
* \param sink The sink to add
*/
void CPositionSource::AddSink(CPositionSink * sink)
{
	mSinks.push_back(sink);
}
/**
* Sets position from source
* \param point Position from source
*/
void CPositionSource::SetPosition(Gdiplus::Point point)
{
	mPosition = point;
}
/**
* Updates source, calls sink
* \param point New Position
*/
void CPositionSource::Update(Gdiplus::Point point)
{
	SetPosition(point);
	for (auto sink : mSinks)
	{
		sink->Update(point);
	}
}
