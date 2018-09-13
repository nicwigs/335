/**
 * \file Source.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a source
 * Source provides energy to another component. 
 */

#pragma once
#include <memory>
class CComponent;
/**
 * Class that describes an energy source. 
 */
class CSource
{
public:
	CSource();
	virtual ~CSource();

	/** \brief Copy constructor disabled */
	CSource(const CSource &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CSource &) = delete;

	CComponent* GetComponent();
	virtual void SetComponent(CComponent* component);

private:
	CComponent * mComponent = nullptr; ///< Component that owns this source

};

