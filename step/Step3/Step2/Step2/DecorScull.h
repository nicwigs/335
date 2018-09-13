/**
* \file DecorScull.h
*
* \author Nic Wiggins
*
* Class than describes a scull used in decor
*/

#pragma once

#include <memory>
#include "Item.h"


/**
* Implements a decor scull
*/
class CDecorScull : public CItem
{
public:

	CDecorScull(CAquarium * aquarium);
	virtual ~CDecorScull();

	/// Default constructor (disabled)
	CDecorScull() = delete;

	/// Copy constructor (disabled)
	CDecorScull(const CDecorScull &) = delete;


	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

};