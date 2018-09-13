/**
* \file FishNemo.cpp
*
* \author Nic Wiggins
*/

#include "stdafx.h"
#include <string>
#include "FishNemo.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishNemoImageName = L"images/nemo.png";

/// Maximum speed in X direction in
/// in pixels per second
const double MaxSpeedX = 30;

/// Minimum speed in X Direction in
/// in pixels per second
const double MinSpeedX = 20;

/// Maximum speed in Y direction in
/// in pixels per second
const double MaxSpeedY = 70;

/// Minimum speed in Y Direction in
/// in pixels per second
const double MinSpeedY = 60;

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishNemo::CFishNemo(CAquarium *aquarium) :
	CFish(aquarium, FishNemoImageName)
{
	// Nemo swims faster in Y than X
	// He swims up towards the boats - didnt work out for him last time
	SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
	SetSpeedY(-(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY))); 
}

/**
* Destructor.
*/
CFishNemo::~CFishNemo()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \return itemNode XML node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishNemo::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);
	itemNode->SetAttribute(L"type", L"nemo");
	return itemNode;
}