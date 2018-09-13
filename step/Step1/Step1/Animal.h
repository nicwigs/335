/**
 * \file Animal.h
 *
 * \author Nic Wiggins
 *
 * Class that discribes an animal.
 *
 *Holds methods that are common to all animals such as display 
 */

#pragma once

/**
 * Class that holds methods pertaining to animals
 */
class CAnimal
{
public:
	CAnimal();
	virtual ~CAnimal();

	/** Display an animal. */
	virtual void DisplayAnimal() {}
	virtual int NumEyes();
};

