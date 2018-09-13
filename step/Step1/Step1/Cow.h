/**
 * \file Cow.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a cow.
 *
 *This class holds a collection of characteristics of a cow.
 */

#pragma once
#include <string>
#include "Animal.h"

/**
 * Class that describes a cow.
 *
 *Holds a collection of characteristics of a cow.
 */
class CCow : public CAnimal
{
public:
	CCow();
	virtual ~CCow();

	/// The types of cow we can have on our farm
	enum Type { Bull, BeefCow, MilkCow };

	void ObtainCowInformation();
	void DisplayAnimal();

private:
	/// The cow's name
	std::string mName;

	/// The type of code: Bull, BeefCow, or MilkCow
	Type mType = MilkCow;

	/// The milk production for a cow in gallons per day
	double mMilkProduction = 0;

};

