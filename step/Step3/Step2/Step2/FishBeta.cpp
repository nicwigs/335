/**
 * \file FishBeta.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include <string>
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;

 /// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/// Maximum speed in X direction in
/// in pixels per second
const double MaxSpeedX = 30;

/// Minimum speed in X Direction in
/// in pixels per second
const double MinSpeedX = 2;

/// Maximum speed in Y direction in
/// in pixels per second
const double MaxSpeedY = 5;

/// Minimum speed in Y Direction in
/// in pixels per second
const double MinSpeedY = 2;

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium *aquarium) :
	CFish(aquarium, FishBetaImageName)
{
	//Mr.Beta Fish is slow
	SetSpeedX(MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX));
	SetSpeedY(MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY));
}

/**
 * Destructor. 
 */
CFishBeta::~CFishBeta()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \return itemNode XML node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CFish::XmlSave(node);
	itemNode->SetAttribute(L"type", L"beta");
	return itemNode;
}