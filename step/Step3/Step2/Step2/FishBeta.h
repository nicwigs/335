/**
 * \file FishBeta.h
 *
 * \author Nic Wiggins
 *
 * Class than describes a beta fish
 */

#pragma once

#include <memory>

#include "Fish.h"


/**
 * Implements a beta fish
 */
class CFishBeta : public CFish
{
public:	 
	
	CFishBeta(CAquarium * aquarium);
	virtual ~CFishBeta();

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

};

