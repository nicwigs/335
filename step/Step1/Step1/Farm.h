/**
 * \file Farm.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a farm.
 *
 * This class holds a collection of animals that make
 * up the inventory of a farm.
 */

#pragma once
#include <vector>
#include "Cow.h"

/**
 * Class that describes a farm.
 *
 * Holds a collection of animals that make up the farm 
 * inventory.
 */
class CFarm
{
public:
	CFarm();
	virtual ~CFarm();
	void AddAnimal(CAnimal *animal);
	void DisplayInventory();
	int CountTheEyes();

private:
	/// A list with the inventory of all animals on the farm
	std::vector<CAnimal *> mInventory;

};

