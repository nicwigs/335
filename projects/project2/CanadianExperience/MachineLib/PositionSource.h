/**
 * \file PositionSource.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a position source
 *
 * Who owns this gives energy via a position change
 */

#pragma once
#include "Source.h"
#include <vector>
class CPositionSink;
/**
 * Class that describes a position source
 */
class CPositionSource : public CSource
{
public:
	CPositionSource();
	virtual ~CPositionSource();

	/** \brief Copy constructor disabled */
	CPositionSource(const CPositionSource &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPositionSource &) = delete;

	void AddSink(CPositionSink* sink);
	void SetPosition(Gdiplus::Point point);
	void Update(Gdiplus::Point point);

private:
	/// The sinks of this source. 
	std::vector<CPositionSink*> mSinks;
	///Position of source
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
};

