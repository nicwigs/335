/**
* \file FishDory.h
*
* \author Nic Wiggins
*
* Class than describes a Dory fish
*/

#pragma once

#include <memory>

#include "Fish.h"

/**
* Implements a Dory fish
*/
class CFishDory : public CFish
{
public:

	CFishDory(CAquarium * aquarium);
	virtual ~CFishDory();

	/// Default constructor (disabled)
	CFishDory() = delete;

	/// Copy constructor (disabled)
	CFishDory(const CFishDory &) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
};
