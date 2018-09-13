/**
 * \file RotationSink.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include "RotationSink.h"
/**
 * Constructor. 
 */
CRotationSink::CRotationSink()
{
}

/**
 * Destructor. 
 */
CRotationSink::~CRotationSink()
{
}

/**
 * Allows to line up teeth of gear
 * \param offset Amount to offset the rotation
 */
void CRotationSink::SetOffset(double offset)
{
	mOffset = offset;
}

/**
 * Speed ratio is defined driving gear teeth/ driven gear teeth
 * This is set in the factory. 
 * \param ratio Ratio of teeth. 
 */
void CRotationSink::SetSpeedRatio(double ratio)
{
	mSpeedRatio = ratio;
}

/**
 * Updates rotation
 * \param rotation Rotation of sink
 */
void CRotationSink::Update(double rotation)
{
	GetComponent()->SetRotation(rotation*mSpeedRatio+mOffset);
}
