/**
 * \file MinionFactory.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include <cassert>
#include "MinionFactory.h"
#include "ImageHelper.h"
#include "Minion.h"
#include "WardrobeItem.h"

using namespace std;

CMinionFactory::CMinionFactory()
{
}

std::shared_ptr<CMinion> CMinionFactory::Create(int eyes)
{
	if (eyes == 1)
	{
		return make_shared<CMinion>(eyes, mMinion1, mMinion1dead, mPassed);
	}
	else
	{
		eyes = 2;
		return make_shared<CMinion>(eyes, mMinion2, mMinion2dead, mPassed);
	}
}


std::shared_ptr<CWardrobeItem> CMinionFactory::CreateWardrobe(CWorkshopController::Wardrobe item)
{
	assert(item >= CWorkshopController::BlueJeans && item <= CWorkshopController::Goggles2);
	return make_shared<CWardrobeItem>(item, mWardrobe[item]);
}


bool CMinionFactory::Load()
{
	mMinion1 = CImageHelper::LoadImageW(L"WorkshopLib/images/minion1n.png");
	mMinion2 = CImageHelper::LoadImageW(L"WorkshopLib/images/minion2n.png");
	mMinion1dead = CImageHelper::LoadImageW(L"WorkshopLib/images/minion1d.png");
	mMinion2dead = CImageHelper::LoadImageW(L"WorkshopLib/images/minion2d.png");
	mPassed = CImageHelper::LoadImageW(L"WorkshopLib/images/passed.png");

	mWardrobe[CWorkshopController::GreenJeans] = CImageHelper::LoadImageW(L"WorkshopLib/images/pants-green.png");
	mWardrobe[CWorkshopController::BlueJeans] = CImageHelper::LoadImageW(L"WorkshopLib/images/pants-blue.png");
	mWardrobe[CWorkshopController::Goggles1] = CImageHelper::LoadImageW(L"WorkshopLib/images/goggles1.png");
	mWardrobe[CWorkshopController::Goggles2] = CImageHelper::LoadImageW(L"WorkshopLib/images/goggles2.png");


	return mMinion1 != nullptr && mMinion2 != nullptr;
}

CMinionFactory::~CMinionFactory()
{
}

/// \endcond

