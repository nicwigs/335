/**
 * \file ActorFactory.h
 *
 * \author Nic Wiggins
 *
 * Abstract base class for actor factories.
 */

#pragma once

#include <memory>
class CActor;

 /**
 * Abstract base class for actor factories.
 */
class CActorFactory
{
public:
	CActorFactory();
	virtual ~CActorFactory();

	/**
	* Creates the factory.
	*\return pointer to actor
	*/
	virtual std::shared_ptr<CActor> Create() = 0;
};

