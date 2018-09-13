/**
 * \file LavarFactory.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "LavarFactory.h"
#include <memory>
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace std;
using namespace Gdiplus;


/**
 * Constructor. 
 */
CLavarFactory::CLavarFactory()
{
}


/**
 * Destructor.
 */
CLavarFactory::~CLavarFactory()
{
}

/** This is a concrete factory method that creates our Harold actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CLavarFactory::Create()
{
	shared_ptr<CActor> actor = make_shared<CActor>(L"Lavar");

	auto shirt = make_shared<CImageDrawable>(L"Shirt", L"images/black_coat.png");
	shirt->SetCenter(Point(45, 148));
	shirt->SetPosition(Point(0, -114));
	actor->SetRoot(shirt);

	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/jeans_lleg.png");
	lleg->SetCenter(Point(11, 7));
	lleg->SetPosition(Point(20, 0));
	shirt->AddChild(lleg);

	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/jeans_rleg.png");
	rleg->SetCenter(Point(49, 7));
	rleg->SetPosition(Point(-20, 0));
	shirt->AddChild(rleg);

	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/headb3.png");
	headb->SetCenter(Point(46, 33));
	headb->SetPosition(Point(0, -145));
	shirt->AddChild(headb);
	
	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/headt3.png");
	headt->SetCenter(Point(49, 93));
	headt->SetPosition(Point(0, -33));
	headt->SetRightEyeCenter(Point(65, 70));
	headt->SetLeftEyeCenter(Point(35, 70));
	headt->SetRightEyeBrow(Point(65, 45), Point(85, 65));
	headt->SetLeftEyeBrow(Point(35, 45), Point(15, 65));
	headb->AddChild(headt);
	
	auto larm = make_shared<CPolyDrawable>(L"Left Arm");
	larm->SetColor(Color(25, 20, 26));
	larm->SetPosition(Point(40, -140));
	larm->AddPoint(Point(-7, -7));
	larm->AddPoint(Point(-7, 96));
	larm->AddPoint(Point(15, 96));
	larm->AddPoint(Point(15, -7));
	shirt->AddChild(larm);


	auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
	rarm->SetColor(Color(25, 20, 26));
	rarm->SetPosition(Point(-45, -140));
	rarm->AddPoint(Point(-7, -7));
	rarm->AddPoint(Point(-7, 96));
	rarm->AddPoint(Point(15, 96));
	rarm->AddPoint(Point(15, -7));
	shirt->AddChild(rarm);

	auto lhand = make_shared<CPolyDrawable>(L"Left Hand");
	lhand->SetColor(Color(208, 160, 116));
	lhand->SetPosition(Point(0, 96));
	lhand->AddPoint(Point(-12, -2));
	lhand->AddPoint(Point(-12, 17));
	lhand->AddPoint(Point(15, 17));
	lhand->AddPoint(Point(15, -2));
	larm->AddChild(lhand);

	auto rhand = make_shared<CPolyDrawable>(L"Right Hand");
	rhand->SetColor(Color(208, 160, 116));
	rhand->SetPosition(Point(0, 96));
	rhand->AddPoint(Point(-12, -2));
	rhand->AddPoint(Point(-12, 17));
	rhand->AddPoint(Point(18, 17));
	rhand->AddPoint(Point(18, -2));
	rarm->AddChild(rhand);


	actor->AddDrawable(larm);
	actor->AddDrawable(rarm);
	actor->AddDrawable(rhand);
	actor->AddDrawable(lhand);
	actor->AddDrawable(rleg);
	actor->AddDrawable(lleg);
	actor->AddDrawable(shirt);
	actor->AddDrawable(headb);
	actor->AddDrawable(headt);

	return actor;
}