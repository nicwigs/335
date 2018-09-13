/**
 * \file WorkshopWnd.cpp
 *
 * \author Charles Owen
 */

#include "stdafx.h"
#include <algorithm>    // std::random_shuffle

#include "WorkshopLib.h"
#include "WorkshopWnd.h"
#include "DoubleBufferDC.h"
#include "Minion.h"
#include "WardrobeItem.h"

#include <cassert>

using namespace std;
using namespace Gdiplus;

/// \cond 

// Frame duration in milliseconds
const int FrameDuration = 30;

/* Pixel values */
const int WorkshopWidth = 800;
const int WorkshopHeight = 600;

const int NumStations = 4;

/// Y value for the bottom row buttons
const int ButtonY = 550;

/// Y value for the Wardrobe button (larger)
const int ButtonWardrobeY = ButtonY - 49;

/// Y value for the bottom of a Minion
const int MinionY = 405;


// Duration of a time slice for our simulation
const double SimulationTimeslice = 0.001;

// Maximum conveyor belt speed in stations per second
const double MaxConveyorSpeed = 1;


IMPLEMENT_DYNAMIC(CWorkshopWnd, CWnd)

/// \endcond

/** 
 * Constructor 
 */
CWorkshopWnd::CWorkshopWnd()
{
    srand((unsigned int)time(nullptr));


}

/// Destructor
CWorkshopWnd::~CWorkshopWnd()
{
}


void CWorkshopWnd::Update(double elapsed)
{
    while (elapsed >= SimulationTimeslice)
    {
        UpdateTimeslice();
        elapsed -= SimulationTimeslice;
    }
}


void CWorkshopWnd::Load()
{
    //
    // Load all of the images
    //
    LoadImage(mBackgroundImage, L"WorkshopLib/images/Workshop.jpg");
	LoadImage(mShowerImage, L"WorkshopLib/images/shower-water.png");
	mButtonAdvance.Load(L"WorkshopLib/images/advance.png", L"WorkshopLib/images/advance-d.png");
	mButtonAdvance.SetPosition(400, 90);
	mButtonNext.Load(L"WorkshopLib/images/next.png", L"WorkshopLib/images/next-d.png");
	mButtonNext.SetPosition(WorkshopWidth/2, 90);
	mButtonShower.Load(L"WorkshopLib/images/shower.png", L"WorkshopLib/images/shower-d.png");
	mButtonShower.SetPosition(100, ButtonY);
	mButtonInnoculate.Load(L"WorkshopLib/images/innoculate.png", L"WorkshopLib/images/innoculate-d.png");
	mButtonInnoculate.SetPosition(500, ButtonY);
	mButtonInspect.Load(L"WorkshopLib/images/inspect.png", L"WorkshopLib/images/inspect-d.png");
	mButtonInspect.SetPosition(700, ButtonY);
	mButtonWardrobe.Load(L"WorkshopLib/images/wardrobe.png");
	mButtonWardrobe.SetPosition(300, ButtonWardrobeY);

	mNeedle.Load(L"WorkshopLib/images/needle.png");
	mNeedle.SetX(500);

	mMinionFactory.Load();
}

/// \cond


BEGIN_MESSAGE_MAP(CWorkshopWnd, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_LBUTTONDOWN()
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


/** The workshop width. Based on the width of the background image
* \return Width in pixels */
int CWorkshopWnd::GetWidth()
{
    return (int)(WorkshopWidth * mScale);
}

/** The workshop height. Based on the height of the background image
* \return Height in pixels */
int CWorkshopWnd::GetHeight()
{
    return (int)(WorkshopHeight * mScale);
}

void CWorkshopWnd::OnPaint()
{
    if (mFirstDraw)
    {
        SetTimer(1, FrameDuration, nullptr);
        mFirstDraw = false;
    }

    // Handle time management for the simulation
    TimeManagement(); 

    CPaintDC paintDC(this); // device context for painting

    CDoubleBufferDC dbDC(&paintDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context
	graphics.ScaleTransform((REAL)mScale, (REAL)mScale);

    int w, h;
    CRect rect;
    GetClientRect(&rect);
    w = rect.Width();
    h = rect.Height();
    int bottom = mBackgroundImage->GetHeight();

    // 
    // Background
    //

    Draw(&graphics, mBackgroundImage, 0, 0);

    //
    // Buttons
    //
    DrawButtons(&graphics);

	// Draw needle before the Minion
	mNeedle.Draw(&graphics);

	if (mMinion != nullptr)
	{
		mMinion->Draw(&graphics, (int)((mMinionPosition - 0.5) * WorkshopWidth / NumStations), MinionY);
	}

	if (mShower)
	{
		Draw(&graphics, mShowerImage, 25, 80);
	}

	if (mDressingItem != nullptr)
	{
		mDressingItem->Draw(&graphics, 0, 0);
	}

	if (mStrippingItem != nullptr)
	{
		mStrippingItem->Draw(&graphics, 0, 0);
	}

}


void CWorkshopWnd::DrawButtons(Gdiplus::Graphics *graphics)
{
	mButtonNext.Draw(graphics);
	mButtonAdvance.Draw(graphics); 
	mButtonShower.Draw(graphics);
	mButtonInnoculate.Draw(graphics);
	mButtonInspect.Draw(graphics);
	mButtonWardrobe.Draw(graphics);
}





void CWorkshopWnd::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    UpdateWindow();

    CWnd::OnTimer(nIDEvent);
}


void CWorkshopWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x = (int)(point.x / mScale);
	point.y = (int)(point.y / mScale);

	mLButtonDown = true;

    //
    // Standard buttons
    //
	if (mButtonNext.ButtonDown(point))
	{
		mController->OnNextPressed();
		return;
	}

	if (mButtonAdvance.ButtonDown(point))
	{
		mController->OnAdvancePressed();
		return;
	}

	if (mButtonShower.ButtonDown(point))
	{
		mController->OnShowerPressed();
		return;
	}

	if (mButtonInnoculate.ButtonDown(point))
	{
		mController->OnInnoculatePressed();
		return;
	}

	if (mButtonInspect.ButtonDown(point))
	{
		mController->OnInspectPressed();
		return;
	}

	auto ret = mButtonWardrobe.ButtonDown(point);
	if (ret != CWorkshopController::None)
	{
		mController->OnWardrobePressed(ret);
		return;
	}

    CWnd::OnLButtonDown(nFlags, point);
}

void CWorkshopWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	point.x = (int)(point.x / mScale);
	point.y = (int)(point.y / mScale);


	if (mLButtonDown)
	{
		ButtonsUp();
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void CWorkshopWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	point.x = (int)(point.x / mScale);
	point.y = (int)(point.y / mScale);

	if (!(nFlags & MK_LBUTTON) && mLButtonDown)
	{
		ButtonsUp();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CWorkshopWnd::ButtonsUp()
{
	mLButtonDown = false;
	mButtonAdvance.ButtonUp();
	mButtonNext.ButtonUp();
	mButtonShower.ButtonUp();
}


int CWorkshopWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    Load();



    return 0;
}




BOOL CWorkshopWnd::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Load an image into a local bitmap pointer
* \param bitmap Reference to shared_ptr we load into
* \param name The filename to load */
void CWorkshopWnd::LoadImage(std::shared_ptr<Gdiplus::Bitmap> &bitmap, const wchar_t *name)
{
    bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(name));
    if (bitmap->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open: ");
        msg += name;
        AfxMessageBox(msg.c_str());
    }
}

/**
* Draw a bitmap it's native size.
* \param bitmap Bitmap declared as a shared_ptr to a Gdiplus::Bitmap
* \param x X location in pixels
* \param y Y location in pixels
*/
void CWorkshopWnd::Draw(Gdiplus::Graphics *graphics, std::shared_ptr<Gdiplus::Bitmap> &bitmap, int x, int y)
{
    graphics->DrawImage(bitmap.get(), x, y, bitmap->GetWidth(), bitmap->GetHeight());
}

/**
* Set the elevator controller we are using for this elevator.
* @param c Elevator controller
*/
void CWorkshopWnd::SetController(std::shared_ptr<CWorkshopController> c)
{
    mController = c;
    mController->SetWorkshop(this);
    mController->Initialize();
}


/** Handle once-per-draw time management
*
* Handles updating the time management component and
* calls to the local Update function.
*/
void CWorkshopWnd::TimeManagement()
{
    mTimeManagement.Update();

    while (mTime < mTimeManagement.GetTime())
    {
        UpdateTimeslice();
        mTime += SimulationTimeslice;
    }

}


/** Update in time
*/
void CWorkshopWnd::UpdateTimeslice()
{
    double elapsed = SimulationTimeslice;

	if (mNeedle.IsInnoculating())
	{
		mNeedle.Update(elapsed);
		if (!mNeedle.IsInnoculating())
		{
			mController->InnoculationDone();
		}
	}
	
	mMinionPosition += mConveyorSpeed * elapsed;
	if (mMinionPosition >= 5.0)
	{
		// Minion has left the building
		mMinion = nullptr;
	}
	
	if (mDressingItem != nullptr && mDressingItem->IsFlying())
	{
		mDressingItem->Update(elapsed);
		if (!mDressingItem->IsFlying()) {
			mMinion->Add(mDressingItem);
			mDressingItem = nullptr;
			mController->MinionDressed();
		}
	}

	if (mStrippingItem != nullptr && mStrippingItem->IsFlying())
	{
		mStrippingItem->Update(elapsed);
		if (!mStrippingItem->IsFlying()) {
			mStrippingItem = nullptr;
			mController->StripDone();
		}
	}

    if (mController != nullptr)
    {
        mController->Service();
    }

}

void CWorkshopWnd::NextMinion()
{
	if (mForceEyes == 0)
	{
		mMinion = mMinionFactory.Create(rand() & 1 + 1);
	}
	else 
	{
		mMinion = mMinionFactory.Create(mForceEyes);
	}
	
	mMinionPosition = 0;
	SetConveyorSpeed(0);
}

void CWorkshopWnd::SetConveyorSpeed(double speed)
{
    // Actual stored speed is in stations per second
	mConveyorSpeed = speed * MaxConveyorSpeed;
}

void CWorkshopWnd::SetShower(bool enable)
{
	mShower = enable;
	if (mShower && mMinion != nullptr)
	{
		mMinion->Shower();
	}
}

void CWorkshopWnd::DressMinion(CWorkshopController::Wardrobe item)
{
	assert(mMinion != nullptr);
	mDressingItem = mMinionFactory.CreateWardrobe(item);
	mDressingItem->Fly(mButtonWardrobe.GetPosition(), mMinion->Target(mDressingItem->GetItem()));
}

void CWorkshopWnd::Innoculate()
{
	assert(mMinion != nullptr);
	mNeedle.Innoculate();
	mMinion->Innoculate();
}

void CWorkshopWnd::KillMinion()
{
	assert(mMinion != nullptr);
	mMinion->Kill();
}

void CWorkshopWnd::PassedInspection()
{
	assert(mMinion != nullptr);
	mMinion->Passed();
}

void CWorkshopWnd::Strip()
{
	assert(mMinion != nullptr);
	mStrippingItem = mMinion->Strip();
	mStrippingItem->Fly(mMinion->Target(mStrippingItem->GetItem()), mButtonWardrobe.GetPosition());
}

/// \endcond


