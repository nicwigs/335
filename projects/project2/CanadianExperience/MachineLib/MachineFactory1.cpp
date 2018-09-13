/**
 * \file MachineFactory1.cpp
 *
 * \author Nic Wiggins
 */
#include "stdafx.h"
#include <memory>
#include "MachineFactory1.h"
#include "WorkingMachine.h"
#include "Shape.h"
#include "Motor.h"
#include "Gear.h"
#include "Arm.h"
#include "Rod.h"
#include "Lever.h"
#include "Piston.h"
using namespace std;
using namespace Gdiplus;
/**
 * Constructor.
 */
CMachineFactory1::CMachineFactory1()
{
}
/**
 * Destructor. 
 */
CMachineFactory1::~CMachineFactory1()
{
}
/**
* Create a working machine object
* \returns Object of type CWorkingMachine
*/
std::shared_ptr<CWorkingMachine> CMachineFactory1::CreateMachine()
{
	//The machine
	auto machine = make_shared<CWorkingMachine>(1);

	// The base
	auto base = make_shared<CShape>();
	int wid = 550;
	base->Rectangle(-wid / 2, 0, wid, 40);
	base->SetImage(L"images/base.png");
	machine->AddComponent(base);

	//The motor
	auto motor = make_shared<CMotor>();
	wid = 100;
	motor->Rectangle(-wid / 2, 40, wid, 80);
	motor->SetImage(L"images/motor-frame.png");

	auto shaft = make_shared<CPolygon>();
	wid = 50;
	shaft->CenteredSquare(wid);
	shaft->SetImage(L"images/electric-wheel.png");

	motor->SetPosition(100, -38-40);
	motor->SetSpeed(1.0);
	motor->SetShaft(shaft);
	machine->AddComponent(motor);
	machine->SetMotor(motor);

	// The gear driven by the motor
	// radius 20 pixels, 10 teeth
	auto gear1 = make_shared<CGear>(20, 10);
	gear1->SetImage(L"images/iron.png");
	gear1->SetPosition(motor->GetX(),motor->GetY());
	machine->AddComponent(gear1);

	motor->GetSource()->AddSink(gear1->GetSink());

	// A post that holds the larger gear
	auto gear2post = make_shared<CShape>();
	gear2post->Rectangle(-10, 0, 20, 30);
	gear2post->SetPosition(gear1->GetX() + 55, -40);
	gear2post->SetColor(Color::DarkGreen);
	machine->AddComponent(gear2post);

	// The second gear
	// Radius 40 pixels, 20 teeth
	auto gear2 = make_shared<CGear>(40, 20);
	gear2->SetImage(L"images/hammered-copper.png");
	gear2->SetPosition(gear1->GetX() + 55, gear1->GetY());
	machine->AddComponent(gear2);

	gear2->GetSink()->SetSpeedRatio(-0.5); //gear1 teeth/gear2 teeth
	gear1->GetSource()->AddSink(gear2->GetSink());

	// The arm attached to the second gear
	// 50 pixels long
	auto arm = make_shared<CArm>(50);
	arm->SetImage(L"images/arm1.png");
	arm->SetPosition(gear2->GetX(),gear2->GetY());
	machine->AddComponent(arm);

	gear2->GetSource()->AddSink(arm->GetSink());

	// The column that holds the lever
	auto column = make_shared<CShape>();
	column->Rectangle(-20, -40, 40, 220);
	column->SetImage(L"images/column.png");

	// The lever
	auto lever = make_shared<CLever>(400);
	lever->SetPosition(0, -232);
	lever->SetImage(L"images/lever.png");
	lever->SetDriveLength(190);
	machine->AddComponent(lever);


	// The flag attached to the lever
	// Adding the points allows (0,0) be at the end
	// of the flagpole, so it rotates around that point.
	auto flag = make_shared<CShape>();
	flag->AddPoint(-50, 0);
	flag->AddPoint(-50, -100);
	flag->AddPoint(5, -100);
	flag->AddPoint(5, 0);
	flag->SetImage(L"images/flag.png");
	flag->SetPosition(lever->GetX(),lever->GetY());
	machine->AddComponent(flag);

	lever->GetRotationSource()->AddSink(flag->GetSink());

	// Column is added after the lever so it is in front
	machine->AddComponent(column);

	// Rod from arm to lever
	auto rod1 = make_shared<CRod>(arm->GetEndPoint(), lever->GetDrivePoint());
	BYTE gray = 50;
	rod1->SetColor(Color(gray, gray, gray));
	machine->AddComponent(rod1);

	arm->GetSource()->AddSink(rod1->GetSink());
	rod1->GetSource()->AddSink(lever->GetSink());

	//Piston
	// Height 90, width 30
	auto piston = make_shared<CPiston>(90, 30);
	piston->SetImage(L"images/piston.png");
	piston->SetPosition(-175,-140);
	machine->AddComponent(piston);

	// Rod from lever to Piston
	auto rod2 = make_shared<CRod>(lever->GetPushPoint(),piston->GetPosition());
	rod2->SetColor(Color(gray, gray, gray));
	machine->AddComponent(rod2);

	lever->GetPositionSource()->AddSink(rod2->GetSink());
	rod2->GetSource()->AddSink(piston->GetSink());

	// Cylinder
	auto cylinder = make_shared<CShape>();
	cylinder->Rectangle(-30, 0, 60, 120);
	cylinder->SetPosition(-175, -38);
	cylinder->SetImage(L"images/cylinder.png");
	machine->AddComponent(cylinder);


	return machine;
}
