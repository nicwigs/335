/**
* \file FishDory.cpp
*
* \author Nic Wiggins
*/

#include "stdafx.h"
#include <string>
#include "FishDory.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishDoryImageName = L"images/dory.png";

/// Maximum speed in X direction in
/// in pixels per second
const double MaxSpeedX = 80;

/// Minimum speed in X Direction in
/// in pixels per second
const double MinSpeedX = 50;

/// Maximum speed in Y direction in
/// in pixels per second
const double MaxSpeedY = 30;

/// Minimum speed in Y Direction in
/// in pixels per second
const double MinSpeedY = 10;

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishDory::CFishDory(CAquarium *aquarium) :
	CFish(aquarium, FishDoryImageName)
{
	//Dorry is always clueless, she starts opposite of the other fish, moving left
	// Moves fast in X, slow in Y
	SetSpeedX(-(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX)));
	SetSpeedY(-(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY)));
	SetMirror(true);
}

/**
* Destructor.
*/
CFishDory::~CFishDory()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \return itemNode XML node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);
	itemNode->SetAttribute(L"type", L"dory");
	return itemNode;
}