/**
 * \file PictureFactory.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"

#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "LavarFactory.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor.
 */
CPictureFactory::CPictureFactory()
{
}

/**
* Destructor.
*/
CPictureFactory::~CPictureFactory()
{
}

/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	shared_ptr<CPicture> picture = make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI =
		make_shared<CImageDrawable>(L"Background", L"images/Background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	// Create and add Harold
	CHaroldFactory factory;
	auto harold = factory.Create();
	// This is where Harold will start out.
	harold->SetPosition(Point(400, 500));
	picture->AddActor(harold);

	// Create and add Lavar Ball
	CLavarFactory factory2;
	auto lavar = factory2.Create();
	// This is where Lavar will start out.
	lavar->SetPosition(Point(800,500));
	picture->AddActor(lavar);

	return picture;
}