/**
 * \file HaroldFactory.h
 *
 * \author Nic Wiggins
 *
 * Factory class that builds the Harold character
 */

#pragma once

#include "ActorFactory.h"
#include "Actor.h"

 /**
 * Factory class that builds the Harold character
 */
class CHaroldFactory : public CActorFactory
{
public:
	CHaroldFactory();
	virtual ~CHaroldFactory();

	std::shared_ptr<CActor> Create() override;
};

