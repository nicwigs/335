/**
 * \file Motor.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a motor - what runs a machine
 * Constists of 2 shapes. 
 * Owns a shaft - which spins
 */

#pragma once
#include "Component.h"
#include "RotationSource.h"
/**
 * Class that describes a motor - to run a machine. 
 */
class CMotor : public CComponent
{
public:
	CMotor();
	virtual ~CMotor();

	/** \brief Copy constructor disabled */
	CMotor(const CMotor &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CMotor &) = delete;

	virtual void SetSpeed(double speed);
	virtual void Draw(Gdiplus::Graphics *graphics, Gdiplus::Point position) override;
	void SetShaft(std::shared_ptr<CPolygon> shaft);
	void Update(double elapsed);
	CRotationSource * GetSource();

private:	
	double mSpeed; ///< Speed of motor
	std::shared_ptr<CPolygon> mShaft; ///< Pointer to shaft of machine
	CRotationSource mSource; ///< Give energy through rotation 
};

