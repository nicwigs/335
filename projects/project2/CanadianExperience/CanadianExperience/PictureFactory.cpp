/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/*! Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(400, 500));


    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(200, 500));

	//Create MachineA
	shared_ptr<CActor> machineA = make_shared<CActor>(L"MachineA");
	auto machine = make_shared<CMachineDrawable>(L"Machine");
	machineA->SetRoot(machine);
	machineA->AddDrawable(machine);
	machineA->SetPosition(Point(200, 200));

	mActorMachineA = machineA;
	mDrawableMachineA = machine;

	//Create MachineB
	shared_ptr<CActor> machineB = make_shared<CActor>(L"MachineB");
	auto machine2 = make_shared<CMachineDrawable>(L"MachineB");
	machine2->SetMachineNumber(2);
	machineB->SetRoot(machine2);
	machineB->AddDrawable(machine2);
	machineB->SetPosition(Point(400, 200));

	mActorMachineB = machineB;
	mDrawableMachineB = machine2;

	//Draw order
	picture->AddActor(machineA);

	picture->AddActor(harold);
	picture->AddActor(sparty);
	picture->AddActor(machineB);

    return picture;
}
