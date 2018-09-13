/**
 * \file RotationSink.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a component connection
 * that takes energy of rotation 
 */

#pragma once
#include "Sink.h"
#include "RotationSource.h"
/**
 * Class that describes a rotation sink
 */
class CRotationSink : public CSink
{
public:
	CRotationSink();
	virtual ~CRotationSink();

	/** \brief Copy constructor disabled */
	CRotationSink(const CRotationSink &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CRotationSink &) = delete;

	void SetOffset(double offset);
	void SetSpeedRatio(double ratio);
	void Update(double rotation);

private:
	double mOffset = 0.0; ///< Offset for meshing
	double mSpeedRatio = 1.0; ///< Gear difference negative driving/driven

};

