/**
 * \file Shape.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include "Shape.h"

/**
 * Constructor. 
 */
CShape::CShape()
{
	mSink.SetComponent(this);
}

/**
 * Destructor. 
 */
CShape::~CShape()
{
}

/**
 * Get the sink of the shape
 * \returns mSink pointer to sink
 */
CRotationSink * CShape::GetSink()
{
	return &mSink;
}
