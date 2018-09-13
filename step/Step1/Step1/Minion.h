/**
 * \file Minion.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a minion
 *
 * This class holds characteristics of a minion 
 */

#pragma once
#include <string>
#include "Animal.h"

/**
 * Class that describes a minion 
 */
class CMinion : public CAnimal
{
public:
	CMinion();
	virtual ~CMinion();

	void ObtainMinionInformation();
	void DisplayAnimal();
	int NumEyes();

private:
	/// The minion's name
	std::string mName;

	/// The minion's weight
	double mWeight = 0;

	/// The minion's favorite fruit
	std::string mFavoriteFruit;

	/// The minion's number of eyes
	int mEyeCount = 1;

};

