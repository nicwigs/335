/**
 * \file Farm.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Farm.h"

/**
 * Constructor.
 */
CFarm::CFarm()
{
}

/**
 * Destructor. 
 */
CFarm::~CFarm()
{
	// Iterate over all of the animals, destroying 
	// each one.
	for (auto animal : mInventory)
	{
		delete animal;
	}

	// And clear the list
	mInventory.clear();
}

/** Add an animal to the farm inventory.
*
* \param animal An animal to add to the inventory
*/
void CFarm::AddAnimal(CAnimal *animal)
{
	mInventory.push_back(animal);
}

/**
* Display the farm inventory.
*/
void CFarm::DisplayInventory()
{
	for (auto animal : mInventory)
	{
		animal->DisplayAnimal();
	}
}


/**
 * Counts the total number of eyes on the farm.
 *
 * \returns eyeCount the total number of eyes on the farm
 */
int CFarm::CountTheEyes()
{
	int eyeCount = 0;
	for (auto animal : mInventory)
	{
		eyeCount += animal->NumEyes();
	}
	return eyeCount;
}