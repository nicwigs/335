/**
 * \file Sink.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a sink
 * Sink is something that recieves energy in the machine
 */

#pragma once
#include <memory>
#include "Component.h"
/**
 * Class that describes an energy sink.
 */
class CSink
{
public:
	CSink();
	virtual ~CSink();

	/** \brief Copy constructor disabled */
	CSink(const CSink &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CSink &) = delete;

	CComponent* GetComponent();
	virtual void SetComponent(CComponent* component);

private:
	CComponent * mComponent = nullptr; ///< component that owns this sink
};

