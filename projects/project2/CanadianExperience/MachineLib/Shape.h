/**
 * \file Shape.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a shape for a machine. 
 */

#pragma once
#include "Component.h"
#include "RotationSink.h"
/**
 * Class that describes a shape.
 */
class CShape : public CComponent
{
public:
	CShape();
	virtual ~CShape();

	/** \brief Copy constructor disabled */
	CShape(const CShape &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CShape &) = delete;

	CRotationSink * GetSink();

private:
	///Sink
	CRotationSink mSink;
};

