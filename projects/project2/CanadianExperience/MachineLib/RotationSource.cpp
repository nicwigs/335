/**
 * \file RotationSource.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "RotationSource.h"
#include "RotationSink.h"

/**
 * Constructor. 
 */
CRotationSource::CRotationSource()
{
}

/**
 * Destructor. 
 */
CRotationSource::~CRotationSource()
{
}

/**
 * Add sink to source
 * \param sink The sink to add
 */
void CRotationSource::AddSink(CRotationSink*sink)
{
	mSinks.push_back(sink);
}

/**
 * Sets rotation from source
 * \param rot Rotation from source
 */
void CRotationSource::SetRotation(double rot)
{
	mRotation = rot;
}

/**
 * Updates source, calls sink
 * \param rot New Rotation
 */
void CRotationSource::Update(double rot)
{
	SetRotation(rot);
	for (auto sink : mSinks)
	{
		sink->Update(rot);
	}
}

