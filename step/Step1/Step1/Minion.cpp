/**
 * \file Minion.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include <iostream>
#include "Minion.h"

using namespace std;

///exclusive upper bound of the number of eyes a minion can have (1 or 2)
const int EyeCountUpperBound = 3;

/**
 * Constructor
 */
CMinion::CMinion()
{
}

/**
 * Destructor
 */
CMinion::~CMinion()
{
}

/**
 * Obtain a minion description from the user.
 */
void CMinion::ObtainMinionInformation()
{
	cout << endl;
	cout << "Input information about the minion" << endl;

	//Obtain the name
	cout << "Name: ";
	cin >> mName;

	//Obtain weight, loop to ensure entered weight is a double
	bool valid = false;
	while (!valid)
	{
		cout << "Enter weight of minion in kilograms: ";
		double minionWeight;
		cin >> minionWeight;
		if (!cin)
		{
			// We have an error. Clear the input and try again
			cin.clear();
			cin.ignore();
			continue;
		}
		valid = true;
		mWeight = minionWeight;
	}

	//Obtain favorite fruit
	cout << "Favorite Fruit: ";
	cin >> mFavoriteFruit;

	//Obtain number of eyes using a loop to handle errors
	// Can only be 1 or 2 eyes
	valid = false;
	while (!valid)
	{
		cout << "Enter number of eyes (1 or 2): ";
		int numberOfEyes;
		cin >> numberOfEyes;
		if (!cin)
		{
			// We have an error. Clear the input and try again
			cin.clear();
			cin.ignore();
			continue;
		}
		// Check to see if number of eyes is valid 
		if (numberOfEyes > 0 && numberOfEyes < EyeCountUpperBound)
		{
			mEyeCount = numberOfEyes;
			valid = true;
		}
	}

}


/**
 * Dislay the minion
 */
void CMinion::DisplayAnimal()
{
	cout << "Minion " << mName << " // Weight (kg): "
		<< mWeight << " // Favorite Fruit: " << mFavoriteFruit
		<< " // Number of eyes: " << mEyeCount << endl;
}


/**
 * 
 * Provides number of eyes of minion
 *
 * \returns the eye count of the minion
 */
int CMinion::NumEyes()
{
	return mEyeCount;
}