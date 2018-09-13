/**
 * \file Animal.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "Animal.h"

///Standard number of eyes of an animal
const int StandardEyeCount = 2;

/**
 * Constructor
 */
CAnimal::CAnimal()
{
}

/**
 * Detructor
 */
CAnimal::~CAnimal()
{
}

/**
 * Retruns the number of eyes per animal
 *
 * \returns number of eyes of the animal
 */
int CAnimal::NumEyes()
{
	return StandardEyeCount;
}