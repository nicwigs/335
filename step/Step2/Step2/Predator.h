/**
* \file Predator.h
*
* \author Nic Wiggins
*
* Class that describes a predator
* in our aquarium
*/

#pragma once

#include "Item.h"


/**
 * Class that describes a predator 
 */
class CPredator : public CItem
{
public:
	/// Default constructor (disabled)
	CPredator() = delete;

	/// Copy constructor (disabled)
	CPredator(const CPredator &) = delete;

	virtual ~CPredator();

};

