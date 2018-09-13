/**
 * \file RotationSource.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a source rotation
 * Owns this gives energy via rotation. 
 */

#pragma once
#include "Source.h"
#include <vector>
class CRotationSink;
/**
 * Class that describes a Rotation Source
 */
class CRotationSource : public CSource
{
public:
	CRotationSource();
	virtual ~CRotationSource();

	/** \brief Copy constructor disabled */
	CRotationSource(const CRotationSource &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CRotationSource &) = delete;

	void AddSink(CRotationSink* sink);
	void SetRotation(double rot);
	void Update(double rot);

private:
	/// The sinks of this source. 
	std::vector<CRotationSink*> mSinks;
	///rotation of source
	double mRotation = 0;
};

