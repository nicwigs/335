/**
* \file FishNemo.h
*
* \author Nic Wiggins
*
* Class than describes a Nemo fish
*/

#pragma once

#include <memory>


#include "Fish.h"


/**
* Implements a Nemo fish
*/
class CFishNemo : public CFish
{
public:

	CFishNemo(CAquarium * aquarium);
	virtual ~CFishNemo();

	/// Default constructor (disabled)
	CFishNemo() = delete;

	/// Copy constructor (disabled)
	CFishNemo(const CFishNemo &) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	
};
