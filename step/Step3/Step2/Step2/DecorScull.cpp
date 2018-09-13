/**
* \file DecorScull.cpp
*
* \author Nic Wiggins
*/

#include "stdafx.h"
#include <string>
#include "DecorScull.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring DecorScullImageName = L"images/scull.png";

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CDecorScull::CDecorScull(CAquarium *aquarium) :
	CItem(aquarium, DecorScullImageName)
{
}

/**
* Destructor.
*/
CDecorScull::~CDecorScull()
{
}

/**
* Save this item to an XML node
* \param node The node we are going to be a child of
* \return itemNode XML node
*/
std::shared_ptr<xmlnode::CXmlNode>
CDecorScull::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);
	itemNode->SetAttribute(L"type", L"scull");
	return itemNode;
}