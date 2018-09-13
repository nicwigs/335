/**
 * \file Gear.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a gear.
 *
 * They can be different sizes and different teeth
 */

#pragma once
#include "Component.h"
#include "RotationSource.h"
#include "RotationSink.h"
/**
 * Class that describes a gear. 
 */
class CGear : public CComponent
{
public:
	CGear(double radius, int teeth);
	virtual ~CGear();

	/** \brief Default constructor disabled */
	CGear() = delete;
	/** \brief Copy constructor disabled */
	CGear(const CGear &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CGear &) = delete;

	CRotationSource * GetSource();
	CRotationSink * GetSink();
	virtual void SetRotation(double rotation) override;

private:
	int mTeeth = 0; ///< Number of teeth
	double mRadius = 0.0; ///< Radius of gear. 
	CRotationSource mSource; ///< Give energy through rotation
	CRotationSink mSink; ///< Gets energy from rotation. 
};

