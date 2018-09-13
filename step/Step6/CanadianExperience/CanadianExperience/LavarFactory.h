/**
 * \file LavarFactory.h
 *
 * \author Nic Wiggins
 *
 * Factory class that builds the LaVar Ball character
 */

#pragma once

#include "ActorFactory.h"
#include "Actor.h"

 /**
 * Factory class that builds the LaVar Ball character
 */
class CLavarFactory : public CActorFactory
{
public:
	CLavarFactory();
	virtual ~CLavarFactory();

	std::shared_ptr<CActor> Create() override;
};

