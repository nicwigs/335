/**
 * \file PositionSink.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a position sink
 *
 * Who owns this gets energy via a position change
 */

#pragma once
#include "Sink.h"
#include "RotationSource.h"
/**
 * Class that describes a position sink. 
 */
class CPositionSink :public CSink
{
public:
	CPositionSink();
	virtual ~CPositionSink();

	/** \brief Copy constructor disabled */
	CPositionSink(const CPositionSink &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPositionSink &) = delete;

	void Update(Gdiplus::Point pos);
};

