/**
 * \file MachineFactory2.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "MachineFactory2.h"
#include "WorkingMachine.h"
#include "Shape.h"
#include "Motor.h"
#include "Gear.h"
#include "Arm.h"
#include "Rod.h"
#include "Lever.h"
#include "Piston.h"
using namespace std;
/**
 * Constructor.
 */
CMachineFactory2::CMachineFactory2()
{
}

/**
 * Destructor. 
 */
CMachineFactory2::~CMachineFactory2()
{
}
/**
* Create a working machine object
* \returns Object of type CWorkingMachine
*/
std::shared_ptr<CWorkingMachine> CMachineFactory2::CreateMachine()
{
	//The machine
	auto machine = make_shared<CWorkingMachine>(2);

	//Try a shape
	auto body = make_shared<CShape>();
	int width = 500;
	body->Rectangle(-width / 2, 0, width, 400);
	body->SetImage(L"images/mail_truck_rev3_translucent_90.png");

	//Try a motor
	auto motor = make_shared<CMotor>();
	width = 60;
	int height = 80;
	motor->Rectangle(-width / 2, height/2, width, height);

	auto shaft = make_shared<CPolygon>();
	shaft->CenteredSquare(55);
	shaft->SetImage(L"images/shaft.png");

	motor->SetPosition(145,-60);
	motor->SetShaft(shaft);
	machine->SetMotor(motor);

	// The gear driven by the motor
	// radius 20 pixels, 10 teeth
	auto gear1 = make_shared<CGear>(25, 8);
	gear1->SetImage(L"images/iron.png");
	gear1->SetPosition(motor->GetX(), motor->GetY());

	motor->GetSource()->AddSink(gear1->GetSink());

	// The second gear to right of motor
	// Radius 40 pixels, 20 teeth
	auto gear2 = make_shared<CGear>(45, 16);
	gear2->SetImage(L"images/iron.png");
	gear2->SetPosition(gear1->GetX() + 65, gear1->GetY());

	gear2->GetSink()->SetSpeedRatio(-0.5); //gear1 teeth/gear2 teeth
	gear1->GetSource()->AddSink(gear2->GetSink());

	// The third gear to left of motor
	// Radius 40 pixels, 20 teeth
	auto gear3 = make_shared<CGear>(45, 16);
	gear3->SetImage(L"images/iron.png");
	gear3->SetPosition(gear1->GetX() - 65, gear1->GetY());

	gear3->GetSink()->SetSpeedRatio(-0.5); //gear1 teeth/gear2 teeth
	gear1->GetSource()->AddSink(gear3->GetSink());

	// The arm attached to the second gear
	// 35 pixels long
	auto arm1 = make_shared<CArm>(-20);
	arm1->SetImage(L"images/arm1.png");
	arm1->SetPosition(gear2->GetX(), gear2->GetY());

	gear2->GetSource()->AddSink(arm1->GetSink());

	// The arm attached to the third gear
	// 35 pixels long
	auto arm2 = make_shared<CArm>(20);
	arm2->SetImage(L"images/arm1.png");
	arm2->SetPosition(gear3->GetX(), gear3->GetY());

	gear3->GetSource()->AddSink(arm2->GetSink());

	//Piston 1
	// Height 40, width 15
	auto piston1 = make_shared<CPiston>(50, 20);
	piston1->SetImage(L"images/piston.png");
	piston1->SetRotation(0.5);
	piston1->SetPosition(-190, -170);

	//Piston 2
	// Height 40, width 15
	auto piston2 = make_shared<CPiston>(50, 20);
	piston2->SetImage(L"images/piston.png");
	piston2->SetRotation(0.5);
	piston2->SetPosition(piston1->GetX()+25, piston1->GetY()+40);

	//Piston 3
	// Height 40, width 15
	auto piston3 = make_shared<CPiston>(50, 20);
	piston3->SetImage(L"images/piston.png");	
	piston3->SetRotation(0.5);
	piston3->SetPosition(piston2->GetX()+25, piston2->GetY()-5);

	//Piston 4
	// Height 40, width 15
	auto piston4 = make_shared<CPiston>(50, 20);
	piston4->SetImage(L"images/piston.png");
	piston4->SetRotation(0.5);
	piston4->SetPosition(piston3->GetX() + 25, piston1->GetY()-5);

	// Lever1
	auto lever1 = make_shared<CLever>(290);
	lever1->SetPosition(-15, -150);
	lever1->SetImage(L"images/lever.png");
	lever1->SetDriveLength(135);

	// Rod from arm to lever
	auto rod1 = make_shared<CRod>(arm2->GetEndPoint(), lever1->GetDrivePoint());

	arm2->GetSource()->AddSink(rod1->GetSink());
	rod1->GetSource()->AddSink(lever1->GetSink());

	// Rod from lever to Piston
	auto rod2 = make_shared<CRod>(lever1->GetPushPoint(), piston2->GetPosition());

	lever1->GetPositionSource()->AddSink(rod2->GetSink());
	rod2->GetSource()->AddSink(piston2->GetSink());

	// Rod from lever to Piston
	auto rod3 = make_shared<CRod>(lever1->GetPushPoint(), piston3->GetPosition());

	lever1->GetPositionSource()->AddSink(rod3->GetSink());
	rod3->GetSource()->AddSink(piston3->GetSink());

	// Lever2
	auto lever2 = make_shared<CLever>(410);
	lever2->SetPosition(40, -200);
	lever2->SetImage(L"images/lever.png");
	lever2->SetDriveLength(190);

	// Rod from arm to lever
	auto rod4 = make_shared<CRod>(arm1->GetEndPoint(), lever2->GetDrivePoint());

	arm1->GetSource()->AddSink(rod4->GetSink());
	rod4->GetSource()->AddSink(lever2->GetSink());

	// Rod from lever to Piston
	auto rod5 = make_shared<CRod>(lever2->GetPushPoint(), piston1->GetPosition());

	lever2->GetPositionSource()->AddSink(rod5->GetSink());
	rod5->GetSource()->AddSink(piston1->GetSink());

	// Rod from lever to Piston
	auto rod6 = make_shared<CRod>(lever2->GetPushPoint(), piston4->GetPosition());

	lever2->GetPositionSource()->AddSink(rod6->GetSink());
	rod6->GetSource()->AddSink(piston4->GetSink());

	//Draw order
	machine->AddComponent(lever1);
	machine->AddComponent(rod2);
	machine->AddComponent(rod3);
	machine->AddComponent(lever2);
	machine->AddComponent(rod5);
	machine->AddComponent(rod6);

	machine->AddComponent(body);

	machine->AddComponent(motor);
	machine->AddComponent(gear1);
	machine->AddComponent(gear2);
	machine->AddComponent(gear3);
	machine->AddComponent(arm1);
	machine->AddComponent(arm2);
	machine->AddComponent(piston1);
	machine->AddComponent(piston2);
	machine->AddComponent(piston3);
	machine->AddComponent(piston4);
	machine->AddComponent(rod1);
	
	machine->AddComponent(rod4);



	return machine;
}
