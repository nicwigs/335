/**
 * \file WorkshopController.cpp
 *
 * \author Charles Owen
 */

#include "stdafx.h"
#include "WorkshopController.h"
#include "WorkshopWnd.h"
#include "Minion.h"

#include <cassert>

CWorkshopController::CWorkshopController()
{
}


CWorkshopController::~CWorkshopController()
{
}

/// \cond
void CWorkshopController::SetWorkshop(CWorkshopWnd *workshop)
{
    mWorkshop = workshop;
}
/// \endcond

double CWorkshopController::GetMinionPosition()
{
	assert(mWorkshop != NULL);
	return mWorkshop->GetMinionPosition();
}


void CWorkshopController::NextMinion()
{
	assert(mWorkshop != NULL);
	mWorkshop->NextMinion();
}


void CWorkshopController::SetConveyorSpeed(double speed)
{
    assert(mWorkshop != NULL);
    mWorkshop->SetConveyorSpeed(speed);
}


void CWorkshopController::EnableButtonNext()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonNext(true);
}


void CWorkshopController::DisableButtonNext()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonNext(false);
}

void CWorkshopController::EnableButtonAdvance()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonAdvance(true);
}

void CWorkshopController::DisableButtonAdvance()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonAdvance(false);
}

void CWorkshopController::EnableButtonShower()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonShower(true);
}


void CWorkshopController::DisableButtonShower()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonShower(false);
}

void CWorkshopController::EnableButtonWardrobe()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonWardrobe(true);
}


void CWorkshopController::DisableButtonWardrobe()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonWardrobe(false);
}

void CWorkshopController::EnableButtonInnoculate()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonInnoculate(true);
}


void CWorkshopController::DisableButtonInnoculate()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonInnoculate(false);
}


void CWorkshopController::EnableButtonInspect()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonInspect(true);
}


void CWorkshopController::DisableButtonInspect()
{
	assert(mWorkshop != NULL);
	mWorkshop->EnableButtonInspect(false);
}

void CWorkshopController::SetShower(bool enable)
{
	assert(mWorkshop != NULL);
	mWorkshop->SetShower(enable);
}

void CWorkshopController::DressMinion(CWorkshopController::Wardrobe item)
{
	assert(mWorkshop != NULL);
	mWorkshop->DressMinion(item);
}

void CWorkshopController::StartInnoculate()
{
	assert(mWorkshop != NULL);
	mWorkshop->Innoculate();
}

void CWorkshopController::KillMinion()
{
	assert(mWorkshop != NULL);
	mWorkshop->KillMinion();
}

bool CWorkshopController::IsInnoculated()
{
	assert(mWorkshop != nullptr);
	auto minion = mWorkshop->GetMinion();
	assert(minion != nullptr);
	return minion->IsInnoculated();
}

void CWorkshopController::PassedInspection()
{
	assert(mWorkshop != NULL);
	mWorkshop->PassedInspection();
}

bool CWorkshopController::IsClean()
{
	assert(mWorkshop != nullptr);
	auto minion = mWorkshop->GetMinion();
	assert(minion != nullptr);
	return minion->IsClean();
}

bool CWorkshopController::WardrobeMalfunction()
{
	assert(mWorkshop != nullptr);
	auto minion = mWorkshop->GetMinion();
	assert(minion != nullptr);
	return minion->WardrobeMalfunction();
}

bool CWorkshopController::AnyClothes()
{
	assert(mWorkshop != nullptr);
	auto minion = mWorkshop->GetMinion();
	assert(minion != nullptr);
	return minion->AnyClothes();
}

void CWorkshopController::Strip()
{
	assert(mWorkshop != NULL);
	mWorkshop->Strip();
}

