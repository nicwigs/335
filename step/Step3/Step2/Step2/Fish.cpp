/**
 * \file Fish.cpp
 *
 * \author Nic Wiggins
 */


#include "stdafx.h"
#include "Fish.h"
#include "Aquarium.h"

 /// Maximum speed in the X direction in
 /// in pixels per second
const double MaxSpeedX = 50;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Image reverse offset in pixels from
/// edge of image
const int ReverseImageOffset = 10;

/// Image Devisor, used to take half of
/// image height/width for wall detection 
const int ImageDivisor = 2;

/**
* Constructor
* \param aquarium The aquarium we are in
* \param filename Filename for the image we use
*/
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) :
	CItem(aquarium, filename)
{
	mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
	mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
}


/**
 * Destructor.
 */
CFish::~CFish()
{
}


/**
* Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our fish. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CFish::Update(double elapsed)
{

	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);

	// Hit the right side of aquarium 
	if (mSpeedX > 0 && GetX() >=
		GetAquarium()->GetWidth() - ReverseImageOffset - GetImageWidth() / ImageDivisor)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	//Hit Left Side of aquarium
	else if (mSpeedX < 0 && GetX() <= ReverseImageOffset + GetImageWidth() / ImageDivisor)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	//Hit top of aquarium 
	if (mSpeedY < 0 && GetY() <= ReverseImageOffset + GetImageHeight() / ImageDivisor)
	{
		mSpeedY = -mSpeedY;
	}
	//Hit bottom of aquarium 
	else if (mSpeedY > 0 && GetY()
		>= GetAquarium()->GetHeight() - ReverseImageOffset - GetImageHeight() / ImageDivisor)
	{
		mSpeedY = -mSpeedY;
	}
}

/**
* Save a fish to an XML node
* \param node The node we are going to be a child of
* \return itemNode XML node
*/
std::shared_ptr<xmlnode::CXmlNode>
CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);
	itemNode->SetAttribute(L"speedx", mSpeedX);
	itemNode->SetAttribute(L"speedy", mSpeedY);
	return itemNode;
}

/**
* Load the attributes for a fish node.
*
* \param node The Xml node we are loading the item from
*/
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CItem::XmlLoad(node);
	mSpeedX = node->GetAttributeDoubleValue(L"speedx", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"speedy", 0);
	SetMirror(mSpeedX < 0);

}